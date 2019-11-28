#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include "LTexture.h"

using std::vector;
using std::string;

/*
	Structs for resource definition
*/
struct FontDefinition { string name; string path; TTF_Font* instance; int ptSize; };
struct TextureDefinition { string path; SDL_Texture* instance; };
struct MusicDefinition { string path; Mix_Music* instance; };
struct SFXDefinition { string path; Mix_Chunk* instance; };

/*
	ResourcesManager class
*/
class ResourcesManager
{
private:
	vector<TextureDefinition> textures;
	vector<FontDefinition> fonts;
	vector<MusicDefinition> musics;
	vector<SFXDefinition> sfx;
	vector<LTexture*> ltextures;

public:
	SDL_Texture* createTexture(const string path);
	void destroyTexture(const string path);
	void destroyTexture(const SDL_Texture* texture);
	LTexture* createLTexture(const string path);
	void destroyLTexture(const string path);
	TTF_Font* createFont(const string name, const string path, const int ptSize = 16);
	TTF_Font* getFont(const string name); // Simple getter so we don't ship a path everytime
	Mix_Music* createMusic(const string path);
	Mix_Chunk* createSFX(const string path);
	int getResourcesAmount() const;
	void destroy();
};
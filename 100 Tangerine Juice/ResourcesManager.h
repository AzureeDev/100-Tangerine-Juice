#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

/*
	Structs for resource definition
*/
struct FontDefinition {
	string name;
	string path;
	TTF_Font* instance;
	int ptSize;
};

struct TextureDefinition {
	string path;
	SDL_Texture* instance;
};

/*
	ResourcesManager class
*/
class ResourcesManager
{
private:
	vector<TextureDefinition> textures;
	vector<FontDefinition> fonts;

public:
	SDL_Texture* createTexture(const string path);
	void destroyTexture(const string path);
	TTF_Font* createFont(const string name, const string path, const int ptSize = 16);
	TTF_Font* getFont(const string name); // Simple getter so we don't ship a path everytime
	void destroy();
};
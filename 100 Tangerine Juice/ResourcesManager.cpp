#include "ResourcesManager.h"
#include "Globals.h"

#include <SDL_image.h>

SDL_Texture* ResourcesManager::createTexture(const string path)
{
	/*
		Create a new texture and returns it
	*/

	for (size_t i = 0; i < this->textures.size(); ++i)
	{
		if (this->textures[i].path == path)
		{
			return this->textures[i].instance;
		}
	}

	SDL_Texture* texture = IMG_LoadTexture(Globals::engine->getRenderer(), path.c_str());

	if (texture == nullptr)
	{
		SDL_Log("ResourcesManager::createTexture - There was an error loading %s. Is the path correct?", path.c_str());
		return;
	}

	this->textures.push_back({ path, texture });

	return texture;
}

void ResourcesManager::destroyTexture(const string path)
{
	/*
		Destroys the texture defined by path
	*/

	for (size_t i = 0; i < this->textures.size(); ++i)
	{
		if (this->textures[i].path == path)
		{
			SDL_DestroyTexture(this->textures[i].instance);
			this->textures[i].instance = nullptr;
			this->textures.erase(this->textures.begin() + i);

			break;
		}
	}
}

void ResourcesManager::destroyTexture(const SDL_Texture* texture)
{
	/*
		Destroys the texture defined by SDL_Texture*
	*/

	for (size_t i = 0; i < this->textures.size(); ++i)
	{
		if (this->textures[i].instance == texture)
		{
			SDL_DestroyTexture(this->textures[i].instance);
			this->textures[i].instance = nullptr;
			this->textures.erase(this->textures.begin() + i);

			break;
		}
	}
}

shared_ptr<LTexture> ResourcesManager::createLTexture(const string path)
{
	/*
		Create a new LTexture
	*/

	shared_ptr<LTexture> newTexture = make_shared<LTexture>(LTexture(path));
	this->ltextures.push_back(newTexture);

	return newTexture;
}

shared_ptr<LTexture> ResourcesManager::createLTexture()
{
	/*
		Create a new LTexture (constructor empty)
	*/

	shared_ptr<LTexture> newTexture = make_shared<LTexture>(LTexture());
	this->ltextures.push_back(newTexture);

	return newTexture;
}

void ResourcesManager::destroyLTexture(const string path)
{
	/*
		Destroys the texture defined by path
	*/
}

TTF_Font* ResourcesManager::createFont(const string name, const string path, const int ptSize)
{
	/*
		Create a new font with ptSize and returns it
	*/

	for (size_t i = 0; i < this->fonts.size(); ++i)
	{
		if (this->fonts[i].name == name)
		{
			return this->fonts[i].instance;
		}
	}

	TTF_Font* font = TTF_OpenFont(path.c_str(), ptSize);
	this->fonts.push_back({ name, path, font, ptSize });

	return font;
}

TTF_Font* ResourcesManager::getFont(const string name)
{
	/*
		Get the font with the name "name". Nullptr if the name wasn't found.
	*/

	for (size_t i = 0; i < this->fonts.size(); ++i)
	{
		if (this->fonts[i].name == name)
		{
			return this->fonts[i].instance;
		}
	}

	return nullptr;
}

Mix_Music* ResourcesManager::createMusic(const string path)
{
	/*
		Create a new music and returns it
	*/

	for (size_t i = 0; i < this->musics.size(); ++i)
	{
		if (this->musics[i].path == path)
		{
			return this->musics[i].instance;
		}
	}

	Mix_Music* music = Mix_LoadMUS(path.c_str());
	this->musics.push_back({ path, music });

	return music;
}

Mix_Chunk* ResourcesManager::createSFX(const string path)
{
	/*
		Create a new sfx sound and returns it
	*/

	for (size_t i = 0; i < this->sfx.size(); ++i)
	{
		if (this->sfx[i].path == path)
		{
			return this->sfx[i].instance;
		}
	}

	Mix_Chunk* sfx = Mix_LoadWAV(path.c_str());
	this->sfx.push_back({ path, sfx });

	return sfx;
}

int ResourcesManager::getResourcesAmount() const
{
	size_t amount = this->ltextures.size() + this->textures.size() + this->sfx.size() + this->musics.size() + this->fonts.size();
	return static_cast<int>(amount);
}

void ResourcesManager::destroy()
{
	/*
		Destroy everything loaded, called in LilacEngine::exit()
	*/

	for (const auto& texture : this->textures)
	{
		SDL_DestroyTexture(texture.instance);
	}

	for (const auto& font : this->fonts)
	{
		TTF_CloseFont(font.instance);
	}

	for (const auto& music : this->musics)
	{
		Mix_FreeMusic(music.instance);
	}

	for (const auto& sfx : this->sfx)
	{
		Mix_FreeChunk(sfx.instance);
	}

	this->textures.clear();
	this->ltextures.clear();
	this->fonts.clear();
	this->musics.clear();
	this->sfx.clear();
}
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
			this->textures.erase(this->textures.begin() + i);

			break;
		}
	}
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

void ResourcesManager::destroy()
{
	/*
		Destroy everything loaded, called in LilacEngine::exit()
	*/
	
	for (auto& texture : this->textures)
	{
		SDL_DestroyTexture(texture.instance);
	}

	for (auto& font : this->fonts)
	{
		TTF_CloseFont(font.instance);
	}

	this->textures.clear();
	this->fonts.clear();
}

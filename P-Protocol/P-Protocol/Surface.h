#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "window.h"
#include "render.h"


class Surface
{
public:
	Surface()
		:
		sSurface(NULL)
	{};
	Surface(SDL_Window* w)
		:
		sSurface(SDL_GetWindowSurface(w))
	{
		if (NULL == sSurface)
			printf("ERROR: unable to initialize window surface. SDL error: %s\n", SDL_GetError());
	};
	Surface(char* path)
		:
		sSurface(SDL_LoadBMP(path))
	{
		if (NULL == sSurface)
			printf("ERROR: unable to load %s. SDL error: %s\n", path, SDL_GetError());
	};
	Surface(Window* w)
		:
		sSurface(SDL_GetWindowSurface(w->getWindow()))
	{
		if (NULL == sSurface)
			printf("ERROR: unable to initialize window surface. SDL error: %s\n", SDL_GetError());
	};
	~Surface()
	{
		SDL_FreeSurface(sSurface);
		sSurface = NULL;
	};
	void setSurface(SDL_Surface* newSurface)
	{
		sSurface = newSurface;
	}
	bool loadBmp(const char* origin)
	{
		sSurface = SDL_LoadBMP(origin);
		if (sSurface == NULL)
		{
			printf("ERROR: unable to load the bmp %s. SDL error: %s", origin, SDL_GetError());
			return false;
		}
		return true;
	}
	bool blit(SDL_Surface* src)
	{
		if (SDL_BlitSurface(src, NULL, sSurface, NULL) < 0)
		{
			printf("ERROR: unable to blit. SDL error: %s", SDL_GetError());
			return false;
		}
		return true;
	}
	SDL_PixelFormat* getFormat()
	{
		return sSurface->format;
	}
	SDL_Surface* getSurface()
	{
		return sSurface;
	}
	SDL_Surface** getSurfacePointer()
	{
		return &sSurface;
	}

	//actual surface
private:
	SDL_Surface* sSurface;
};

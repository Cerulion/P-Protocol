#pragma once

#include <stdio.h>

#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

bool init(SDL_Window** window, SDL_Surface** surface, size_t sWidth, size_t sHeight)
{
	//init sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("sdl could not bet initialized. error: %s\n", SDL_GetError());
		return false;
	}
	//create window
	*window = SDL_CreateWindow("haha this ist the second", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sWidth, sHeight, SDL_WINDOW_SHOWN);

	//valid?
	if (*window == NULL)
	{
		printf("window could not be initialized. error: %s\n", SDL_GetError());
		return false;
	}

	*surface = SDL_GetWindowSurface(*window);
	return true;
}

void close(SDL_Surface** surfaces, SDL_Window** window)
{
	//destory window
	SDL_DestroyWindow(*window);
	*window = NULL;

	//destroy surface
	SDL_FreeSurface(*surfaces);
	*surfaces = NULL;

	//destroy SDL xD
	SDL_Quit();
}

void closeSingle(SDL_Surface** surface)
{
	SDL_FreeSurface(*surface);
	*surface = NULL;
}

SDL_Surface* loadSurface(char* path)
{
	SDL_Surface* newSurface = SDL_LoadBMP(path);
	if (newSurface == NULL)
		printf("could not load bmp %s. SDL error: %s\n", path, SDL_GetError());
	return newSurface;
}

bool loadMedia(SDL_Surface** surface[], SDL_Surface* surf, char* origin, char* origin2)
{
	*surface[0] = loadSurface(origin);
	*surface[1] = loadSurface(origin);
	*surface[2] = loadSurface(origin);
	*surface[3] = loadSurface(origin2);
	*surface[4] = SDL_ConvertSurface(loadSurface(origin2), surf->format, NULL);
	return true;
}
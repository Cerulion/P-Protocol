#pragma once

#include <stdio.h>
#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#include <SDL_ttf.h>

class SDL
{
public:
	SDL()
		:
		quit(false)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("could not initialize SDL. SDL error: %s\n", SDL_GetError());
			quit = true;
		}
		if (TTF_Init() < 0)
		{
			printf("could not initialize SDL_ttf. SDL_ttf error: %s\n", TTF_GetError());
			quit = true;
		}
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			//TODO
		}
		printf("SDL has been initialized\n");
	}
	~SDL()
	{
		SDL_Quit();
		printf("SDL has been shut downed\n");
	}
	bool q()
	{
		return quit;
	}
	void q(bool newQ)
	{
		quit = newQ;
	}
	SDL_Event* getEvent()
	{
		return &e;
	}
private:
	SDL_Event e;
	bool quit;
};

#pragma once

#include <stdio.h>
#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

bool eventHandler(SDL_Event* e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			return false;
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				pic.loadBmp(one);
				break;
			case SDLK_DOWN:
				pic.loadBmp(two);
				break;
			case SDLK_LEFT:
				pic.loadBmp(one);
				break;
			case SDLK_RIGHT:
				pic.loadBmp(two);
				break;
			default:
				pic.loadBmp(two);
				break;
		}
	}
	return true;
}
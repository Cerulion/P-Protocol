#pragma once

#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#include <stdio.h>

#include "Window.h"
#include "Rect.h"
#include "color.h"
#include "Surface.h"

class Render
{
public:
	Render()
		:
		pRender(NULL)
	{};
	Render(Window* pWindow)
		:
		//using vsync.. if you dont want to, then delete SDL_RENDERER_PRESENTVSYNC
		//acclelerated renderer somehow doesnt work on my raspi :/ (SDL_RENDERER_ACCELERATED)
		pRender(SDL_CreateRenderer(pWindow->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
	{
		if (NULL == pRender)
			printf("Renderer could not be initialized. SDL Error: %s", SDL_GetError());
		else
		{
			SDL_SetRenderDrawColor(pRender, 0, 0, 0, 0xFF);

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
	};
	Render(Surface* pSurface)
		:
		pRender(SDL_CreateSoftwareRenderer(pSurface->getSurface()))
	{
		if (NULL == pRender)
			printf("Renderer could not be initialized. SDL Error: %s", SDL_GetError());
		else
		{
			SDL_SetRenderDrawColor(pRender, 0, 0, 0, 0xFF);

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
	};
	Render(SDL_Renderer* aRender)
		:
		pRender(aRender)
	{};
	~Render()
	{
		SDL_DestroyRenderer(pRender);
		pRender = NULL;
	}
	SDL_Renderer* getRenderer()
	{
		return pRender;
	}
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		SDL_SetRenderDrawColor(pRender, r, g, b, a);
	}
	void setColor(color* newColor)
	{
		SDL_SetRenderDrawColor(pRender, newColor->r, newColor->g, newColor->b, newColor->a);
	}
	void drawPoint(point* Position)
	{
		SDL_RenderDrawPoint(pRender, Position->getPoint()->x, Position->getPoint()->y);
	}
	void drawRect(Rect* Position)
	{
		SDL_Rect temp = { Position->getRect()->x, Position->getRect()->y, Position->getRect()->w, Position->getRect()->h };
		SDL_RenderFillRect(pRender, &temp);
	}
	void clear()
	{
		SDL_RenderClear(pRender);
	}
	void update()
	{
		SDL_RenderPresent(pRender);
	}
	void setViewport(Rect dst)
	{
		SDL_RenderSetViewport(pRender, dst.getRect());
	}
	void setRenderer(SDL_Renderer* newRender)
	{
		pRender = newRender;
	}
private:
	SDL_Renderer* pRender;
};
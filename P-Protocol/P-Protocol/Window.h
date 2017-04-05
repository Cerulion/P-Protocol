#pragma once

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif

#include <stdio.h>


class Window
{
public:
	Window()
		:
		wWindow(NULL)
	{};
	Window(const char* title, int x, int y, int w, int h)
		:
		wWindow(SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN ))
	{
		if (NULL == wWindow)
			printf("unable to create window. SDL error: %s\n", SDL_GetError());
	};
	Window(const char* title, int w, int h)
		:
		wWindow(SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN ))
	{
		if (NULL == wWindow)
			printf("unable to create window. SDL error: %s\n", SDL_GetError());
	};
	~Window()
	{
		SDL_DestroyWindow(wWindow);
		wWindow = NULL;
	}
	bool check()
	{
		if (wWindow == NULL)
		{
			printf("Could not initialize Window. SDL Error: %s\n", SDL_GetError());
			return false;
		}
		return true;
	}
	void setWindow(SDL_Window* newWindow)
	{
		if (wWindow == newWindow)
			printf("window did not change.\n");
		else
			wWindow = newWindow;
	}
	SDL_Window* getWindow()
	{
		return wWindow;
	}
	SDL_Window** getWindowPointer()
	{
		return &wWindow;
	}
	bool Update()
	{
		if(SDL_UpdateWindowSurface(wWindow) < 0)
			return false;
		return true;
	}
private:
	SDL_Window* wWindow;
};

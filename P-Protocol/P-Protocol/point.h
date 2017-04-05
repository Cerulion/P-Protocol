#pragma once

#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

class point
{
public:
	point(int x, int y)
	{
		setPoint(x, y);
	};
	point()
	{
		setPoint(0, 0);
	}
	void setPoint(int x, int y)
	{
		pPoint.x = x;
		pPoint.y = y;
	}
	SDL_Point* getPoint()
	{
		return &pPoint;
	}
protected:
	SDL_Point pPoint;
};
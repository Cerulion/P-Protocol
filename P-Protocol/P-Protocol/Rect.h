#pragma once

#include <SDL.h>
#include "point.h"

class Rect
{
public:
	Rect(int x, int y, int w, int h)
	{
		setRect(x, y, w, h);
	}
	Rect(int w, int h)
	{
		setRect(0, 0, w, h);
	}
	Rect(point* upperLeft, int w, int h)
	{
		setRect(upperLeft);
		rect.w = w;
		rect.h = h;
	}
	Rect(point* upperLeft, point* downRight)
	{
		setRect(upperLeft, downRight);
	}
	Rect()
	{
		setRect(0, 0, 1, 1);
	}
	void setRect(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	void setRect(point* pPoint)
	{
		setRect(pPoint->getPoint()->x, pPoint->getPoint()->y);
	}
	void setRect(SDL_Rect* newRect)
	{
		rect = *newRect;
	}
	void setRect(point* upperLeft, point* downRight)
	{
		setRect(upperLeft);
		rect.w = downRight->getPoint()->x - upperLeft->getPoint()->x;
		rect.h = downRight->getPoint()->y - upperLeft->getPoint()->y;
	}
	void setRect(int x, int y, int w, int h)
	{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}
	SDL_Rect* getRect()
	{
		return &rect;
	}
	point* getUpperLeft()
	{
		return &point(rect.x, rect.y);
	}
	point* getDownRight()
	{
		return &point(rect.x + rect.w, rect.y + rect.h);
	}
private:
	SDL_Rect rect;
};
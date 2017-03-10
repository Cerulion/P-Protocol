#pragma once

#include <SDL.h>

class color
{
public:
	color(Uint8 nr, Uint8 ng, Uint8 nb, Uint8 na)
		:
		r(nr),
		g(ng),
		b(nb),
		a(na)
	{
		sdlColor = { r, g, b, a };
	};
	SDL_Color* getColor()
	{
		return &sdlColor;
	}
	void setColor(SDL_Color newColor)
	{
		sdlColor = newColor;
		//TODO make this stuff right
	}
	void setColor(color* newColor)
	{
		sdlColor = *newColor->getColor();
		r = sdlColor.r;
		g = sdlColor.g;
		b = sdlColor.b;
		a = sdlColor.a;
	}
	void modulateColor(int dr, int dg, int db, int da)
	{
		sdlColor = { r + dr, g + dg, b + db, a + da };
		r += dr;
		g += dg;
		b += db;
		a += da;
	}
	template <typename T>
	void modulateHeatColor(T dH)
	{
		setHeatColor(r + (int)(dH));
	}
	template <typename T>
	void setHeatColor(T H)
	{
		if (H > 255)
		{
			r = 255;
			b = -255;
			sdlColor = { 255, 0, -255, 0 };
			return;
		}
		else if (H < 0)
		{
			r = 0;
			b = 0;
			sdlColor = { 0, 0, 0, 0 };
			return;
		}

		r = (int)H;
		b = -(int)H;

		sdlColor = { r, 0, b, 0 };
	}
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
private:
	SDL_Color sdlColor;
};
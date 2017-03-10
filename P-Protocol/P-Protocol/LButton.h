#pragma once

#include "point.h"
#include "LButtonSprite.h"
#include "Rect.h"
#include "Texture.h"
#include "render.h"
#include "constants.h"

class LButton
{
public:
	LButton(int x, int y, int w, int h, const char* origin, Render* mRender)
		:
		pRender(mRender),
		mTexture(Texture(origin, mRender)),
		pTexture(nullptr)
	{
		setPosition(x, y, w, h);
		mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	}
	LButton(int x, int y, int w, int h, const char* text, color someColorlol, Render* mRender)
		:
		pRender(mRender),
		mTexture(Texture(text, someColorlol,mRender))
	{
		mPosRect.setRect(x, y, w, h);
		mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	}
	LButton()
		:
		pTexture(nullptr),
		mTexture(NULL)
	{
		setPosition(0, 0, 0, 0);
		mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	}
	void setPosition(int x, int y,int w, int h)
	{
		mPosRect.setRect(x, y, w, h);
	}
	bool handleEvent(SDL_Event* e)
	{
		//check for mouse event
		if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_FINGERDOWN)
		{
			int x, y;

			SDL_GetMouseState(&x, &y);

			if (e->type == SDL_FINGERDOWN)
			{
				x = e->tfinger.x * SCREEN_WIDTH;
				y = e->tfinger.y * SCREEN_HEIGHT;
			}

			bool inside = false;
			if (x > mPosRect.getRect()->x)
			{
				if (y > mPosRect.getRect()->y)
				{
					if (y < mPosRect.getRect()->y + mPosRect.getRect()->h)
					{
						if (x < mPosRect.getRect()->x + mPosRect.getRect()->w)
						{
							inside = true;
						}
					}
				}
			}

			if (!inside)
			{
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
			}
			else
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
					return true;
					break;
				case SDL_MOUSEBUTTONUP:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
					break;
				case SDL_FINGERDOWN:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
					return true;
					break;
				}
			}
		}
		return false;
	}
	void update()
	{
		if (!(mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION))
		{
			SDL_SetRenderDrawColor(pRender->getRenderer(), 255, 255, 255, 0);
			SDL_RenderDrawRect(pRender->getRenderer(), mPosRect.getRect());
			SDL_SetRenderDrawColor(pRender->getRenderer(), 0, 0, 0, 0);
		}

		mTexture.update(&point(mPosRect.getRect()->x, mPosRect.getRect()->y));
	}
private:
	//point mPosition;
	Rect mPosRect;
	LButtonSprite mCurrentSprite;
	Texture mTexture;
	Texture* pTexture;
	Render* pRender;
};
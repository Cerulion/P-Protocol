#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "render.h"
#include "Rect.h"
#include "color.h"
#include "point.h"

//creating global font, TODO good idea?
TTF_Font* pFont = NULL;

class Texture
{
public:
	Texture()
		:
		pTexture(NULL)
	{};
	Texture(const char* origin, Render* Renderer)
		:
		pTexture(NULL),
		pRender(Renderer->getRenderer())
	{
		loadTexture(origin, Renderer);
	};	
	Texture(Render* Renderer)
		:
		pTexture(NULL),
		pRender(Renderer->getRenderer())
	{};
	Texture(const char* text, color textColor, Render* Renderer)
		:
		pTexture(NULL),
		pRender(Renderer->getRenderer())
	{
		loadText(text, textColor);
	}
	Texture(const char* origin, Render* Renderer, color colorKey)
		:
		pTexture(NULL),
		pRender(Renderer->getRenderer())
	{
		loadTexture(origin, Renderer, colorKey);
	}
	~Texture()
	{
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
	}
	SDL_Texture* getTexture()
	{
		return pTexture;
	}
	void free()
	{
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
	}
	bool loadTexture(const char* origin, Render* Renderer)
	{
		SDL_Surface* temp = IMG_Load(origin);

		if (NULL == temp)
		{
			printf("Unable to load %s. SDL_image error: %s.", origin, IMG_GetError());
			return false;
		}
		else
		{
			Format.setRect(0, 0, temp->w, temp->h);

			pTexture = SDL_CreateTextureFromSurface(Renderer->getRenderer(), temp);

			if (NULL == pTexture)
			{
				printf("unable to render Texture %s. SDL_image error: %s.", origin, IMG_GetError());
				return false;
			}

			SDL_FreeSurface(temp);

			return true;
		}
	}
	bool loadTexture(const char* origin, Render* Renderer, color colorKey)
	{
		SDL_Surface* temp = IMG_Load(origin);

		if (NULL == temp)
		{
			printf("Unable to load %s. SDL_image error: %s.", origin, IMG_GetError());
			return false;
		}
		else
		{
			SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, colorKey.r, colorKey.g, colorKey.b));

			Format.setRect(0, 0, temp->w, temp->h);

			pTexture = SDL_CreateTextureFromSurface(Renderer->getRenderer(), temp);

			if (NULL == pTexture)
			{
				printf("unable to render Texture %s. SDL_image error: %s.", origin, IMG_GetError());
				return false;
			}

			SDL_FreeSurface(temp);

			return true;
		}
	}
	bool loadTexture(const char* origin)
	{
		SDL_Surface* temp = IMG_Load(origin);

		if (NULL == temp)
		{
			printf("Unable to load %s. SDL_image error: %s.", origin, IMG_GetError());
			return false;
		}

		else
		{
			pTexture = SDL_CreateTextureFromSurface(pRender, temp);

			if (NULL == pTexture)
			{
				printf("unable to render Texture %s. SDL_image error: %s.", origin, IMG_GetError());
				return false;
			}
			Format.setRect(0, 0, temp->w, temp->h);

			SDL_FreeSurface(temp);

			return true;
		}
	}
	bool loadText(const char* text, color textColor)
	{
		//TODO free every surface before loading a new one
		free();

		pFont = TTF_OpenFont("lazy.ttf", 40);

		SDL_Surface* textSurface = TTF_RenderText_Solid(pFont, text, *textColor.getColor());

		if (NULL == textSurface)
			printf("Unable to create text surface: %s. SDL_ttf error: %s\n", text, TTF_GetError());

		else
		{
			//render this
			pTexture = SDL_CreateTextureFromSurface(pRender, textSurface);

			if (NULL == pTexture)
				printf("Unable to render text surface to Texture: %s. SDL error: %s\n", text, SDL_GetError());

			else
			{
				Format.setRect(0, 0, textSurface->w, textSurface->h);
			}

			SDL_FreeSurface(textSurface);
		}
		return pTexture != NULL;
	}
	void setColor(color* newColor)
	{
		SDL_SetTextureColorMod(pTexture, newColor->r, newColor->g, newColor->b);
	}
	void setBlending(SDL_BlendMode blending)
	{
		SDL_SetTextureBlendMode(pTexture, blending);
	}
	void setAlpha(Uint8 alpha)
	{
		SDL_SetTextureAlphaMod(pTexture, alpha);
	}
	void setTexture(SDL_Texture* newTexture)
	{
		pTexture = newTexture;
	}
	//TODO make this right
	void update(Rect* dst, Rect* clip = NULL)
	{
		SDL_RenderCopy(pRender, pTexture, clip == NULL ? NULL : clip->getRect(), dst == NULL ? NULL : dst->getRect());
	}
	void update(point* position)
	{
		SDL_RenderCopy(pRender, pTexture, NULL, Rect(position, Format.getRect()->w, Format.getRect()->h).getRect());
	}
	void updateFormat()
	{
		SDL_RenderCopy(pRender, pTexture, NULL, Format.getRect());
	}
	void updateS(point* position, Rect* clip = NULL, double angle = 0.0, point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		SDL_RenderCopyEx(pRender, pTexture, clip == NULL ? NULL : clip->getRect(), Format.getRect(), angle, center == NULL ? NULL : center->getPoint(), flip);
	}
	void setRenderer(Render* newRender)
	{
		pRender = newRender->getRenderer();
	}
	SDL_Renderer* getRenderer()
	{
		return pRender;
	}
	Render* getRenderer2()
	{
		//dont forget to delete your stuff!
		Render* temp = new Render(pRender);
		return temp;
	}
	SDL_Rect* getFormat()
	{
		return Format.getRect();
	}
private:
	SDL_Texture* pTexture;
	SDL_Renderer* pRender;
	Rect Format;
};

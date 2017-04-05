#pragma once

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif

#include "Render.h"
#include "SDLrunner.h"
#include "texture.h"
#include "window.h"
#include "surface.h"
#include "LButton.h"
#include "LButtonSprite.h"
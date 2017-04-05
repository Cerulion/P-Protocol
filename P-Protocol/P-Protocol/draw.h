#pragma once

#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#include <SDL_image.h>
#include "render.h"
#include "SDLrunner.h"
#include "texture.h"
#include "window.h"
#include "surface.h"
#include "LButton.h"
#include "LButtonSprite.h"
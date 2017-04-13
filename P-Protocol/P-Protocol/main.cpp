#include <stdio.h>

#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include "draw.h"
#include "States.h"
#include "constants.h"

#include "Transmitter.h"

#define INPUT_PIN RPI_GPIO_P1_15
#define OUTPUT_PIN RPI_GPIO_P1_11

#define PULSE 25

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	srand(time(NULL));
#endif
	
	SDL runner;
	Window wdw("hallo", SCREEN_WIDTH, SCREEN_HEIGHT);
	Surface frs(&wdw);
	Render ren(&frs);

	if (frs.getSurface() == NULL)
		return 1;

	MenueState menue(&ren, &runner, 0);
	ArcState* currState = &menue;

	while (!runner.q())
	{
		while (SDL_PollEvent(runner.getEvent()) != 0)
		{
			if (runner.getEvent()->type == SDL_QUIT)
				runner.q(true);

			//keyboard
			else if (runner.getEvent()->type == SDL_KEYDOWN)
			{
				switch (runner.getEvent()->key.keysym.sym)
				{
				case SDLK_q:
					runner.q(true);
					break;
				default:
					break;
				}
			}
		}

		ren.clear();

		currState->executeCode();
		currState->draw();

		SDL_UpdateWindowSurface(wdw.getWindow());

		ren.update();
	}

	/*
	Transmitter hans = Transmitter(INPUT_PIN, OUTPUT_PIN, PULSE);

	while (1)
	{
		hans.sendInt(170);
		hans.sendInt(178);
	}*/


#ifdef _WIN32
	//while (getchar() != 'q');
#endif
	
	return 0;
}
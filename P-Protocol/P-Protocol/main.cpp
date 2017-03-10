#include <stdio.h>
#include <SDL.h>

#include "draw.h"
#include "States.h"

#include "Transmitter.h"

#define INPUT_PIN RPI_GPIO_P1_15
#define OUTPUT_PIN RPI_GPIO_P1_11

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define PULSE 25

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	srand(time(NULL));
#endif
	
	SDL runner;
	Window wdw("hallo", SCREEN_WIDTH, SCREEN_HEIGHT);
	Render ren(&wdw);
	Surface frs(&wdw);

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
				default:
					break;
				}
			}
		}

		ren.clear();

		currState->executeCode();
		currState->draw();

		ren.update();
	}


	Transmitter hans = Transmitter(INPUT_PIN, OUTPUT_PIN, PULSE);

	/*while (1)
	{
		hans.sendInt(170);
		hans.sendInt(178);
	}*/


#ifdef _WIN32
	while (getchar() != 'q');
#endif
	
	return 0;
}
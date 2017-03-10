#pragma once

#include "States.h"
#include "draw.h"
#include "constants.h"

class ExState : public ArcState
{
public:
	ExState(Render* Renderer, SDL* ev, int call)
		:
		pRender(Renderer),
		e(ev),
		c(call),
		progress(0),
		restart(LButton(SCREEN_WIDTH - 200, 50, 200, 80, "Restart", color(255, 255, 255, 0), pRender)),
		plus(LButton(SCREEN_WIDTH - 200, 130, 200, 80, "Plus", color(255, 255, 255, 0), pRender)),
		minus(LButton(SCREEN_WIDTH - 200, 210, 200, 80, "minus", color(255, 255, 255, 0), pRender)),
		reset(LButton(SCREEN_WIDTH - 200, 290, 200, 80, "reset", color(255, 255, 255, 0), pRender)),
		quit(LButton(SCREEN_WIDTH - 200, 370, 200, 80, "quit", color(255, 255, 255, 0), pRender))
	{};
	virtual void executeCode() override
	{
		/*if (restart.handleEvent(e->getEvent()))
		{
			hah.setDefault();
		}
		if (minus.handleEvent(e->getEvent()))
		{
			hah.modulatePerc(-0.01f);
		}
		if (plus.handleEvent(e->getEvent()))
		{
			hah.modulatePerc(0.01f);
		}
		if (reset.handleEvent(e->getEvent()))
		{
			hah.resetExceptions();
		}
		hah.handleEvent(e->getEvent());
		hah.progress();
		if (quit.handleEvent(e->getEvent()))
		{

		}*/
		//SDL_Delay(10);
	}
	virtual void draw() override
	{
		restart.update();
		minus.update();
		plus.update();
		reset.update();
	}
private:
	Render* pRender;
	SDL* e;
	int c;

	int progress;

	LButton restart;
	LButton plus;
	LButton minus;
	LButton reset;
	LButton quit;
};
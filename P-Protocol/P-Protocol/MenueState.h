#pragma once

#include "States.h"
#include "draw.h"

class MenueState : public ArcState
{
public:
	MenueState(Render* Renderer, SDL* ev, int call)
		:
		pRender(Renderer),
		e(ev),
		c(call),
		NextState(STATE_MENUE),
		forward(LButton(20, 20, 20, 10, "Hallo", color(255, 255, 255, 0), pRender))
	{};
	virtual void executeCode() override
	{
		if (forward.handleEvent(e->getEvent()))
		{
			printf("button has been pressed\n");
			NextState = STATE_EX;
		}
		
	}
	virtual void draw() override
	{
		forward.update();
	}
	virtual States getNextState() override
	{
		return NextState;
	}
private:
	Render* pRender;
	SDL* e;
	int c;

	States NextState;

	LButton forward;
};
#pragma once

enum States
{
	STATE_MENUE = 0,
	STATE_EX,
	STATE_TOTAL
};

class ArcState
{
public:
	virtual void executeCode(){}
	virtual void draw(){}
	virtual States getNextState(){ return STATE_MENUE; }

private:
	ArcState* currState;
};
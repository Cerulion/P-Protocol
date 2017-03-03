#pragma once

#ifdef _DEBUG
	#include "bcm2835.h"
	#define RPI_GPIO_P1_15 22
	#define BCM2835_GPIO_FSEL_INPT 0x00
	#define BCM2835_GPIO_FSEL_OUTP 0x01
	#include <time.h>
#else
	#include <bcm2835.h>
#endif

#define INP 0
#define OUP 1


class Transmitter
{
public:
	Transmitter(int pin, int mode)
		:
		pin(pin),
		mode(mode)
	{
		if (!alr_init)
		{
			init_err = bcm2835_init();
			alr_init = true;
		}
		if (!init_err)
		{
			bcm2835_gpio_fsel(pin, mode == INP ? BCM2835_GPIO_FSEL_INPT : BCM2835_GPIO_FSEL_OUTP);
		}

		amount++;
	}
	~Transmitter()
	{
		if (--amount == 0)
		{
			bcm2835_close();
			alr_init = false;
			init_err = false;
		}
	}
	int read()
	{
		return bcm2835_gpio_lev(pin);
	}
	static void sleep(size_t time)
	{
		bcm2835_delay(time);
	}

private:
	static bool init_err;
	static bool alr_init;
	static size_t amount;
	int pin;
	int mode;
};

size_t Transmitter::amount = 0;
bool Transmitter::init_err = false;
bool Transmitter::alr_init = false;
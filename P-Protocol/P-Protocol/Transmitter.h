#pragma once

#ifdef _DEBUG
	#include "bcm2835.h"
	#include <time.h>
	#define RPI_GPIO_P1_15 22
	#define RPI_GPIO_P1_11 17
	#define BCM2835_GPIO_FSEL_INPT 0x00
	#define BCM2835_GPIO_FSEL_OUTP 0x01
	#define HIGH 1
	#define LOW 0
#else
	#include <bcm2835.h>
#endif

#define INP 0
#define OUP 1
#define NOP -1

//do i really need these?
#define BIT7 (1 << 7)
#define BIT6 (1 << 6)
#define BIT5 (1 << 5)
#define BIT4 (1 << 4)
#define BIT3 (1 << 3)
#define BIT2 (1 << 2)
#define BIT1 (1 << 1)
#define BIT0 (1 << 0)

class Transmitter
{
public:
	Transmitter(int in_pin, int out_pin, int pulse)
		:
		in_pin(in_pin),
		out_pin(out_pin),
		pulse(pulse)
	{
		if (!alr_init)
		{
			init_succ = bcm2835_init();
			alr_init = true;
		}
		if (init_succ)
		{
			if (in_pin != NOP)
				bcm2835_gpio_fsel(in_pin, BCM2835_GPIO_FSEL_INPT);
			if (out_pin != NOP)
				bcm2835_gpio_fsel(out_pin, BCM2835_GPIO_FSEL_OUTP);

			amount++;
		}

		for (int i = 1, k = 0; k < 8; i *= 2, k++)
			bitMask[k] = i;
	}
	~Transmitter()
	{
		if (--amount == 0)
		{
			bcm2835_close();
			alr_init = false;
			init_succ = false;
		}
	}
	inline int read()
	{
		return bcm2835_gpio_lev(in_pin);
	}
	inline void write(int state)
	{
		bcm2835_gpio_write(out_pin, state); //check if every positive number counts as high
	}
	inline static void sleep(size_t time)
	{
		bcm2835_delay(time);
	}

	inline void sendInt(int i) //i should be 1 byte
	{
		if (i < 0 || i > 255)
			return;

		for (int k = 7; k >= 0; k--) // send it backwards to receive it in the right order
		{
			write(i & bitMask[k]);
			sleep(pulse);
		}
		//now send inverse signal
		for (int k = 7; k >= 0; k--)
		{
			write(!(i & bitMask[k]));
			sleep(pulse);
		}
	}
	inline int recvInt()
	{
		int temp = 0;
		int check = 0;

		for (int k = 0; k < 8; k++)
		{
			temp <<= 1;
			temp |= read();
			sleep(pulse);
		}
		for (int k = 0; k < 8; k++)
		{
			check <<= 1;
			check |= read();
			sleep(pulse);
		}

		if ((temp ^ check) == 255)
			return temp;
		return -1;
	}
	//TODO sync function


private:
	static bool init_succ;
	static bool alr_init;
	static size_t amount;
	int in_pin;
	int out_pin;
	int pulse;

	int bitMask[8];
};

size_t Transmitter::amount = 0;
bool Transmitter::init_succ = false; //true if all cool, false otherwise
bool Transmitter::alr_init = false;
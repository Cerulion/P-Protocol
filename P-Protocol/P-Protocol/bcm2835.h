//only a dummy file

#pragma once
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#include <windows.h>
#endif

bool bcm2835_init()
{
	printf("init\n");
	return true;
}
void bcm2835_close()
{
	printf("close\n");
	return;
}
void bcm2835_gpio_fsel(int a, int b)
{
	return;
}
int bcm2835_gpio_lev(int a)
{
	if (static_cast<double>(rand()) / static_cast<double>(RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}
void bcm2835_delay(int a)
{
	Sleep(a);
}
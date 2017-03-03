#include <stdio.h>

#include "Transmitter.h"

#define INPUT_PIN BCM2835_GPIO_FSEL_INPT


int main()
{
#ifdef _DEBUG
	srand(time(NULL));
#endif

	Transmitter hans = Transmitter(INPUT_PIN, INP);

	for (int i = 0; i < 20; i++)
	{
		printf("%d\n", hans.read());
		Transmitter::sleep(25);
	}

	while (getchar() != 'q');
	return 0;
}
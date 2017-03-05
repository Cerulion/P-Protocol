#include <stdio.h>

#include "Transmitter.h"

#define INPUT_PIN RPI_GPIO_P1_15
#define OUTPUT_PIN RPI_GPIO_P1_11

int main()
{
#ifdef _DEBUG
	srand(time(NULL));
#endif

	Transmitter hans = Transmitter(INPUT_PIN, OUTPUT_PIN, 25);

	int test = 1;
	test <<= 1;
	printf("%d\n", 1 << 1);
	hans.sendInt(5);


	for (int i = 0; i < 20; i++)
	{
		printf("%d\n", hans.read());
		Transmitter::sleep(25);
	}

#ifdef _WIN32
	while (getchar() != 'q');
#endif
	
	return 0;
}
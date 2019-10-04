#include <DMAParallelPort.hpp>
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

extern "C" {
int app_main();
}

#define BUFFERLENGTH 100

int app_main() {
	uint16_t buffer[BUFFERLENGTH];
	// This buffer will be written to the output port, one element at the time, at the frequency of the trigger timer
	for (int i = 0; i < BUFFERLENGTH / 2; i++) {
		buffer[i] = 0xff00;
	}
	for (int i = BUFFERLENGTH / 2; i < BUFFERLENGTH; i++) {
		buffer[i] = 0x00ff;
	}

	// Important: Enable the port clock for the output port manually
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef init = { 0 };
	init.Pin = GPIO_PIN_All;
	init.Mode = GPIO_MODE_OUTPUT_PP;
	init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;

	DMAParallelPort port(
			&buffer[0],
			BUFFERLENGTH,
			*GPIOB,
			init,
			htim6,
			hdma_tim6_up);

	while (1) { }
}

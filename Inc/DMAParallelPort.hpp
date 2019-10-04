/***********************  I n c l u d e  -  F i l e  ************************/
/*!
 *  \class    DMAParallelPort
 *  \author   Rafael.Bachmann@duagon.de
 *  \date     2019-04-10
 *
 ****************************************************************************/

#ifndef DMA_PARALLEL_PORT_H
#define DMA_PARALLEL_PORT_H

#include <cstddef>
#include <cstdint>

#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_tim.h"
#include "stm32g4xx_hal_dma.h"

class DMAPDMAParallelPort;

extern "C" {
void MX_DMA_Init(void);
void MX_TIM6_Init(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);
}

class DMAParallelPort {
public:
	DMAParallelPort(
			uint16_t buffer[],
			size_t bufferLength,
			GPIO_TypeDef& port,
			GPIO_InitTypeDef& pin_config,
			TIM_HandleTypeDef& timer_handle,
			DMA_HandleTypeDef& timer_dma_update_handle);

	~DMAParallelPort() {};

private:
	uint16_t *buffer;
	size_t bufferLength = 0;

	GPIO_TypeDef& port;
	GPIO_InitTypeDef pin_config = { 0 };
	TIM_HandleTypeDef& timer_handle;
	DMA_HandleTypeDef& timer_dma_update_handle;
};

#endif // DMA_PARALLEL_PORT_H

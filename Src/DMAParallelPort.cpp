/***********************  P r o g r a m  -  M o d u l e  ********************/
/*!
 *  \class    DMAParallelPort
 *  \author   Rafael.Bachmann@duagon.de
 *  \date     2019-04-10
 *
 ****************************************************************************/

#include <DMAParallelPort.hpp>

DMAParallelPort::DMAParallelPort(
        uint16_t *buffer,
        size_t bufferLength,
        GPIO_TypeDef& port,
        GPIO_InitTypeDef& pin_config,
        TIM_HandleTypeDef& timer_handle,
        DMA_HandleTypeDef& timer_dma_update_handle) :
		    buffer(buffer),
			bufferLength(bufferLength),
            port(port),
            pin_config(pin_config),
            timer_handle(timer_handle),
            timer_dma_update_handle(timer_dma_update_handle)
{
    if ((GPIO_PIN_MASK & pin_config.Pin) == 0)
    {
        /* No pins for output */
        return;
    }

    // TODO make sure clock for gpio port was initialized

    HAL_GPIO_Init(&port, &pin_config);

    MX_DMA_Init();
    MX_TIM6_Init();

    HAL_DMA_Start(
            &timer_dma_update_handle,
            (uint32_t) buffer,
            (uint32_t) &(port.ODR),
            bufferLength);
    HAL_TIM_Base_Start(&timer_handle);
    __HAL_TIM_ENABLE_DMA(&timer_handle, TIM_DMA_UPDATE);
}

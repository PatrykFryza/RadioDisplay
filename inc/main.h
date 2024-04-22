/*
 * main.h
 *
 *  Created on: Apr 11, 2024
 *      Author: patry
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f4xx.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_i2c.h"
#include "stm32f4xx_ll_spi.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32f4_timer_properties.h"

#define DISP_IRQ_GPIO_PORT GPIOA
#define DISP_IRQ_PIN GPIO_PIN_15

#define NRF24_CSN_GPIO_PORT GPIOC
#define NRF24_CSN_PIN GPIO_PIN_5

#define NRF24_CE_GPIO_PORT GPIOC
#define NRF24_CE_PIN GPIO_PIN_4

#define NRF24_IRQ_GPIO_PORT GPIOB
#define NRF24_IRQ_PIN GPIO_PIN_0

#define DUMMY_BYTE ((uint8_t)0x00)

#endif /* INC_MAIN_H_ */

/*
 * init.c
 *
 *  Created on: Apr 14, 2024
 *      Author: patry
 */
#include "init.h"

void SystemClock_Config(void){
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_5);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_PWR_DisableOverDriveMode();
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

  while(LL_RCC_HSI_IsReady() != 1);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 168, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();

  while(LL_RCC_PLL_IsReady() != 1);
  while (LL_PWR_IsActiveFlag_VOS() == 0);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);
  LL_Init1msTick(168000000);
  LL_SetSystemCoreClock(168000000);
  LL_RCC_SetTIMPrescaler(LL_RCC_TIM_PRESCALER_TWICE);
}

void I2C3_init(void){
 LL_I2C_InitTypeDef I2C_InitStruct = {0};
 LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

 LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
 LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
 /**I2C3 GPIO Configuration
 PC9   ------> I2C3_SDA
 PA8   ------> I2C3_SCL
 */
 GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
 GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
 GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
 GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
 GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
 GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
 LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

 GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
 GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
 GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
 GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
 GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
 GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
 LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3);

 LL_I2C_DisableOwnAddress2(I2C3);
 LL_I2C_DisableGeneralCall(I2C3);
 LL_I2C_EnableClockStretching(I2C3);
 I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
 I2C_InitStruct.ClockSpeed = 100000;
 I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;
 I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
 I2C_InitStruct.DigitalFilter = 0;
 I2C_InitStruct.OwnAddress1 = 0;
 I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
 I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
 LL_I2C_Init(I2C3, &I2C_InitStruct);
 LL_I2C_SetOwnAddress2(I2C3, 0);
}

void SPI1_init(void){
  LL_SPI_InitTypeDef SPI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**SPI1 GPIO Configuration
  PA5   ------> SPI1_SCK
  PA6   ------> SPI1_MISO
  PA7   ------> SPI1_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV32;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 10;
  LL_SPI_Init(SPI1, &SPI_InitStruct);
  LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_Enable(SPI1);
}

void GPIO_init(void){
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_ResetOutputPin(GPIOC, NRF24_CE_PIN|NRF24_CSN_PIN);

  GPIO_InitStruct.Pin = NRF24_CE_PIN|NRF24_CSN_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE0);
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
	LL_EXTI_Init(&EXTI_InitStruct);

	LL_GPIO_SetPinPull(NRF24_IRQ_GPIO_PORT, NRF24_IRQ_PIN, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinMode(NRF24_IRQ_GPIO_PORT, NRF24_IRQ_PIN, LL_GPIO_MODE_INPUT);
	NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(EXTI0_IRQn);


	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE15);
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_15;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
	LL_EXTI_Init(&EXTI_InitStruct);

	LL_GPIO_SetPinPull(DISP_IRQ_GPIO_PORT, DISP_IRQ_PIN, LL_GPIO_PULL_UP);
	LL_GPIO_SetPinMode(DISP_IRQ_GPIO_PORT, DISP_IRQ_PIN, LL_GPIO_MODE_INPUT);

	NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}

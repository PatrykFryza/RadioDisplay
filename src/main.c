/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"
#include "init.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "nRF24.h"

uint8_t rf_receive_flag = 0;
uint8_t disp_touch_flag = 0;

int main(void){
	SystemClock_Config();
	//Create TouchData struct
	TM_STMPE811_TouchData touchData;
	//Initialize LCD
	TM_ILI9341_Init(); //240 - x; 320 - y
	//Rotate LCD
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
	GPIO_init();
	SPI1_init();
	I2C3_init();
	if(TM_STMPE811_Init() != TM_STMPE811_State_Ok){
			TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
			while (1);
	}
	touchData.orientation = TM_ILI9341_Orientation_Portrait_2;
	TM_ILI9341_DrawFilledRectangle(0, 260, 119, 319, ILI9341_COLOR_RED);
	TM_ILI9341_DrawFilledRectangle(120, 260, 239, 319, ILI9341_COLOR_BLUE);

	nRF24_Init();
//	nRF24_SetRXAddress(0, (uint8_t*)"Nad");
//	nRF24_SetTXAddress((uint8_t*)"Odb");

	nRF24_SetRXAddress(0, (uint8_t*)"Odb");
	nRF24_SetTXAddress((uint8_t*)"Nad");
	nRF24_RX_Mode();



	uint8_t press_flag = 0;
	uint16_t counter = 0;
	uint8_t line = 3;
	while(1){
		if (disp_touch_flag){
			TM_STMPE811_ReadTouch(&touchData);
			if(touchData.x < 120 && touchData.y > 260){
				TM_ILI9341_Puts(0, 10, "Sending \"Hello world\"", &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
				press_flag = 1;
			}
			if(touchData.x > 120 && touchData.y > 260){
				TM_ILI9341_Puts(0, 10, "Sending Counter", &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
				++counter;
				press_flag = 2;
			}
		}
		if(press_flag == 1){
			uint8_t message[] = "Hello World";
			nRF24_SendPacket(message, 11);
			press_flag = 0;
			LL_mDelay(300);
			clear_interrupt(&disp_touch_flag);
			TM_ILI9341_Puts(0, 10, "Sending \"Hello world\"", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLACK);
		}
		else if(press_flag == 2){
			uint8_t message[20] = {0};
			uint8_t length = sprintf((char*)message, "Counter: %d", counter);
			nRF24_SendPacket(message, length);
			press_flag = 0;
			LL_mDelay(300);
			clear_interrupt(&disp_touch_flag);
			TM_ILI9341_Puts(0, 10, "Sending \"Hello world\"", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLACK);
		}
		if(line > 22)
			line = 3;
		if(rf_receive_flag){
			uint8_t Nrf24_Message[15] = {0};
			uint8_t length = 0;
			rf_receive_flag = 0;
			nRF24_IRQ_Read();
			do{
				nRF24_ReadRXPaylaod(Nrf24_Message, &length);
				TM_ILI9341_Puts(0, 11*line, "              ", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLACK);
				TM_ILI9341_Puts(0, 11*line, (char*)Nrf24_Message, &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
				++line;
			}while(!nRF24_IsRxEmpty());
		}
	}
}

void EXTI0_IRQHandler(void){
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) != RESET){
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
		nRF24_IRQ_Handler();
		rf_receive_flag = 1;
	}
}

void EXTI15_10_IRQHandler(void){
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_15) != RESET){
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
    disp_touch_flag = 1;
  }
}

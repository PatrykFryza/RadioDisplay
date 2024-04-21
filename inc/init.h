/*
 * init.h
 *
 *  Created on: Apr 14, 2024
 *      Author: patry
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_

#include "main.h"

void SystemClock_Config(void);
void I2C3_init(void);
void SPI1_init(void);
void GPIO_init(void);

#endif /* INC_INIT_H_ */

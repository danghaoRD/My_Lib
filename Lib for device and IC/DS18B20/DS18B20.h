/*
 * DS18B20.h
 *
 *  Created on: Aug 14, 2021
 *      Author: DANG HAO
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include "main.h"

#define DS18B20_PORT GPIOA
#define DS18B20_PIN GPIO_PIN_1

#define WRITE_DS18_LOW_PIN 		HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);
#define WRITE_DS18_HIGHT_PIN	HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 1);

#define READ_DS18_PIN		    (HAL_GPIO_ReadPin (DS18B20_PORT, DS18B20_PIN))
extern TIM_HandleTypeDef htim1;
void delay_us (uint16_t us);
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t DS18B20_Start (void);
void DS18B20_Write (uint8_t data);
uint8_t DS18B20_Read (void);
uint16_t DS18B20_ReadTemp16(void);
#endif /* INC_DS18B20_H_ */

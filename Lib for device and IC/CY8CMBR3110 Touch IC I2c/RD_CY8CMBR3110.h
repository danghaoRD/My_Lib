/*
 * RD_CY8CMBR3110.h
 *
 *  Created on: Apr 9, 2021
 *      Author: dangv
 */

#ifndef 	INC_RD_CY8CMBR3110_H_
#define 	INC_RD_CY8CMBR3110_H_

#include 	"main.h"
#define 	I2C_ADD_CY8   				    (0x37<<1)
//#define 	SYSTEM_STATUS_CY8_REG			0x8A				// check config loaded
//#define		SENSOR_EN_CY8_REG				0x00				// active pin
//#define 	FSS_EN_CY8_REG					0x02				// flanking sensor Suppression
//#define 	SENSITIVITY0_CY8_REG			0x08				// sensitivities CS 0-1-2-3
//#define 	SENSITIVITY1_CY8_REG			0x0A				// sensitivities CS 4-5-6-7
//#define 	SENSITIVITY2_CY8_REG			0x08				// sensitivities CS 8-9-10-11
//#define 	SENSOR_DEBOUNCE_CY8_REG			0X1C				// Num off scan time 0->15			// defaul 3
//#define 	PROX_EN_CY8_REG					0x26				// select proximity or button only  // defaul button anh active low pass filter
//#define 	DEVICE_CFG0_CY8_REG				0x4D				// config filter
//#define 	DEVICE_CFG1_CY8_REG				0x4E				// config	System diagnostics
//#define 	DEVICE_CFG2_CY8_REG				0x4F				// config Reset , Automatic threshold
//#define 	DEVICE_CFG3_CY8_REG				0x50				// power supply
#define 	SYNC_COUNTER0_CY8_REG			0xB9				// check pin number press
#define 	SYNC_COUNTER1_CY8_REG			0xDB				// check pin number press
#define 	DIFFERENCE_COUNT_SENSOR0_CY8_REG 0xBA				// count signal sensor0; 16 bit
#define		BUTTON_STAT_CY8_REG				0xAA				// Button STT    touch/ no touch
#define		LATCHED_BUTTON_STAT_CY8_REG		0xAC				// the last time BUTTON_STAT_CY8_REG
#define 	CTRL_CMD_CY8_REG				0x86				//
#define 	CTRL_CMD_STATUS_CY8_REG			0x88
#define 	CTRL_CMD_ERR_CY8_REG			0x89
#define 	SIZE_OF_DATA_CONFIG			    128
I2C_HandleTypeDef hi2c2;

#define 	I2CWrite_CY8_DEF(Slave_Add,Reg_Add, Size, data)    HAL_I2C_Mem_Write(&hi2c2,Slave_Add,Reg_Add, 1 , data,Size,1000);
#define 	I2CRead_CY8_DEF(Slave_Add, Reg_Add, Size, data)	HAL_I2C_Mem_Read(&hi2c2, Slave_Add, Reg_Add, 1, data, Size, 1000);

/*-----------------------------------Value Config------------------------------------*/
#define		SENSOR_EN_L						0xE3			// active sensor 0-1-5-6-7
#define 	SENSOR_EN_H						0x01			// active sensor 8
#define 	FSS_EN_L						0x00
#define		FSS_EN_H						0x00
#define 	TOGGLE_EN_L						0x00
#define 	TOGGLE_EN_H						0x00
#define 	LED_ON_EN_L						0x00
#define 	LED_ON_EN_H						0X00
#define 	SENSITIVITY0					0x00
#define 	SENSITIVITY1					0x00
#define 	SENSITIVITY2					0x00
#define 	BASE_THRESHOLD0					0x80
#define 	BASE_THRESHOLD1					0x80
#define 	FINGER_THRESHOLD2				0x80
#define 	FINGER_THRESHOLD3				0x80
#define 	FINGER_THRESHOLD4				0x80
#define 	FINGER_THRESHOLD5				0x80
#define 	FINGER_THRESHOLD6				0x80
#define 	FINGER_THRESHOLD7				0x80
#define 	FINGER_THRESHOLD8				0x80
#define 	FINGER_THRESHOLD9				0x80
#define 	SENSOR_DEBOUNCE					0x03
#define 	BUTTON_HYS						0x0C
#define 	BUTTON_LBR						0x32
#define 	BUTTON_NNT						0x33
#define 	BUTTON_NT						0x33
#define 	PROX_EN							0x00
#define 	PROX_CFG						0x80
#define 	PROX_CFG2						0x05
#define 	PROX_TOUCH_TH0_L				0x00
#define 	PROX_TOUCH_TH0_H				0x02
#define 	PROX_TOUCH_TH1_L				0x00
#define 	PROX_TOUCH_TH1_H				0x02
#define 	PROX_RESOLUTION0				0x00
#define 	PROX_RESOLUTION1				0x00
#define 	PROX_HYS						0x05
#define 	PROX_LBR						0x32
#define 	PROX_NNT						0x14
#define 	PROX_NT							0x14
#define 	PROX_POSITIVE_TH0				0x1E
#define 	PROX_POSITIVE_TH1				0x1E
#define 	PROX_NEGATIVE_TH0				0x1E
#define 	PROX_NEGATIVE_TH1				0x1E
#define 	LED_ON_TIME						0x00
#define 	BUZZER_CFG						0x01
#define		BUZZER_ON_TIME					0x01
#define 	GPO_CFG							0x00
#define 	PWM_DUTYCYCLE_CFG0				0x0F
#define 	PWM_DUTYCYCLE_CFG1				0x0F
#define 	PWM_DUTYCYCLE_CFG2				0x0F
#define 	PWM_DUTYCYCLE_CFG3				0x0F
#define 	PWM_DUTYCYCLE_CFG4				0x0F
#define 	SPO_CFG							0x41								// set SPO 1 as host interrupt
#define 	DEVICE_CFG0						0x03
#define 	DEVICE_CFG1						0x01
#define 	DEVICE_CFG2						0x08
#define 	DEVICE_CFG3						0x00
#define 	I2C_ADDR						0x37
#define 	REFRESH_CTRL					0x06
#define 	STATE_TIMEOUT					0x0A
#define 	SCRATCHPAD0						0x00
#define 	SCRATCHPAD1						0x00
#define		CONFIG_CRC_L					0x01
#define 	CONFIG_CRC_H					0X00
/*-------------------------------------------------------------------------------------*/

/*-----------------------ADD_Register == local of Register_Config[x] -------------------------------------------*/
#define		SENSOR_EN_L_REG_CY8				0x00
#define 	SENSOR_EN_H_REG_CY8				0x01
#define 	FSS_EN_L_REG_CY8				0x02
#define		FSS_EN_H_REG_CY8				0x03
#define 	TOGGLE_EN_L_REG_CY8				0x04
#define 	TOGGLE_EN_H_REG_CY8				0x05
#define 	LED_ON_EN_L_REG_CY8				0x06
#define 	LED_ON_EN_H_REG_CY8				0X07
#define 	SENSITIVITY0_REG_CY8			0x08
#define 	SENSITIVITY1_REG_CY8			0x09
#define 	SENSITIVITY2_REG_CY8			0x0A
#define 	BASE_THRESHOLD0_REG_CY8			0x0C
#define 	BASE_THRESHOLD1_REG_CY8			0x0D
#define 	FINGER_THRESHOLD2_REG_CY8		0x0E
#define 	FINGER_THRESHOLD3_REG_CY8		0x0F
#define 	FINGER_THRESHOLD4_REG_CY8		0x10
#define 	FINGER_THRESHOLD5_REG_CY8		0x11
#define 	FINGER_THRESHOLD6_REG_CY8		0x12
#define 	FINGER_THRESHOLD7_REG_CY8		0x13
#define 	FINGER_THRESHOLD8_REG_CY8		0x14
#define 	FINGER_THRESHOLD9_REG_CY8		0x15
#define 	SENSOR_DEBOUNCE_REG_CY8			0x1C
#define 	BUTTON_HYS_REG_CY8				0x1D
#define 	BUTTON_LBR_REG_CY8				0x1F
#define 	BUTTON_NNT_REG_CY8				0x20
#define 	BUTTON_NT_REG_CY8				0x21
#define 	PROX_EN_REG_CY8					0x26
#define 	PROX_CFG_REG_CY8				0x27
#define 	PROX_CFG2_REG_CY8				0x28
#define 	PROX_TOUCH_TH0_L_REG_CY8		0x2A
#define 	PROX_TOUCH_TH0_H_REG_CY8		0x2B
#define 	PROX_TOUCH_TH1_L_REG_CY8		0x2C
#define 	PROX_TOUCH_TH1_H_REG_CY8		0x2D
#define 	PROX_RESOLUTION0_REG_CY8		0x2E
#define 	PROX_RESOLUTION1_REG_CY8		0x2F
#define 	PROX_HYS_REG_CY8				0x30
#define 	PROX_LBR_REG_CY8				0x32
#define 	PROX_NNT_REG_CY8				0x33
#define 	PROX_NT_REG_CY8					0x34
#define 	PROX_POSITIVE_TH0_REG_CY8		0x35
#define 	PROX_POSITIVE_TH1_REG_CY8		0x36
#define 	PROX_NEGATIVE_TH0_REG_CY8		0x39
#define 	PROX_NEGATIVE_TH1_REG_CY8		0x3A
#define 	LED_ON_TIME_REG_CY8				0x3D
#define 	BUZZER_CFG_REG_CY8				0x3E
#define		BUZZER_ON_TIME_REG_CY8			0x3F
#define 	GPO_CFG_REG_CY8					0x40
#define 	PWM_DUTYCYCLE_CFG0_REG_CY8		0x41
#define 	PWM_DUTYCYCLE_CFG1_REG_CY8		0x42
#define 	PWM_DUTYCYCLE_CFG2_REG_CY8		0x43
#define 	PWM_DUTYCYCLE_CFG3_REG_CY8		0x44
#define 	PWM_DUTYCYCLE_CFG4_REG_CY8		0x45
#define 	SPO_CFG_REG_CY8					0x4C
#define 	DEVICE_CFG0_REG_CY8				0x4D
#define 	DEVICE_CFG1_REG_CY8				0x4E
#define 	DEVICE_CFG2_REG_CY8				0x4F
#define 	DEVICE_CFG3_REG_CY8				0x50
#define 	I2C_ADDR_REG_CY8				0x51
#define 	REFRESH_CTRL_REG_CY8			0x52
#define 	STATE_TIMEOUT_REG_CY8			0x55
#define 	SCRATCHPAD0_REG_CY8				0x7A
#define 	SCRATCHPAD1_REG_CY8				0x7B
#define		CONFIG_CRC_L_REG_CY8			0x7E
#define 	CONFIG_CRC_H_REG_CY8			0X7F




uint8_t		I2C_Write_CY8(uint16_t Slave_Add, uint16_t Reg_Add, uint16_t size, uint16_t  DataWrite);
uint16_t 	I2C_Read_CY8(uint16_t SlaveAdd, uint16_t RegAdd, uint16_t Size );

void 		RD_CY8_Init(void);
uint16_t 	RD_CY8_Read_Sensor(uint8_t SensorID);


/*
1-11 - CS7
2-12 - CS8
3- 3 - CS0
4-9	 - CS5
5-10 - CS6
PW-4 - CS1
 */
#endif /* INC_RD_CY8CMBR3110_H_ */

/*
 * MFM_384.h
 *
 *  Created on: Sep 26, 2021
 *      Author: DANG HAO
 */

#ifndef INC_MFM_384_H_
#define INC_MFM_384_H_
#include "main.h"
UART_HandleTypeDef huart2;
#define MAX_LENG_SEND_RTU  100

#define CRC_Tx(Data, Leng) 	  		HAL_UART_Transmit(&huart2, Data, Leng, 100)

#define Modbus_TxEn_RxDis			HAL_GPIO_WritePin(Modbus_Ctr_GPIO_Port, Modbus_Ctr_Pin, GPIO_PIN_SET)      // Active Tx end inactive Rx
#define Modbus_RxEn_TxDis			HAL_GPIO_WritePin(Modbus_Ctr_GPIO_Port, Modbus_Ctr_Pin, GPIO_PIN_RESET)    // Active Rx end inactive Tx

#define V1_ADDR_DATA_4				0x02
#define V1_ADDR_DATA_3				0x03
#define V1_ADDR_DATA_2				0x00
#define V1_ADDR_DATA_1				0x01

#define I1_ADDR_DATA_4				0x22
#define I1_ADDR_DATA_3				0x23
#define I1_ADDR_DATA_2				0x20
#define I1_ADDR_DATA_1				0x21

#define Kw1_ADDR_DATA_4				0x32
#define Kw1_ADDR_DATA_3				0x33
#define Kw1_ADDR_DATA_2				0x30
#define Kw1_ADDR_DATA_1				0x31

#define Fre_ADDR_DATA_4				0x72
#define Fre_ADDR_DATA_3				0x73
#define Fre_ADDR_DATA_2				0x70
#define Fre_ADDR_DATA_1				0x71

#define Kwh_ADDR_DATA_4				0x76
#define Kwh_ADDR_DATA_3				0x77
#define Kwh_ADDR_DATA_2				0x74
#define Kwh_ADDR_DATA_1				0x75

#define LENG_OF_MODBUS_STR	207
typedef struct
{
	uint8_t Clear_Flag;
	uint8_t Leng_Rx;
	uint8_t ADDR_Slave;
	uint8_t Function;
	uint8_t Leng_Data;
	uint8_t Data[200];
	uint8_t CRC_16[2];
} ModBus_Rx_Struct;

typedef struct
{
	float Voltage_Phase1;
	float Current_Phase1;
	float Kw1;
	float Total_Kw;
	float Frequency;
	float Kwh;
}MFM_384_Data_Struct;

extern MFM_384_Data_Struct MFM_384_Data;
extern ModBus_Rx_Struct ModBus_Data_Rx;

void MFM_384_Converter(ModBus_Rx_Struct *Modbus_Rx, MFM_384_Data_Struct *MFM_Data);

void Modbus_RTU_Send(uint8_t ADDR_Slave, uint8_t Function, uint8_t* Data, uint16_t Data_Leng);

void Modbus_RTU_Recever(uint8_t Rx_In, ModBus_Rx_Struct *Modbus_Rx);
void Modbus_RTU_Rx_Clear(ModBus_Rx_Struct *Modbus_Rx);
uint16_t CRC16_2(unsigned char *buf, int len);
#endif /* INC_MFM_384_H_ */

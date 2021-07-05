/*
 * BG02_H10SG10.h
 *
 *  Created on: Jun 24, 2021
 *      Author: HAO_DANG
 */
/*
 * Lib for Module BG02_H10SG10 GPS. Get Paremeter auto when module send through UART 9600 bps.
 * example Data $GNRMC,000014.265,V,2059.44505,N,10548.48844,E,0.000,0.00,060180,,,N*51{0D}{0A}
 * need active UART on MCU and enable RX_Interrupt
 *
 * it's RingBuffer Lib
 */
#ifndef INC_BG02_H10SG10_H_
#define INC_BG02_H10SG10_H_

#include "main.h"
#include "string.h"

#define KEY_DATA $GNRMC

#define UART_GPS USART1

struct GPS_Para
{
	char str_Para_GPS[60];

	char Type_Para_GPS[8];

	uint16_t North_GPS_Degree;
	uint8_t  North_GPS_Minute;
	uint8_t  North_GPS_Second;
	float	 North_GPS_Float;

	uint16_t East_GPS_Degree;
	uint8_t  East_GPS_Minute;
	uint8_t  East_GPS_Second;
	float	 East_GPS_Float;

};
extern struct GPS_Para GPS_Value;

/*
 * Brief: receiver 1 byte data and auto check data
 * 			Transfer to data struc if find data GPS
 * 	Input: struct GPS_Para *GPS_Data   struc save data after transfer
 * 	char Data_In. 1 byte data raceiver from source Ring Buff GPS data
 */
void BG02_Receive_UART(struct GPS_Para *GPS_Data, char Data_In);

// clear struct  data (pointer struct GPS)
void BG02_Clear_Str_Data(struct GPS_Para *GPS_Data);

// transfer data from string(pointer struct GPS) to int degree and float GPS signal.(pointer struct GPS)
void GB02_Transfer_Data(struct GPS_Para *GPS_Data);

//#define BUFFER_SIZE		1024
//uint8_t Write_DataToRing(struct Ring_Buffer *Ring_Bufer_GPS, uint8_t Data_In);
//int 	READ_DataFromRing(struct Ring_Buffer *Ring_Bufer_GPS);

//struct Ring_Buffer
//{
//	uint8_t Data[BUFFER_SIZE];
//	int Read_Local;
//	int Write_Local;
//};
//
//extern struct Ring_Buffer Ring_Bufer_UART;
#endif /* INC_BG02_H10SG10_H_ */

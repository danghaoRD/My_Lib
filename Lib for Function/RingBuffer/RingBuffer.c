/*
 * RingBuffer.c
 *
 *  Created on: Jul 3, 2021
 *      Author: DANG_HAO 
 *	V1.1   Jul 16, 2021: fix  READ_DataFromRing() can't read end char
 *
 */
#include "RingBuffer.h"

// struct Ring_Buffer Ring_Bufer_GPS_Rec;
// struct Ring_Buffer Ring_Bufer_RIIM_Rec;
// struct Ring_Buffer Ring_Bufer_Debug_Rec;


uint8_t Write_DataToRing(struct Ring_Buffer *Ring_Bufer_In, uint8_t Data_In)
{
	int Temp_Local_Write = (Ring_Bufer_In->Write_Local +1) % BUFFER_SIZE;		// ignore local 0 when Start

	if(Temp_Local_Write != Ring_Bufer_In->Read_Local)
	{
		Ring_Bufer_In->Data[Temp_Local_Write] = Data_In;
		Ring_Bufer_In->Write_Local = Temp_Local_Write;
		return 1;																// successfully
	}
	else
		return 0;													// Fail
}
/* V1.0
uint8_t READ_DataFromRing(struct Ring_Buffer *Ring_Bufer_In, uint8_t *Data_Out)
{
	uint16_t  Temp_Local_Read = (Ring_Bufer_In->Read_Local) % BUFFER_SIZE;   // ignore local 0 when Start

	if(Temp_Local_Read == Ring_Bufer_In->Write_Local)
	{
		return 0;													// Fail.  No data to Read
	}
	else
	{
		uint8_t Temp_Data = Ring_Bufer_In->Data[Temp_Local_Read]; 
		*Data_Out = Temp_Data;
		Ring_Bufer_In->Read_Local = Temp_Local_Read+1;
		
		return 1;
	}
}
*/ 

// V1.1 edit
uint8_t READ_DataFromRing(struct Ring_Buffer *Ring_Bufer_In, uint8_t *Data_Out)
{
	uint16_t  Temp_Local_Read = (Ring_Bufer_In->Read_Local+1) % BUFFER_SIZE;   // ignore local 0 when Start

	if(Temp_Local_Read == ((Ring_Bufer_In->Write_Local+1) % BUFFER_SIZE))
	{
		return 0;													// Fail.  No data to Read
	}
	else
	{
		uint8_t Temp_Data = Ring_Bufer_In->Data[Temp_Local_Read];
		//Ring_Bufer_In->Data[Temp_Local_Read] = 0x00;
		Ring_Bufer_In->Read_Local = Temp_Local_Read;
		*Data_Out = Temp_Data;
		return 1;
	}
}

// void uartCsend_GPS( char *Data)
// {
// 	while(*(Data) != 0x00)
// 	{
// 		UART_SEND_1CHAR_GPS(Data);
// 		Data++;
// 	}
// }

// void uartCsend_RIIM( char *Data)
// {
// 	while(*(Data) != 0x00)
// 	{
// 		UART_SEND_1CHAR_RIIM(Data);
// 		Data++;
// 	}
// }

// void uartCsend_Debug( char *Data)
// {
// 	while(*(Data) != 0x00)
// 	{
// 		UART_SEND_1CHAR_DEBUG(Data);
// 		Data++;
// 	}
// }

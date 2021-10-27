/*
 * RingBuffer.h
 *
 *  Created on: Jul 3, 2021
 *      Author: HAO_DANG
 *
 *        Brief: Lib for function for handing string ang ringbuff of UART
 *   V1.1   Jul 16, 2021: fix  READ_DataFromRing() can't read end char
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_

#include "main.h"
#define BUFFER_SIZE		1024					// leng (byte) off data Ring Buff

// // RD_EDIT: UART Pointer change it to suit your MCU/IDE
// extern UART_HandleTypeDef huart1;
// extern UART_HandleTypeDef huart2;
// extern UART_HandleTypeDef huart3;


// RD_EDIT: UART change it to suit your MCU/IDE
// #define UART_SEND_1CHAR_GPS(Data)			HAL_UART_Transmit(&huart1, (uint8_t *) Data, 1, 100)
// #define UART_SEND_1CHAR_RIIM(Data)			HAL_UART_Transmit(&huart2, (uint8_t *) Data, 1, 100)
// #define UART_SEND_1CHAR_DEBUG(Data)			HAL_UART_Transmit(&huart3, (uint8_t *) Data, 1, 100)


struct Ring_Buffer
{
	// RD_EDIT: Ring_Buff Create New struct if you want many RingBuff have difference leng data
	uint8_t Data[BUFFER_SIZE];
	int Read_Local;
	int Write_Local;
};

// extern struct Ring_Buffer Ring_Bufer_GPS_Rec;
// extern struct Ring_Buffer Ring_Bufer_RIIM_Rec;
// extern struct Ring_Buffer Ring_Bufer_Debug_Rec;

/*
 *  Write 1 byte data to ring buffer tageted
 *  Input:  struct Ring_Buffer Pointer RingBuff save data
 *  		Data_In:  data write to ring buff
 *  Output:  uint8_t: Stt of function    	return = 1;	// successfully
 *  										return = 0; // fail
 */
uint8_t Write_DataToRing(struct Ring_Buffer *Ring_Bufer_In, uint8_t Data_In);

/*
 *  Read 1 byte data From ring buffer tageted
 *  Input:  struct Ring_Buffer Pointer RingBuff write data
 *  		Data_Out:  poiter data write out saved.
 *  Output:  uint8_t: Stt of function    	return = 1;	// successfully
 *  										return = 0; // fail
 */
uint8_t READ_DataFromRing(struct Ring_Buffer *Ring_Bufer_In, uint8_t *Data_Out);


// void uartCsend_GPS( char *Data);				// Write string to uart GPS
// void uartCsend_RIIM( char *Data);				// Write string to uart RIIM
// void uartCsend_Debug( char *Data);				// Write string to uart Debug
#endif /* INC_RINGBUFFER_H_ */

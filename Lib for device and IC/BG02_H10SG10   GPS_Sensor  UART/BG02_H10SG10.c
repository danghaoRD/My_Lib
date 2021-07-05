/*
 * BG02_H10SG10.c
 *
 *  Created on: July 05, 2021
 *      Author: HAO_DANG
 */
#include "BG02_H10SG10.h"
struct GPS_Para GPS_Value;

void BG02_Receive_UART(struct GPS_Para *GPS_Data, char  Data_In)
{

	static uint8_t Count_Rx=0;
	static uint8_t Receive_Data=0;
	//static uint8_t Transfer_Data=0;
	if(Data_In != 0xff)
	{

		if(Data_In == 0x0A)
		{
			BG02_Clear_Str_Data(GPS_Data);								// clear Data when end data
			Count_Rx=0;
			Receive_Data=0;												// turn Off Recive Data to
		}
		else
		{
			if(Count_Rx <= 5)
			{
				GPS_Data->Type_Para_GPS[Count_Rx] = Data_In;

				if(strcmp(GPS_Data->Type_Para_GPS, "$GNRMC") == 0)
				{
					Receive_Data=1;
				}
			}

			if((Receive_Data == 1) && (Count_Rx > 5))
			{
				GPS_Data->str_Para_GPS[Count_Rx-6] = Data_In;
				if(Data_In == 'E')
				{
					GB02_Transfer_Data(GPS_Data);
				}

			}
			Count_Rx ++;
			if(Count_Rx >=60) Count_Rx = 59;
		}
	}
}

void GB02_Transfer_Data(struct GPS_Para *GPS_Data)
{
	//char	DataNorthBuff[15] = {0};
	for(int i=0; i<=59; i++)
	{
		if(GPS_Data->str_Para_GPS[i] == 'N')
		{
			GPS_Data->North_GPS_Second = (uint8_t) ((GPS_Data->str_Para_GPS[i-6]-0x30)*10 + (GPS_Data->str_Para_GPS[i-5]-0x30));
			GPS_Data->North_GPS_Minute = (uint8_t) ((GPS_Data->str_Para_GPS[i-9]-0x30)*10 + (GPS_Data->str_Para_GPS[i-8]-0x30));

			if((GPS_Data->str_Para_GPS[i-12] <= 0x39) && (GPS_Data->str_Para_GPS[i-12] >= 0x30) )
			{
				GPS_Data->North_GPS_Degree = (uint8_t) ((GPS_Data->str_Para_GPS[i-12]-0x30)*100 + (GPS_Data->str_Para_GPS[i-11]-0x30)*10 \
														+ (GPS_Data->str_Para_GPS[i-10]-0x30));

				GPS_Data->North_GPS_Float = (float) ((GPS_Data->North_GPS_Degree) + (GPS_Data->North_GPS_Minute)/60.0 + (GPS_Data->North_GPS_Second)/3600.0);
			}
			else
			{
				GPS_Data->North_GPS_Degree = (uint8_t) (  (GPS_Data->str_Para_GPS[i-11]-0x30)*10 + (GPS_Data->str_Para_GPS[i-10]-0x30));
				GPS_Data->North_GPS_Float = (float) ((GPS_Data->North_GPS_Degree) + (GPS_Data->North_GPS_Minute)/60.0 + (GPS_Data->North_GPS_Second)/3600.0);
			}
		}

		if(GPS_Data->str_Para_GPS[i] == 'E')
		{
			GPS_Data->East_GPS_Second = (uint8_t) ((GPS_Data->str_Para_GPS[i-6]-0x30)*10 + (GPS_Data->str_Para_GPS[i-5]-0x30));
			GPS_Data->East_GPS_Minute = (uint8_t) ((GPS_Data->str_Para_GPS[i-9]-0x30)*10 + (GPS_Data->str_Para_GPS[i-8]-0x30));

			if((GPS_Data->str_Para_GPS[i-12] <= 0x39) && (GPS_Data->str_Para_GPS[i-12] >= 0x30) )
			{
				GPS_Data->East_GPS_Degree = (uint8_t) ((GPS_Data->str_Para_GPS[i-12]-0x30)*100 + (GPS_Data->str_Para_GPS[i-11]-0x30)*10 \
														+ (GPS_Data->str_Para_GPS[i-10]-0x30));

				GPS_Data->East_GPS_Float = (float) ((GPS_Data->East_GPS_Degree) + (GPS_Data->East_GPS_Minute)/60.0 + (GPS_Data->East_GPS_Second)/3600.0);
			}
			else
			{
				GPS_Data->East_GPS_Degree = (uint8_t) (  (GPS_Data->str_Para_GPS[i-11]-0x30)*10 + (GPS_Data->str_Para_GPS[i-10]-0x30));

				GPS_Data->East_GPS_Float = (float) ((GPS_Data->East_GPS_Degree) + (GPS_Data->East_GPS_Minute)/60.0 + (GPS_Data->East_GPS_Second)/3600.0);
			}
		}

	}
}

void BG02_Clear_Str_Data(struct GPS_Para *GPS_Data)
{
	for(int i=0; i<= 59; i++)
	{
		GPS_Data->str_Para_GPS[i] = 0x00;
	}
}

/*
struct Ring_Buffer Ring_Bufer_UART;

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

int READ_DataFromRing(struct Ring_Buffer *Ring_Bufer_In)
{
	uint16_t  Temp_Local_Read = (Ring_Bufer_In->Read_Local) % BUFFER_SIZE;   // ignore local 0 when Start

	if(Temp_Local_Read == Ring_Bufer_In->Write_Local)
	{
		return -1;													// Fail.  No data to Read
	}
	else
	{
		uint8_t Temp_Data = Ring_Bufer_In->Data[Temp_Local_Read];
		//Ring_Bufer_In->Data[Temp_Local_Read] = 0x00;
		Ring_Bufer_In->Read_Local = Temp_Local_Read+1;
		return Temp_Data;
	}
}
*/

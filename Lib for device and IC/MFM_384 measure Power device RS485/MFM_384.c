/*
 * MFM_384.c
 *
 *  Created on: Sep 26, 2021
 *      Author: PC2
 */
#include "MFM_384.h"
ModBus_Rx_Struct ModBus_Data_Rx;
MFM_384_Data_Struct MFM_384_Data;
void MFM_384_Converter(ModBus_Rx_Struct *Modbus_Rx, MFM_384_Data_Struct *MFM_Data)
{
	uint32_t Voltage_P1_Buff;
	Voltage_P1_Buff = (uint32_t) 	((Modbus_Rx->Data[V1_ADDR_DATA_4] << 24) |\
						 	 	 	 (Modbus_Rx->Data[V1_ADDR_DATA_3] << 16) |\
									 (Modbus_Rx->Data[V1_ADDR_DATA_2] << 8)  |\
									 (Modbus_Rx->Data[V1_ADDR_DATA_1] << 0) );
	MFM_Data->Voltage_Phase1 = *(float *)(&Voltage_P1_Buff);

	uint32_t Current_P1_Buff;
	Current_P1_Buff = (uint32_t) 	((Modbus_Rx->Data[I1_ADDR_DATA_4] << 24) |\
						 	 	 	 (Modbus_Rx->Data[I1_ADDR_DATA_3] << 16) |\
									 (Modbus_Rx->Data[I1_ADDR_DATA_2] << 8)  |\
									 (Modbus_Rx->Data[I1_ADDR_DATA_1] << 0) );
	MFM_Data->Current_Phase1 = *(float *)(&Current_P1_Buff);

	uint32_t Kw1_Buff;
	Kw1_Buff 	   = (uint32_t) 	((Modbus_Rx->Data[Kw1_ADDR_DATA_4] << 24) |\
						 	 	 	 (Modbus_Rx->Data[Kw1_ADDR_DATA_3] << 16) |\
									 (Modbus_Rx->Data[Kw1_ADDR_DATA_2] << 8)  |\
									 (Modbus_Rx->Data[Kw1_ADDR_DATA_1] << 0) );
	MFM_Data->Kw1 			= *(float *)(&Kw1_Buff);

	uint32_t Fre_Buff;
	Fre_Buff 	   = (uint32_t) 	((Modbus_Rx->Data[Fre_ADDR_DATA_4] << 24) |\
						 	 	 	 (Modbus_Rx->Data[Fre_ADDR_DATA_3] << 16) |\
									 (Modbus_Rx->Data[Fre_ADDR_DATA_2] << 8)  |\
									 (Modbus_Rx->Data[Fre_ADDR_DATA_1] << 0) );
	MFM_Data->Frequency 			= *(float *)(&Fre_Buff);

	uint32_t Kwh_Buff;
	Kwh_Buff 	   = (uint32_t) 	((Modbus_Rx->Data[Kwh_ADDR_DATA_4] << 24) |\
						 	 	 	 (Modbus_Rx->Data[Kwh_ADDR_DATA_3] << 16) |\
									 (Modbus_Rx->Data[Kwh_ADDR_DATA_2] << 8)  |\
									 (Modbus_Rx->Data[Kwh_ADDR_DATA_1] << 0) );
	MFM_Data->Kwh 			= *(float *)(&Kwh_Buff);
}

void Modbus_RTU_Recever(uint8_t Rx_In, ModBus_Rx_Struct *Modbus_Rx)
{
	const uint8_t Data_OffSet = 3;
	if(Modbus_Rx->Leng_Rx == 0)
	{
		Modbus_Rx->ADDR_Slave = Rx_In;
	}

	if(Modbus_Rx->Leng_Rx == 1)
	{
		Modbus_Rx->Function = Rx_In;
	}

	if(Modbus_Rx->Leng_Rx == 2)
	{
		Modbus_Rx->Leng_Data = Rx_In;
	}

	if((Modbus_Rx->Leng_Rx >= 3) && (Modbus_Rx->Leng_Rx < Data_OffSet + Modbus_Rx->Leng_Data) )
	{
		Modbus_Rx->Data[Modbus_Rx->Leng_Rx -Data_OffSet] = Rx_In;
	}

	if(Modbus_Rx->Leng_Rx == Data_OffSet + Modbus_Rx->Leng_Data)
	{
		Modbus_Rx->CRC_16[0] =  Rx_In;
	}

	if(Modbus_Rx->Leng_Rx == Data_OffSet + Modbus_Rx->Leng_Data +1)
	{
		Modbus_Rx->CRC_16[1] =  Rx_In;
	}

	Modbus_Rx->Leng_Rx++;
	if((Modbus_Rx->Leng_Rx >= 3) && (Modbus_Rx->Leng_Rx >= Modbus_Rx->Leng_Data + 5))
	{
		Modbus_Rx->Leng_Rx = 0;
	}

}

void Modbus_RTU_Rx_Clear(ModBus_Rx_Struct *Modbus_Rx)
{
	uint8_t *p_Clear_Buff;

	p_Clear_Buff = (uint8_t *) Modbus_Rx;

	const uint8_t Leng_Of_Modbus_Rx = LENG_OF_MODBUS_STR;

	for(int i=0; i <= Leng_Of_Modbus_Rx; i++)
	{
		*(p_Clear_Buff + i) = 0x00;
	}
}
void Modbus_RTU_Send(uint8_t ADDR_Slave, uint8_t Function, uint8_t* Data, uint16_t Data_Leng)
{
	const uint8_t Leng_Offset_ADR_Function = 2;		// Leng data ADR and Function
	const uint8_t Leng_Offset_CRC		   = 2;		// Leng CRC
	uint8_t Data_Buff[MAX_LENG_SEND_RTU] = {0};

	Data_Buff[0] = ADDR_Slave;
	Data_Buff[1] = Function;

	for(int i=0; i<Data_Leng; i++)
	{
		Data_Buff[i+Leng_Offset_ADR_Function] = *(Data+i);				// Shift 2 by offset ADDR, Function data
	}

	uint16_t CRC_Buff;
	CRC_Buff = CRC16_2((uint8_t *)Data_Buff, Data_Leng+2);				// Shift 2 by offset ADDR, Function data

	Data_Buff[Data_Leng + Leng_Offset_ADR_Function]    = (uint8_t) ((CRC_Buff     ) & 0xff);
	Data_Buff[Data_Leng + Leng_Offset_ADR_Function +1] = (uint8_t) ((CRC_Buff >> 8) & 0xff);

	Modbus_TxEn_RxDis;
	CRC_Tx(Data_Buff, Data_Leng + Leng_Offset_ADR_Function + Leng_Offset_CRC);
	Modbus_RxEn_TxDis;
}


uint16_t CRC16_2(unsigned char *buf, int len)
{
  unsigned int crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++)
  {
  crc ^= (unsigned int)buf[pos];    // XOR byte into least sig. byte of crc

  for (int i = 8; i != 0; i--) {    // Loop over each bit
    if ((crc & 0x0001) != 0) {      // If the LSB is set
      crc >>= 1;                    // Shift right and XOR 0xA001
      crc ^= 0xA001;
    }
    else                            // Else LSB is not set
      crc >>= 1;                    // Just shift right
    }
  }

  return crc;
}

/*
 * RD_CY8CMBR3110.c
 *
 *  Created on: Apr 9, 2021
 *      Author: dangv
 */
#include "RD_CY8CMBR3110.h"
//uint8_t config_crc_L	= 0x00;
//uint8_t	confi__crc_H	= 0x00;

uint8_t	Register_Config[128] = {0};





void RD_CY8_uplate_Data(void)
{

	Register_Config[ SENSOR_EN_L_REG_CY8] 		= SENSOR_EN_L;
	Register_Config[ SENSOR_EN_H_REG_CY8] 		= SENSOR_EN_H;
	Register_Config[ FSS_EN_L_REG_CY8] 			= FSS_EN_L;
	Register_Config[ FSS_EN_H_REG_CY8] 			= FSS_EN_H;
	Register_Config[ TOGGLE_EN_L_REG_CY8] 		= TOGGLE_EN_L;
	Register_Config[ TOGGLE_EN_H_REG_CY8] 		= TOGGLE_EN_H;
	Register_Config[ LED_ON_EN_L_REG_CY8] 		= LED_ON_EN_L;
	Register_Config[ LED_ON_EN_H_REG_CY8] 		= LED_ON_EN_H;
	Register_Config[ SENSITIVITY0_REG_CY8] 		= SENSITIVITY0;
	Register_Config[ SENSITIVITY1_REG_CY8]	 	= SENSITIVITY1;
	Register_Config[ SENSITIVITY2_REG_CY8] 		= SENSITIVITY2;
	Register_Config[ BASE_THRESHOLD0_REG_CY8] 	= BASE_THRESHOLD0;
	Register_Config[ BASE_THRESHOLD1_REG_CY8] 	= BASE_THRESHOLD1;
	Register_Config[ FINGER_THRESHOLD2_REG_CY8] = FINGER_THRESHOLD2;
	Register_Config[ FINGER_THRESHOLD3_REG_CY8] = FINGER_THRESHOLD3;
	Register_Config[ FINGER_THRESHOLD4_REG_CY8] = FINGER_THRESHOLD4;
	Register_Config[ FINGER_THRESHOLD5_REG_CY8] = FINGER_THRESHOLD5;
	Register_Config[ FINGER_THRESHOLD6_REG_CY8] = FINGER_THRESHOLD6;
	Register_Config[ FINGER_THRESHOLD7_REG_CY8] = FINGER_THRESHOLD7;
	Register_Config[ FINGER_THRESHOLD8_REG_CY8] = FINGER_THRESHOLD8;
	Register_Config[ FINGER_THRESHOLD9_REG_CY8] = FINGER_THRESHOLD9;
	Register_Config[ SENSOR_DEBOUNCE_REG_CY8] 	= SENSOR_DEBOUNCE;
	Register_Config[ BUTTON_HYS_REG_CY8] 		= BUTTON_HYS;
	Register_Config[ BUTTON_LBR_REG_CY8] 		= BUTTON_LBR;
	Register_Config[ BUTTON_NNT_REG_CY8	] 		= BUTTON_NNT;
	Register_Config[ BUTTON_NT_REG_CY8] 		= BUTTON_NT;
	Register_Config[ PROX_EN_REG_CY8] 			= PROX_EN;
	Register_Config[ PROX_CFG_REG_CY8 ] 		= PROX_CFG;
	Register_Config[ PROX_CFG2_REG_CY8] 		= PROX_CFG2;
	Register_Config[ PROX_TOUCH_TH0_L_REG_CY8] 	= PROX_TOUCH_TH0_L;
	Register_Config[ PROX_TOUCH_TH0_H_REG_CY8]	= PROX_TOUCH_TH0_H;
	Register_Config[ PROX_TOUCH_TH1_L_REG_CY8] 	= PROX_TOUCH_TH1_L;
	Register_Config[ PROX_TOUCH_TH1_H_REG_CY8] 	= PROX_TOUCH_TH1_H;
	Register_Config[ PROX_RESOLUTION0_REG_CY8] 	= PROX_RESOLUTION0;
	Register_Config[ PROX_RESOLUTION1_REG_CY8] 	= PROX_RESOLUTION1;
	Register_Config[ PROX_HYS_REG_CY8] 			= PROX_HYS;
	Register_Config[ PROX_LBR_REG_CY8] 			= PROX_LBR;
	Register_Config[ PROX_NNT_REG_CY8]		 	= PROX_NNT;
	Register_Config[ PROX_NT_REG_CY8] 			= PROX_NT;
	Register_Config[ PROX_POSITIVE_TH0_REG_CY8] = PROX_POSITIVE_TH0;
	Register_Config[ PROX_POSITIVE_TH1_REG_CY8] = PROX_POSITIVE_TH1;
	Register_Config[ PROX_NEGATIVE_TH0_REG_CY8] = PROX_NEGATIVE_TH0;
	Register_Config[ PROX_NEGATIVE_TH1_REG_CY8] = PROX_NEGATIVE_TH1;
	Register_Config[ LED_ON_TIME_REG_CY8] 		= LED_ON_TIME;
	Register_Config[ BUZZER_CFG_REG_CY8	] 		= BUZZER_CFG;
	Register_Config[ BUZZER_ON_TIME_REG_CY8	] 	= BUZZER_ON_TIME;
	Register_Config[ GPO_CFG_REG_CY8] 			= GPO_CFG;
	Register_Config[PWM_DUTYCYCLE_CFG0_REG_CY8] = PWM_DUTYCYCLE_CFG0;
	Register_Config[PWM_DUTYCYCLE_CFG1_REG_CY8] = PWM_DUTYCYCLE_CFG1;
	Register_Config[PWM_DUTYCYCLE_CFG2_REG_CY8] = PWM_DUTYCYCLE_CFG2;
	Register_Config[PWM_DUTYCYCLE_CFG3_REG_CY8] = PWM_DUTYCYCLE_CFG3;
	Register_Config[PWM_DUTYCYCLE_CFG4_REG_CY8] = PWM_DUTYCYCLE_CFG4;
	Register_Config[SPO_CFG_REG_CY8] 			= SPO_CFG;
	Register_Config[ DEVICE_CFG0_REG_CY8] 		= DEVICE_CFG0;
	Register_Config[ DEVICE_CFG1_REG_CY8] 		= DEVICE_CFG1;
	Register_Config[ DEVICE_CFG2_REG_CY8] 		= DEVICE_CFG2;
	Register_Config[ DEVICE_CFG3_REG_CY8] 		= DEVICE_CFG3;
	Register_Config[ I2C_ADDR_REG_CY8] 			= I2C_ADDR;
	Register_Config[ REFRESH_CTRL_REG_CY8] 		= REFRESH_CTRL;
	Register_Config[ STATE_TIMEOUT_REG_CY8] 	= STATE_TIMEOUT;
	Register_Config[ SCRATCHPAD0_REG_CY8] 		= SCRATCHPAD0;
	Register_Config[ SCRATCHPAD1_REG_CY8] 		= SCRATCHPAD1;
	Register_Config[CONFIG_CRC_L_REG_CY8]       = 0x00;
	Register_Config[CONFIG_CRC_H_REG_CY8]       = 0x00;
}

void RD_CY8_Init(void)
{

	    uint32_t checkSum32_Buff		= 0;
		uint16_t checkSum_Buff 			= 0;
		uint8_t  ctrlCmdStatus_Buff 	= 0xff;				// buff check
		uint8_t	 ctrlCmdErr_Buff		= 0x00;
		uint8_t  cmdOpCode_Save_Buff	= 0x02;		// save data
		uint8_t  cmdOpCode_GetCRC_Buff	= 0x03;		// save data
		uint8_t	 cmdOpCode_Reset_Buff	= 255;
		uint8_t check_CALC_CRC[2]      ={0};
//		for(int i=0; i<62; i++)													//check sum Register_Config[0] --> Register_Config[62]
//		{
//			checkSum_Buff = checkSum_Buff + Register_Config[i];
//			checkSum32_Buff = checkSum32_Buff + Register_Config[i];
//		}
//		if(checkSum32_Buff ==1);
//		Register_Config[62] =   (checkSum_Buff & 0xFF);					// get value for CONFIG_CRC_L
//		Register_Config[63] =  (checkSum_Buff>>8) & 0xFF;				// get value for CONFIG_CRC_H
		 RD_CY8_uplate_Data();
		do
		{
			checkSum_Buff=1;
			for(int i=0; i< 126; i++)													//check sum Register_Config[0] --> Register_Config[125]
			{
				checkSum_Buff = checkSum_Buff + Register_Config[i];
				checkSum32_Buff = checkSum32_Buff + Register_Config[i];
			}
			if(checkSum32_Buff ==1);
			Register_Config[CONFIG_CRC_L_REG_CY8] =   (checkSum_Buff & 0xFF);					// get value for CONFIG_CRC_L
			Register_Config[CONFIG_CRC_H_REG_CY8] =  (checkSum_Buff>>8) & 0xFF;				// get value for CONFIG_CRC_H




			Register_Config[CONFIG_CRC_L_REG_CY8] =  0xb2;								// get value for CONFIG_CRC_L
			Register_Config[CONFIG_CRC_H_REG_CY8] =  0xe0;								// get value for CONFIG_CRC_H

/*--------------------------------------------------get CRC--------------------------------------------------------------*/
			while(HAL_I2C_Mem_Write(&hi2c2, I2C_ADD_CY8, SENSOR_EN_L_REG_CY8, 1, Register_Config, SIZE_OF_DATA_CONFIG, 1000) != HAL_OK);				// config data
			HAL_Delay(50);

			while(HAL_I2C_Mem_Write(&hi2c2, I2C_ADD_CY8, CTRL_CMD_CY8_REG, 1, &cmdOpCode_GetCRC_Buff, 1, 1000) != HAL_OK);		// send cmd op code =2 to save
			HAL_Delay(220);

			while(HAL_I2C_Mem_Read(&hi2c2, I2C_ADD_CY8, 0x94, 1, check_CALC_CRC, 2, 1000) != HAL_OK);
			Register_Config[CONFIG_CRC_L_REG_CY8] =  check_CALC_CRC[0];					// get value for CONFIG_CRC_L
			Register_Config[CONFIG_CRC_H_REG_CY8] =  check_CALC_CRC[1];			// get value for CONFIG_CRC_H
/*--------------------------------------------------get CRC--------------------------------------------------------------*/



			while(HAL_I2C_Mem_Write(&hi2c2, I2C_ADD_CY8, SENSOR_EN_L_REG_CY8, 1, Register_Config, SIZE_OF_DATA_CONFIG, 1000) != HAL_OK);				// config data
			HAL_Delay(50);

			do
			{
				while(HAL_I2C_Mem_Write(&hi2c2, I2C_ADD_CY8, CTRL_CMD_CY8_REG, 1, &cmdOpCode_Save_Buff, 1, 1000) != HAL_OK);		// send cmd op code =2 to save
				HAL_Delay(220);
				while(HAL_I2C_Mem_Read(&hi2c2, I2C_ADD_CY8, CTRL_CMD_STATUS_CY8_REG, 1, &ctrlCmdStatus_Buff, 1, 1000) != HAL_OK);

				//while(HAL_I2C_Mem_Read(&hi2c2, I2C_ADD_CY8, 0x94, 1, check_CALC_CRC, 2, 1000) != HAL_OK);
			//	ctrlCmdStatus_Buff =0;
				if(ctrlCmdStatus_Buff == 0)																							// config and save successfully
				{
					while(HAL_I2C_Mem_Write(&hi2c2, I2C_ADD_CY8, CTRL_CMD_CY8_REG, 1, &cmdOpCode_Reset_Buff, 1, 1000) != HAL_OK);
					HAL_Delay(100);
				}
				else
				{
					while(HAL_I2C_Mem_Read(&hi2c2, I2C_ADD_CY8, CTRL_CMD_ERR_CY8_REG, 1, &ctrlCmdErr_Buff, 1, 1000) != HAL_OK);
					HAL_Delay(220);

				}

			}
			while((ctrlCmdErr_Buff == 253) || (ctrlCmdErr_Buff == 255));
		}
		while(ctrlCmdErr_Buff == 254);



}



void RD_CY8_Config(void)
{
	  uint8_t Data_Buff[2];
	  Data_Buff[0] = 0x01;
	  Data_Buff[1] = 0x01;
	  while( HAL_I2C_Mem_Write(&hi2c2, I2C_ADD_CY8, SENSOR_EN_L_REG_CY8, 1, Data_Buff, 2, 1000) != HAL_OK)
	  {

	  }
}

uint8_t RD_CY8_CMD_STT(void)
{
	uint8_t cmdSttBuff=1;
	  while(  HAL_I2C_Mem_Read(&hi2c2, I2C_ADD_CY8, CTRL_CMD_STATUS_CY8_REG, 1, &cmdSttBuff, 1, 1000) != HAL_OK)
	  {

	  }
	  return cmdSttBuff;
}

uint8_t RD_CY8_CMD_ERR(void)
{
	uint8_t cmdErrBuff = 1;
	  while(  HAL_I2C_Mem_Read(&hi2c2, I2C_ADD_CY8, CTRL_CMD_ERR_CY8_REG, 1, &cmdErrBuff, 1, 1000) != HAL_OK)
	  {

	  }
	  return cmdErrBuff;

}
uint16_t RD_CY8_Read_Sensor(uint8_t SensorID)
{
	uint16_t RegSensorID_Buff =0xFF;
	RegSensorID_Buff = DIFFERENCE_COUNT_SENSOR0_CY8_REG + SensorID;
	uint16_t CountSignal_Buff = 0xFF;
	CountSignal_Buff =  I2C_Read_CY8(I2C_ADD_CY8, RegSensorID_Buff, 2);
	return CountSignal_Buff;
}
uint8_t I2C_Write_CY8(uint16_t Slave_Add, uint16_t Reg_Add, uint16_t size, uint16_t  DataWrite)
{
	uint8_t data[2];
	if(size == 2)
	{
		data[0] = DataWrite & 0xff;  //DataWrite & 0xff;
		data[1] = (DataWrite >> 8); //(DataWrite >> 8);
	}
	else
	{
		data[0] = DataWrite & 0xff;
		data[1] = 0x00;
	}
	I2CWrite_CY8_DEF(Slave_Add, Reg_Add, size, data);

//	uint16_t data_buff =0x00;
//
	 return 0;
}

uint16_t I2C_Read_CY8(uint16_t SlaveAdd, uint16_t RegAdd, uint16_t Size)
{
	uint8_t data[2] = {0};
	 I2CRead_CY8_DEF(SlaveAdd, RegAdd, Size, data);
	//	 HAL_I2C_Mem_Read(&hi2c2, I2C_ADD_CY8, SENSOR_EN_CY8_REG, 1, data, 2, 1000);
	//	 uint16_t CheckSysStt_Buff2  = (Data_Buff[0]<<8) | Data_Buff[1];
	uint16_t Result = 0x00;
	Result = (data[1] << 8) | data[0];
	return Result;
}

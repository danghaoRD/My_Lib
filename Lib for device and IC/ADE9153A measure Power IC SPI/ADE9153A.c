/*
 * ADE9153A.c
 *
 *  Created on: July 6, 2021
 *      Author: HAO_DANG
 */

#include "ADE9153A.h"
struct EnergyRegs energyVals;  //Energy register values are read and stored in EnergyRegs structure
struct PowerRegs powerVals;    //Metrology data can be accessed from these structures
struct RMSRegs rmsVals;
struct PQRegs pqVals;
struct AcalRegs acalVals;
struct Temperature tempVal;

void ADE9153A_Init(void)
{
	  ADE9153AReset();
	  Delayms(1000);

	  ADE9153AWrite16(REG_RUN, ADE9153A_RUN_ON);
	  uint32_t Version = ADE9153ARead32(REG_VERSION_PRODUCT);
	  Delayms(100);
	  ADE9153AConfig();
	  ADE9153AWrite32(REG_AIGAIN, -268435456);
}

void ADE9153AWrite16(uint16_t Add, uint16_t Data)
{
	uint8_t Data_Buff[4];
	Add = (Add << 4) & 0xFFF0;

	Data_Buff[0] = (Add ) 	 	& 0xF0;
	Data_Buff[1] = (Add >> 8) 	& 0xFF; // shift Add <<4 + 0 (Write cmd)
	Data_Buff[2] = (Data ) 		& 0xFF;
	Data_Buff[3] = (Data >>8)   & 0xFF;

	SPI_SS_PIN_ADE9153A_LOW										// Enable Slave SPI
	SPI_ADE9153A_TRANS(Data_Buff, 2);
	SPI_SS_PIN_ADE9153A_HIGH									// End Trans SPI
}

void ADE9153AWrite32(uint16_t Add, uint32_t Data)
{
	uint8_t Data_Buff[6];
	Add = (Add << 4) & 0xFFF0;

	Data_Buff[0] = (Add ) 	  	& 0xFF;
	Data_Buff[1] = (Add >> 8) 	& 0xFF; // shift Add <<4 + 0 (Write cmd)
	Data_Buff[2] = (Data >> 16) & 0xFF;
	Data_Buff[3] = (Data >> 24) & 0xFF;
	Data_Buff[4] = (Data ) 		& 0xFF;
	Data_Buff[5] = (Data >> 8)  & 0xFF;

	SPI_SS_PIN_ADE9153A_LOW										// Enable Slave SPI
	SPI_ADE9153A_TRANS(Data_Buff, 3);							// End Trans SPI
	SPI_SS_PIN_ADE9153A_HIGH
}

uint16_t ADE9153ARead16(uint16_t Add )
{
	uint8_t Data_Buff[2];
	uint8_t Add_Buff[2];
	uint16_t DataReturn=0;
	Add = ((Add << 4) & 0xFFF0) + 0x8;

	Add_Buff[0] =  Add 			& 0xFF;			// 16 bit SPI Mode
	Add_Buff[1] =  (Add >> 8) 	& 0xFF;

	SPI_SS_PIN_ADE9153A_LOW
	SPI_ADE9153A_TRANS(Add_Buff, 1);
	SPI_ADE9153A_RECEIVE(Data_Buff, 1);
	SPI_SS_PIN_ADE9153A_HIGH

	DataReturn = (Data_Buff[1] << 8) | Data_Buff[0]; // MSB Mode
	return  DataReturn;
}

uint32_t ADE9153ARead32(uint16_t Add )
{
	uint8_t Data_Buff[4]={0};
	uint8_t Add_Buff[6]={0};
	uint32_t DataReturn=0;
	uint16_t Add_Read;
	Add_Read = (((Add << 4) & 0xFFF0) + 8);

	Add_Buff[0] =  Add_Read 		& 0xFF;
	Add_Buff[1] =  (Add_Read >> 8) 	& 0xFF;
	Add_Buff[2] = 0x00;
	Add_Buff[3] = 0x00;

	SPI_SS_PIN_ADE9153A_LOW
	// Delayms(1);
	SPI_ADE9153A_TRANS(Add_Buff, 1);
	SPI_ADE9153A_RECEIVE(Data_Buff, 2);
	// Delayms(1);
	SPI_SS_PIN_ADE9153A_HIGH

	DataReturn = ((Data_Buff[1] << 24) 	|  Data_Buff[0]<<16) \
				| ((Data_Buff[3] << 8) | (Data_Buff[2]  ));	// MSB x16 x2 data

	return  DataReturn;
}
void ADE9153AReset(void)
{
	SPI_RESET_PIN_ADE9153A_LOW
	Delayms(100);
	SPI_RESET_PIN_ADE9153A_HIGH
	Delayms(1000);
}

void ADE9153AConfig(void)
{
	ADE9153AWrite16(REG_AI_PGAGAIN, ADE9153A_AI_PGAGAIN);
	ADE9153AWrite16(REG_CONFIG0, ADE9153A_CONFIG0);
	ADE9153AWrite16(REG_CONFIG1, ADE9153A_CONFIG1);
	ADE9153AWrite16(REG_CONFIG2,ADE9153A_CONFIG2);
	ADE9153AWrite16(REG_CONFIG3,ADE9153A_CONFIG3);
	ADE9153AWrite16(REG_ACCMODE,ADE9153A_ACCMODE);
	ADE9153AWrite32(REG_VLEVEL,ADE9153A_VLEVEL);
	ADE9153AWrite16(REG_ZX_CFG,ADE9153A_ZX_CFG);
	ADE9153AWrite32(REG_MASK,ADE9153A_MASK);
	ADE9153AWrite32(REG_ACT_NL_LVL,ADE9153A_ACT_NL_LVL);
	ADE9153AWrite32(REG_REACT_NL_LVL,ADE9153A_REACT_NL_LVL);
	ADE9153AWrite32(REG_APP_NL_LVL,ADE9153A_APP_NL_LVL);
	ADE9153AWrite16(REG_COMPMODE,ADE9153A_COMPMODE);
	ADE9153AWrite32(REG_VDIV_RSMALL,ADE9153A_VDIV_RSMALL);
	ADE9153AWrite16(REG_EP_CFG,ADE9153A_EP_CFG);
	ADE9153AWrite16(REG_EGY_TIME,ADE9153A_EGY_TIME);		//Energy accumulation ON
	ADE9153AWrite16(REG_TEMP_CFG,ADE9153A_TEMP_CFG);
}
uint8_t CheckID(void)
{
	return 0;
}

void ADE9153AReadEnergyRegs(struct EnergyRegs *Data)
{
	int32_t tempReg;
	float tempValue;

	tempReg =  (int32_t) (ADE9153ARead32(REG_AWATTHR_HI));
	Data->ActiveEnergyReg = tempReg;
	tempValue = (float)tempReg * CAL_ENERGY_CC / 1000;
	Data->ActiveEnergyValue = tempValue;				//Energy in mWhr

	tempReg = (int32_t) (ADE9153ARead32(REG_AFVARHR_HI));
	Data->FundReactiveEnergyReg = tempReg;
	tempValue = (float)tempReg * CAL_ENERGY_CC / 1000;
	Data->FundReactiveEnergyValue = tempValue;			//Energy in mVARhr

	tempReg = (int32_t)  (ADE9153ARead32(REG_AVAHR_HI));
	Data->ApparentEnergyReg = tempReg;
	tempValue = (float)tempReg * CAL_ENERGY_CC / 1000;
	Data->ApparentEnergyValue = tempValue;				//Energy in mVAhr

}

void ADE9153AReadPowerRegs( struct PowerRegs *Data)
{
	int32_t tempReg;
	float tempValue;

	tempReg 	= (int32_t) (ADE9153ARead32(REG_AWATT));
	Data->ActivePowerReg 	= tempReg;
	tempValue 	= (float)tempReg * CAL_POWER_CC / 1000;
	Data->ActivePowerValue 	= tempValue;						//Power in mW

	tempReg 	= (int32_t) (ADE9153ARead32(REG_AFVAR));
	Data->FundReactivePowerReg 		= tempReg;
	tempValue 	= (float)tempReg * CAL_POWER_CC / 1000;
	Data->FundReactivePowerValue 	= tempValue;				//Power in mVAR

	tempReg 	= (int32_t) (ADE9153ARead32(REG_AVA));
	Data->ApparentPowerReg 			= tempReg;
	tempValue 	= (float)tempReg * CAL_POWER_CC / 1000;
	Data->ApparentPowerValue 		= tempValue;				//Power in mVA
}

void ADE9153AReadRMSRegs(struct RMSRegs *Data)
{
	uint32_t tempReg;
	float 	tempValue;

	tempReg 	= (int32_t) (ADE9153ARead32(REG_AIRMS));
	Data->CurrentRMSReg = tempReg;
	tempValue 	= (float)tempReg * CAL_IRMS_CC / 1000;	//RMS in mA
	Data->CurrentRMSValue = tempValue;

	tempReg 	= (int32_t) (ADE9153ARead32(REG_AVRMS));
	Data->VoltageRMSReg = tempReg;
	tempValue 	= (float)tempReg * CAL_VRMS_CC / 1000;	//RMS in mV
	Data->VoltageRMSValue = tempValue;
}

void ADE9153AHalfRMSRegs( struct HalfRMSRegs *Data)
{
	uint32_t tempReg;
	float tempValue;

	tempReg	 	= (int32_t) (ADE9153ARead32(REG_AIRMS_OC));
	Data->HalfCurrentRMSReg = tempReg;
	tempValue	 = (float)tempReg * CAL_IRMS_CC / 1000;			//Half-RMS in mA
	Data->HalfCurrentRMSValue = tempValue;

	tempReg 	= (int32_t) (ADE9153ARead32(REG_AVRMS_OC));
	Data->HalfVoltageRMSReg = tempReg;
	tempValue 	= (float)tempReg * CAL_VRMS_CC / 1000;			//Half-RMS in mV
	Data->HalfVoltageRMSValue = tempValue;
}

void ADE9153AReadPQRegs(struct PQRegs *Data)
{
	int32_t tempReg;
	uint16_t temp;
	float mulConstant;
	float tempValue;

	tempReg 	= (int32_t) (ADE9153ARead32(REG_APF)); 				//Read PF register
	Data->PowerFactorReg = tempReg;

	tempValue 	= (float)tempReg / (float)134217728; 				//Calculate PF
	Data->PowerFactorValue = tempValue;

	tempReg 	= (int32_t) (ADE9153ARead32(REG_APERIOD)); 			//Read PERIOD register
	Data->PeriodReg = tempReg;

	tempValue 	= (float)(4000 * 65536) / (float)(tempReg + 1);	 	//Calculate Frequency
	Data->FrequencyValue = tempValue;

	temp 		= ADE9153ARead16(REG_ACCMODE); 						//Read frequency setting register
	if((temp & 0x0010) > 0){
		mulConstant = 0.02109375;  									//multiplier constant for 60Hz system
	}else{
		mulConstant = 0.017578125; 									//multiplier constant for 50Hz system
	}

	tempReg = (int16_t) (ADE9153ARead16(REG_ANGL_AV_AI)); 			//Read ANGLE register
	Data->AngleReg_AV_AI 	= tempReg;
	tempValue 				= tempReg * mulConstant;				//Calculate Angle in degrees
	Data->AngleValue_AV_AI 	= tempValue;
}

void ADE9153ReadAcalRegs(struct AcalRegs *Data)
{
	uint32_t tempReg;
	float tempValue;

	tempReg = (int32_t) (ADE9153ARead32(REG_MS_ACAL_AICC)); 	//Read AICC register
	Data->AcalAICCReg = tempReg;
	tempValue = (float)tempReg / (float)2048; 					//Calculate Conversion Constant (CC)
	Data->AICC = tempValue;
	tempReg = (int32_t) (ADE9153ARead32(REG_MS_ACAL_AICERT)); 	//Read AICERT register
	Data->AcalAICERTReg = tempReg;

	tempReg = (int32_t) (ADE9153ARead32(REG_MS_ACAL_AVCC)); 	//Read AVCC register
	Data->AcalAVCCReg = tempReg;
	tempValue = (float)tempReg / (float)2048; 					//Calculate Conversion Constant (CC)
	Data->AVCC = tempValue;
	tempReg = (int32_t) (ADE9153ARead32(REG_MS_ACAL_AVCERT)); 	//Read AICERT register
	Data->AcalAVCERTReg = tempReg;
}

uint8_t ADE9153AStartAcal_AINomal(void)
{
	uint32_t ready = 0;
	int waitTime = 0;

	ready = ADE9153ARead32(REG_MS_STATUS_CURRENT);				//Read system ready bit

	while((ready & 0x00000001) == 0)
	{
		if(waitTime > 11)
		{
			return 0;
		}
		Delayms(100);
		waitTime++;
	}

	ADE9153AWrite32(REG_MS_ACAL_CFG, 0x00000013);
	return 1;
}

uint8_t ADE9153AStartAcal_AITurbo(void)
{
	uint32_t ready = 0;
	int waitTime = 0;

	while((ready & 0x00000001) == 0)
	{
		ready = ADE9153ARead32(REG_MS_STATUS_CURRENT);		//Read system ready bit
		if(waitTime  >15)
		{
			return 0;
		}
		Delayms(100);
		waitTime++;
	}

	ADE9153AWrite32(REG_MS_ACAL_CFG, 0x00000017);
	return 1;
}

uint8_t ADE9153AStartAcal_AV(void)
{
	uint32_t ready = 0;
	int waitTime = 0;

	while((ready & 0x00000001) == 0)
	{
		ready = ADE9153ARead32(REG_MS_STATUS_CURRENT);		//Read system ready bit
		if(waitTime > 15)
		{
			return 0;
		}
		Delayms(100);
		waitTime++;
	}

	ADE9153AWrite32(REG_MS_ACAL_CFG, 0x00000043);
	return 1;
}

void ADE9153AStopAcal(void)
{
	ADE9153AWrite32(REG_MS_ACAL_CFG, 0x00000000);
}

uint8_t ADE9153AApplyAcal(float AICC, float AVCC)
{
	int32_t AIGAIN;
	int32_t AVGAIN;

	AIGAIN = (AICC / (CAL_IRMS_CC * 1000) - 1) * 134217728;
	AVGAIN = (AVCC / (CAL_VRMS_CC * 1000) - 1) * 134217728;

	ADE9153AWrite32(REG_AIGAIN, AIGAIN);
	ADE9153AWrite32(REG_AVGAIN, AVGAIN);
	return 1;
}

void ADE9153AReadTemperature(struct Temperature *Data)
{
	uint32_t trim;
	uint16_t gain;
	uint16_t offset;
	uint16_t tempReg;
	float tempValue;

	ADE9153AWrite16(REG_TEMP_CFG,ADE9153A_TEMP_CFG);//Start temperature acquisition cycle
	Delayms(100); //delay of 2ms. Increase delay if TEMP_TIME is changed

	trim 		= ADE9153ARead32(REG_TEMP_TRIM);
	gain 		= (trim & 0xFFFF);  //Extract 16 LSB
	offset 		= ((trim >> 16) & 0xFFFF); //Extract 16 MSB
	tempReg 	= ADE9153ARead16(REG_TEMP_RSLT);	//Read Temperature result register
	tempValue 	= ((float)offset / 32.00) - ((float)tempReg * (float)gain/(float)131072);

	Data->TemperatureReg = tempReg;
	Data->TemperatureVal = tempValue;
}

void ADE9153AReadAllValue(void)
{
	ADE9153AReadEnergyRegs(&energyVals);
	ADE9153AReadPowerRegs(&powerVals);
	ADE9153AReadRMSRegs(&rmsVals);
	ADE9153AReadPQRegs(&pqVals);
	ADE9153AReadTemperature(&tempVal);
	#if (ADE9153A_UART_ON == 1)
		char cal[128];
		sprintf(cal, "RMS Current \t= %0.3f A\n", 		rmsVals.CurrentRMSValue/1000 );
		uartCsend_Debug(cal);

		sprintf(cal, "RMS Voltage \t= %0.3f V\n", 		rmsVals.VoltageRMSValue/1000 );
		uartCsend_Debug(cal);

		sprintf(cal, "Active Power \t= %0.3f W\n", 		powerVals.ActivePowerValue/1000 );
		uartCsend_Debug(cal);

		sprintf(cal, "Reactive Power \t= %0.3f VAR\n", 	powerVals.FundReactivePowerValue/1000);
		uartCsend_Debug(cal);

		sprintf(cal, "Apparent Factor \t= %0.3f VA\n", 	powerVals.ApparentPowerValue/1000);
		uartCsend_Debug(cal);

		sprintf(cal, "Power Factor \t= %0.3f  \n", 		pqVals.PowerFactorValue);
		uartCsend_Debug(cal);

		sprintf(cal, "Frequency \t= %0.3f Hz\n", 		pqVals.FrequencyValue);
		uartCsend_Debug(cal);

		sprintf(cal, "Active Energy \t= %0.3f Whr\n", 	energyVals.ActiveEnergyValue/1000);
		uartCsend_Debug(cal);

		sprintf(cal, "Reactive Energy \t= %0.3f VARhr\n",energyVals.FundReactiveEnergyValue/1000);
		uartCsend_Debug(cal);

		sprintf(cal, "Apparent Energy \t= %0.3f VAhr\n",energyVals.ApparentEnergyValue/1000);
		uartCsend_Debug(cal);

		sprintf(cal, "T = %0.2f *C\n", 					tempVal.TemperatureVal );
		uartCsend_Debug(cal);
	#endif
}

void ADE9153AAutoCalib(void)
{
	#if (ADE9153A_UART_ON == 1)
		char cal[128];
		uartCsend_Debug("AutoCalibrating Current Chanel\n");
	#endif

	ADE9153AStartAcal_AINomal();
	for(int i=20; i>=1; i--)
	{
		#if (ADE9153A_UART_ON == 1)
			sprintf(cal, " %d A\n", i );
			uartCsend_Debug(cal);
			if(i == 1)
			{
				uartCsend_Debug("Calib Current Done!\n");
			}
		#endif
		Delayms(1000);
	}
	ADE9153AStopAcal();

	#if (ADE9153A_UART_ON == 1)
		uartCsend_Debug("AutoCalibraling Voltage Chanel! \n");
	#endif

	ADE9153AStartAcal_AV();

	for(int i=40; i>=1; i--)
	{
		#if (ADE9153A_UART_ON == 1)
				sprintf(cal, " %d A\n", i );
				uartCsend_Debug(cal);
				if(i == 1)
				{
					uartCsend_Debug("Calib Voltage Done!\n");
				}
		#endif
		Delayms(1000);
	}

	ADE9153AStopAcal();
	Delayms(100);

	ADE9153ReadAcalRegs(&acalVals);

	#if (ADE9153A_UART_ON == 1)
		sprintf(cal, "AICC: \t= %.3f \n", acalVals.AICC);
		uartCsend_Debug(cal);
		sprintf(cal, "AICERT: \t= %ld \n", acalVals.AcalAICERTReg);
		uartCsend_Debug(cal);
		sprintf(cal, "AVCC: \t= %.3f \n", acalVals.AVCC);
		uartCsend_Debug(cal);
		sprintf(cal, "AVCERT: \t= %ld \n", acalVals.AcalAVCERTReg);
		uartCsend_Debug(cal);
	#endif

    long Igain = (-(acalVals.AICC / 838.190) - 1) * 134217728;
    long Vgain = ((acalVals.AVCC / 13411.05) - 1) * 134217728;

    ADE9153AWrite32(REG_AIGAIN, Igain);
    ADE9153AWrite32(REG_AVGAIN, Vgain);

	#if (ADE9153A_UART_ON == 1)
		uartCsend_Debug("AutoCalibration Complete\n");
	#endif

    ADE9153AWrite16(REG_RUN, ADE9153A_RUN_ON);
    Delayms(500);
}

void ADE9153AResetEnergy(void)
{
	ADE9153AWrite16(REG_EP_CFG,ADE9153A_EP_CFG);
}

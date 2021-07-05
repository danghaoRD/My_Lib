/*
 * RD_BP1658CJ.c
 *
 *  Created on: Mar 18, 2021
 *      Author: DangHao
 */

/*
 * OUT1--B byte2-3
 * OUT2--G byte4-5
 * OUT3--R byte7-8
 * OUT4--Y byte9-10
 * OUT5--W byte11-12
 */
#include "RD_BP1658CJ.h"
static uint8_t Byte0 = 0xB0;  // 0b10110000 control 5 OUTPUT CCTRGB, Farme 11byte
static uint8_t Byte1 = 0x00;
static uint8_t Byte2_11[10] = {0} ; // lightness
void RD_BP1658_Init(Imax_CCT Imax_CCT_Set, Imax_RGB Imax_RGB_Set)
{
	Byte1 = Imax_RGB_Set | Imax_CCT_Set;
}

// Lightness of Yellow anh White , max 1024
void RD_BP1685_Control_CCT(uint16_t LightnessWhite, uint16_t LightnessYellow)
{
	if(LightnessWhite  >=1024)  LightnessWhite  = 1024;  	// max 1024, min 0
	if(LightnessYellow >= 1024) LightnessYellow = 1024;
	// White
		Byte2_11[8] = LightnessWhite &  0x1F;      			//5bit LOW
		Byte2_11[9] = (LightnessWhite >> 8) & 0x1F; 		// 5 bit HIGHT
	// YELLOW
		Byte2_11[6] = LightnessYellow & 0x1F;				// 5 bit LOW
		Byte2_11[7] = (LightnessYellow >> 8) & 0x1F;		// 5 bit Higt

		I2CWrite(Byte0, Byte1, Byte2_11)  					// send Control data
	//HAL_I2C_Mem_Write(&hi2c2, 0xB0, 0x01, 1, Byte2_11, 10, 1000);  // 5ma
}

void RD_BP1685_Control_RGB(uint16_t LightnessRed, uint16_t LightnessGreen, uint16_t LightnessBlue)
{
	if(LightnessRed   >= 1024) LightnessRed   = 1024;  		// max 1024, min 0
	if(LightnessGreen >= 1024) LightnessGreen = 1024;
	if(LightnessBlue >= 1024)  LightnessBlue  = 1024;
	// Blue
		Byte2_11[0] = LightnessBlue &  0x1F;      			//5bit LOW
		Byte2_11[1] = (LightnessBlue >> 8) & 0x1F;			// 5 bit HIGHT
	// Green
		Byte2_11[2] = LightnessGreen & 0x1F;				// 5 bit LOW
		Byte2_11[3] = (LightnessGreen >> 8) & 0x1F;			// 5 bit Higt
	// Red
		Byte2_11[4] = LightnessRed & 0x1F;				// 5 bit LOW
		Byte2_11[5] = (LightnessRed >> 8) & 0x1F;			// 5 bit Higt

		I2CWrite(Byte0, Byte1, Byte2_11)  					// send Control data
		//HAL_I2C_Mem_Write(&hi2c2, 0xB0, 0x01, 1, Byte2_11, 10, 1000);  // 5ma
}

void RD_BP1685_Control_CCT_RGB(uint16_t LightnessWhite, uint16_t LightnessYellow, uint16_t LightnessRed, uint16_t LightnessGreen, uint16_t LightnessBlue)
{
	if(LightnessWhite  >= 1024) LightnessWhite  = 1024;  	// max 1024, min 0
	if(LightnessYellow >= 1024) LightnessYellow = 1024;
	if(LightnessRed    >= 1024) LightnessRed    = 1024;
	if(LightnessGreen  >= 1024) LightnessGreen  = 1024;
	if(LightnessBlue   >= 1024) LightnessBlue   = 1024;

	// Blue
		Byte2_11[0] = LightnessBlue &  0x1F;      			//5bit LOW
		Byte2_11[1] = (LightnessBlue >> 8) & 0x1F;			// 5 bit HIGHT
	// Green
		Byte2_11[2] = LightnessGreen & 0x1F;				// 5 bit LOW
		Byte2_11[3] = (LightnessGreen >> 8) & 0x1F;			// 5 bit Higt
	// Red
		Byte2_11[4] = LightnessRed & 0x1F;					// 5 bit LOW
		Byte2_11[5] = (LightnessRed >> 8) & 0x1F;			// 5 bit Higt
	// White
		Byte2_11[8] = LightnessWhite &  0x1F;      			// 5bit LOW
		Byte2_11[9] = (LightnessWhite >> 8) & 0x1F; 		// 5 bit HIGHT
	// YELLOW
		Byte2_11[6] = LightnessYellow & 0x1F;				// 5 bit LOW
		Byte2_11[7] = (LightnessYellow >> 8) & 0x1F;		// 5 bit Higt

		I2CWrite(Byte0, Byte1, Byte2_11)
}

void RD_BP1685_Control_OffAll()
{

	// Blue
		Byte2_11[0] = 0x00;
		Byte2_11[1] = 0x00;
	// Green
		Byte2_11[2] = 0x00;
		Byte2_11[3] = 0x00;
	// Red
		Byte2_11[4] = 0x00;
		Byte2_11[5] = 0x00;
	// White
		Byte2_11[8] = 0x00;
		Byte2_11[9] = 0x00;
	// YELLOW
		Byte2_11[6] = 0x00;
		Byte2_11[7] = 0x00;
		I2CWrite(Byte0, Byte1, Byte2_11)
}

//for(int i=0; i<=1000 ; i++)
//{
//	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	  HAL_I2C_Mem_Write(&hi2c2, 0xB0, 0x06, 1, data1, 10, 1000);  // 30ma
//	  HAL_Delay(30);
//}

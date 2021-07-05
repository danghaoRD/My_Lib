#ifndef __PRF_H__
#define __PRF_H__

#include "main.h"

#define	PRF_REG_RD				0x80

#define	PRF_SCSB_H		HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_SET)
#define	PRF_SCSB_L		HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_RESET)

//#define	PRF_RSTB_H		HAL_GPIO_WritePin(SPI_RST_GPIO_Port, SPI_RST_Pin, GPIO_PIN_SET)
//#define	PRF_RSTB_L		HAL_GPIO_WritePin(SPI_RST_GPIO_Port, SPI_RST_Pin, GPIO_PIN_RESET)

#define	PRF_SCK_H		HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_SET)
#define	PRF_SCK_L		HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_RESET)

#define	PRF_MOSI_H		HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_SET)
#define	PRF_MOSI_L		HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_RESET)

#define	PRF_MISO		HAL_GPIO_ReadPin(SPI_MISO_GPIO_Port, SPI_MISO_Pin)
#define SpiDelay()

void PrfWrRegPtr_U16(uint8_t reg, uint16_t Value);
void PrfWrRegPtr(uint8_t reg, uint8_t *ptr, uint8_t len);
void PrfRdRegPtr(uint8_t reg, uint8_t *ptr, uint8_t len);
//void PrfPortInit(void);
void SpiWr8(uint8_t dat);
uint8_t SpiRd8(void);

void PrfWrRegPtr(uint8_t reg, uint8_t *ptr, uint8_t len)	// wire len byte data to regsigter
{
	uint8_t i;

	PRF_SCSB_L;
	SpiWr8(reg);
	for(i=0;i<len;i++)
	{
		SpiWr8(*ptr++);
	}
	PRF_SCSB_H;
}

void PrfWrRegPtr_U16(uint8_t reg, uint16_t Value)					// wire 16 bit data to regsigter
{
	PRF_SCSB_L;
	SpiWr8(reg);
	SpiWr8(((Value>>8)&0x00FF));
	SpiWr8(  Value    &0x00FF );
	PRF_SCSB_H;
}

void PrfRdRegPtr(uint8_t reg, uint8_t *ptr, uint8_t len)	// read data to regsigter
{
	uint8_t i;

	PRF_SCSB_L;
	SpiWr8(reg|PRF_REG_RD);
	for(i=0;i<len;i++)
	{
		*ptr++ = SpiRd8();
	}
	PRF_SCSB_H;
}

//void PrfPortInit(void)																		// Init Pin RS=0, SC=1;
//{
////	P1M0 |= BIT5|BIT3|BIT2|BIT1;	//RSTB|SCSB|SCK|MOSI
////	P1M0 &= ~(BIT6|BIT4|BIT0);		//PKT|FIFO|MISO
//
//	PRF_RSTB_L;
//	PRF_SCSB_H;
//}

void SpiWr8(uint8_t dat)																	// wire 8 bit data
{
 	uint8_t i;

	for(i=0; i<8; i++)
	{

		if((dat&0x80)==0x80)
			PRF_MOSI_H;
		else
			PRF_MOSI_L;
		PRF_SCK_H;
		SpiDelay();
		PRF_SCK_L;
		SpiDelay();
		dat <<= 1;
	}
	PRF_MOSI_L;
}

uint8_t SpiRd8(void)																			// read 8bit data
{
  uint8_t dat;
	uint8_t i;

	for(i=0; i<8; i++)
	{
		PRF_SCK_H;           	// lay suong xuong CPHA=1
		dat <<= 1;						// doc MSB
		SpiDelay();
		PRF_SCK_L;
		SpiDelay();
		if(PRF_MISO)
			dat |= 0x01;				// lay giá tri 1 bit vua doc duoc roi ghi vào bit dau tien cua dat
	}
	return dat;
}

#endif

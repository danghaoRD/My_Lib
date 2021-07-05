#ifndef __PRF_H__
#define __PRF_H__

#include "main.h"

const uint8_t PrfRegAddrTab[]=
{
  0,1,2,4,5,7,8,9,10,11,12,13,22,23,24,25,26,
  27,28,32,33,34,35,36,37,38,39,40,41,42,43
};

//const uint16_t PrfRegTab[]=
//{
///*00*/0x6FE0,
///*01*/0x5681,
///*02*/0x6617,
///*04*/0xB1A0,
///*05*/0xC000,
///*07*/0x0030,
///*08*/0x6C91,
///*09*/0x1840,  //0x4010,
///*10*/0x7FFD,
///*11*/0x0008,
///*12*/0x0000,
///*13*/0x48DB,
///*22*/0xC0FF,
///*23*/0x8005,
///*24*/0x0067,
///*25*/0x1659,
///*26*/0x19E0,
///*27*/0x1300,
///*28*/0x1800,
///*32*/0x4800,
///*33*/0x3FC7,
///*34*/0x2000,
///*35*/0x0380,
////Begin Syncword
///*36*/0x4231,
///*37*/0x8575,
///*38*/0x9A0B,
///*39*/0xDECF,
////End syncword
///*40*/0x4401,
///*41*/0xB400,
///*42*/0xFDB0,
///*43*/0x000F
//};

const uint16_t PrfRegTab[]=
{
0x6FE0,
0x5681,
0x6617,
0x9CC9,
0x6637,
0x0007,
0x6C90,
0x4800,
0x7FFD,
0x0008,
0x0000,
0x48BD,
0x00FF,
0x8005,
0x0067,
0x1659,
0x19E0,
0x1200,
0x1800,
0x4000,
0x3FC7,
0x2000,
0x0F20,
0x1003,
0x0853,
0x1DBC,
0x6E97,
0x4401,
0xB000,
0xFDB0,
0x000F
};

#define SpiDelay() 
#define PRF_INIT_TAB_LEN	    31

//Prf register map
#define PRF_RF_SYN_LOCK				0x03	//RF Synthesizer Lock Status Register
#define PRF_RAW_RSSI				0x06	//RAW RSSI Value Register
#define PRF_TX_RX_CH				0x07	//TX/RX Enable and Channel Register
#define PRF_PA_CTR					0x09	//PA Control Register
#define PRF_RSSI_OFF				0x0B	//RSSI OFF Control Register
#define PRF_EN_VCO_CAL				0x17	//VCO Calibration Enable Register
#define PRF_DAT_CFG					0x20	//Data Configure Register
#define PRF_DLY_TM_CTR0				0x21	//Delay Time Control Register 0
#define PRF_DLY_TM_CTR1				0x22	//Delay Time Control Register 1
#define PRF_PM_MISC					0x23	//Power Management and Miscellaneous Register
#define PRF_SYNCWORD0				0x24	//SYNCWORD Register 0
#define PRF_SYNCWORD1				0x25	//SYNCWORD Register 1
#define PRF_SYNCWORD2				0x26	//SYNCWORD Register 2
#define PRF_SYNCWORD3				0x27	//SYNCWORD Register 3
#define PRF_FIFO_SYNWORD_TH			0x28	//FIFO and SYNCWORD Threshold Register
#define PRF_MISC					0x29	//Miscellaneous Register
#define PRF_SCAN_RSSI0				0x2A	//SCAN RSSI Register 0
#define PRF_SCAN_RSSI1				0x2B	//SCAN RSSI Register 1
#define PRF_STATUS					0x30	//Status Register
#define PRF_FIFO_DAT				0x32	//FIFO Data Register
#define PRF_FIFO_PTR				0x34	//FIFO Pointer Register
//Prf read regster address = (REG_ADDR|PRF_REG_RD)
#define	PRF_REG_RD				0x80
//pa gain
#define PRF_PA_GAIN_MASK				0x0780
#define PRF_PA_GAIN_BIS				0x07
#define PRF_PA_GAIN_P5DBM			0x00
#define PRF_PA_GAIN_N15DBM			0x0F
//crc
#define PRF_STATUS_CRC_MASK			0x8000
#define PRF_STATUS_CRC_ERR			0x8000
#define PRF_STATUS_CRC_OK			0x0000
//rssi
#define PRF_RAW_RSSI_MASK			0xFC00
#define PRF_RAW_RSSI_BIS				0x0A
//ptr
#define PRF_FIFO_WR_PTR_MASK			0x3F00
#define PRF_FIFO_WR_PTR_BIS			0x08
#define PRF_FIFO_RD_PTR_MASK			0x003F
#define PRF_FIFO_RD_PTR_BIS			0x00

#define	TX_ENABLE	(1L<<0x08)
#define	RX_ENABLE	(1L<<0x07)

#define CLR_W_PTR		0x8000
#define CLR_R_PTR		0x0080
#define CLR_WR_PTR		0x8080

#define PRF_IDLE	0x00
#define PRF_RX		0x01
#define PRF_TX		0x02


#define	PRF_SCSB_H	HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_SET)
#define	PRF_SCSB_L	HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_RESET)

#define	PRF_RSTB_H	HAL_GPIO_WritePin(SPI_RST_GPIO_Port, SPI_RST_Pin, GPIO_PIN_SET)
#define	PRF_RSTB_L	HAL_GPIO_WritePin(SPI_RST_GPIO_Port, SPI_RST_Pin, GPIO_PIN_RESET)

#define	PRF_SCK_H		HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_SET)
#define	PRF_SCK_L		HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_RESET)

#define	PRF_MOSI_H	HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_SET)
#define	PRF_MOSI_L	HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_RESET)

#define	PRF_MISO		HAL_GPIO_ReadPin(SPI_MISO_GPIO_Port, SPI_MISO_Pin)



void PrfInit(void);
void PrfSetModeCh(uint8_t mode, uint8_t ch);
void PrfWrFifo(uint8_t *ptr, uint8_t len);
void PrfRdFifo(uint8_t *ptr, uint8_t len);
void PrfClrTxRxPtr(void);
void PrfSleep(void);
void PrfWakeup(void);
void PrfSetRx(void);
void PrfTxPtr(uint8_t *ptr, uint8_t ch);

void PrfWrRegPtr_U16(uint8_t reg, uint16_t Value);
void PrfWrRegPtr(uint8_t reg, uint8_t *ptr, uint8_t len);
void PrfRdRegPtr(uint8_t reg, uint8_t *ptr, uint8_t len);
void PrfPortInit(void);
void SpiWr8(uint8_t dat);
uint8_t SpiRd8(void);

void PrfDemoInit(void);
void PrfRxDemoProc(void);
void PrfTxDemoProc(void);

#define PRF_TXBUF_SIZE 48
#define PRF_RXBUF_SIZE 48

typedef struct
{
	uint8_t rssi;
	uint8_t ch;
	uint8_t sta;
	uint8_t txpwr;
	uint8_t txbuf[PRF_TXBUF_SIZE];
	uint8_t rxbuf[PRF_RXBUF_SIZE];
}prf_t;

prf_t Prf;

void PrfInit(void)												// Init Optimum value to 31 reg
{
	uint8_t i;
	uint8_t reg;
	uint8_t regval[2];

	PrfPortInit();
	HAL_Delay(10);
	PRF_RSTB_H;
	HAL_Delay(10);
	
	for(i=0;i<PRF_INIT_TAB_LEN;i++)
	{
		reg = PrfRegAddrTab[i];
		regval[0] = PrfRegTab[i]>>8;
		regval[1] = PrfRegTab[i];
		PrfWrRegPtr(reg, regval, 2);
		SpiDelay(); 
		SpiDelay(); 
	}
}

void PrfSetModeCh(uint8_t mode, uint8_t ch) // Set mode Tx, Rx, channel 
{
	uint16_t Temp;
	uint8_t regval[2];
	
	Temp = mode<<7;														// mode là bien cai dat che do hoat dong Tx/Rx
	Temp |= ch;																// ch la bien cai dat tan so (channel) hoat dong cua thiet bi
	regval[0] = Temp>>8;											// MSB
	regval[1] = Temp;			
	PrfWrRegPtr(PRF_TX_RX_CH, regval, 2);			// PRF_TX_RX :0x07 là thanh ghi cau hinh TX/RX va channel
}

void PrfWrFifo(uint8_t *ptr, uint8_t len)
{
	PrfWrRegPtr(PRF_FIFO_DAT, ptr, len);
}

void PrfRdFifo(uint8_t *ptr, uint8_t len)
{
	PrfRdRegPtr(PRF_FIFO_DAT|PRF_REG_RD, ptr, len);
}

void PrfClrTxRxPtr(void)										// clear Tx, Rx poiter to 0
{
	uint16_t Temp;
	uint8_t regval[2];
	
	Temp = CLR_WR_PTR;												// 0x34 Tx_Rx poiter Resigter
	regval[0] = Temp>>8;
	regval[1] = Temp;
	PrfWrRegPtr(PRF_FIFO_PTR, regval, 2);  		// clear Tx, Rx poiter to 0
}

void PrfSetRx(void)
{
	PrfSetModeCh(PRF_IDLE, Prf.ch);
	PrfClrTxRxPtr();
	PrfSetModeCh(PRF_RX, Prf.ch);
}

void PrfSleep(void)
{
	uint8_t regval[2];
	
	regval[0] = 0xC3;
	regval[1] = 0x80;
	//regval.u16 = 0xC3;
	PrfWrRegPtr(PRF_PM_MISC, regval, 2);
}

void PrfWakeup(void)
{
	uint16_t i;
	
	PRF_SCSB_L;
	for(i=0;i<2000;i++);
}

void PrfTxPtr(uint8_t *ptr, uint8_t ch)
{
//	uint16_t tm;
	
	if(ptr[0]<PRF_TXBUF_SIZE)
	{
		PrfSetModeCh(PRF_IDLE, ch);
		PrfClrTxRxPtr();
		PrfWrFifo(ptr, (ptr[0]+1));
		PrfSetModeCh(PRF_TX, ch);
//		tm = 0;
		//while(PRF_PKT)
		{
//			tm++;
//			if(tm>5000);
//				break;
		}
//		for(;tm<5000;tm++);
	}
}

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

void PrfPortInit(void)																		// Init Pin RS=0, SC=1;
{
//	P1M0 |= BIT5|BIT3|BIT2|BIT1;	//RSTB|SCSB|SCK|MOSI
//	P1M0 &= ~(BIT6|BIT4|BIT0);		//PKT|FIFO|MISO

	PRF_RSTB_L;
	PRF_SCSB_H;
}

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


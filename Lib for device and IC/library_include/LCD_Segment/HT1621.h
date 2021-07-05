/*
 * HT1621.h
 *
 *  Created on: Oct 13, 2020
 *      Author: DangVanHao  RangDong
 *      HT1621 V1.0   15h date 13/10/20
 *      Thư viện điều khiển IC HT1621 cho màn hình Sengment LCD. sử dụng 3 chân từ vđk
 *      WR, DATA, CS
 *      LCD nối tới IC bằng 4 chân COM và x chân SEG (tùy vào mcuj đích sử dụng)
 */

#ifndef INC_HT1621_H_
#define INC_HT1621_H_
#include "stm32f1xx_hal.h"
#include "main.h"

//Define mode
#define  COMMAND_MODE 			0b10000000 /*!< This is used FOR sending standard commands. */
#define  READ_MODE  			0b11000000 /*!< This instructs the HT1621 to prepare FOR reading the internal RAM. */
#define  WRITE_MODE  			0b10100000 /*!< This instructs the HT1621 to prepare FOR writing the internal RAM. */
#define  READ_MODIFY_WRITE_MODE 0b10100000 /*!< This instructs the HT1621 to prepare FOR reading/modifying batch of internal RAM adresses. */
#define  SPECIAL_MODE  			0b10010000 /*!< This instructs the HT1621 to prepare FOR executing a special command. */

//Define command
#define COMMAND_SYS_DIS    0b00000000 /*!< System disable. It stops the bias generator and the system oscillator. */
#define COMMAND_SYS_EN     0b00000010 /*!< System enable. It starts the bias generator and the system oscillator. */
#define COMMAND_LCD_OFF    0b00000100 /*!< Turn off the bias generator. */
#define COMMAND_LCD_ON     0b00000110 /*!< Turn on the bias generator. */
#define COMMAND_TIMER_DIS  0b00001000 /*!< Disable time base output. */
#define COMMAND_WDT_DIS    0b00001010 /*!< Watch-dog timer disable. */
#define COMMAND_TIMER_EN   0b00001100 /*!< Enable time base output. */
#define COMMAND_WDT_EN     0b00001110 /*!< Watch-dog timer enable. The timer is reset. */
#define COMMAND_CLR_TIMER  0b00011000 /*!< Clear the contents of the time base generator. */
#define COMMAND_CLR_WDT    0b00011100 /*!< Clear the contents of the watch-dog stage. */
#define COMMAND_TONE_OFF   0b00010000 /*!< Stop emitting the tone signal at the tone pin. \sa TONE2K, TONE4K */
#define COMMAND_TONE_ON    0b00010010 /*!< Start emitting tone signal at the tone pin. Tone frequency is selected using commands TONE2K or TONE4K. \sa TONE2K, TONE4K */
#define COMMAND_TONE2K     0b11000000 /*!< Output tone is at 2kHz. */
#define COMMAND_TONE4K     0b10000000 /*!< Output tone is at 4kHz. */
#define COMMAND_RC256K     0b00110000 /*!< System oscillator is the internal RC oscillator at 256kHz. */
#define COMMAND_XTAL32K    0b00101000 /*!< System oscillator is the crystal oscillator at 32768Hz. */
#define COMMAND_EXT256K    0b00111000 /*!< System oscillator is an external oscillator at 256kHz. */

//Set bias to 1/2 or 1/3 cycle

//Set to 2,3 or 4 connected COM lines
#define COMMAND_BIAS_HALF_2_COM   0b01000000 /*!< Use 1/2 bias and 2 commons. */
#define COMMAND_BIAS_HALF_3_COM   0b01001000 /*!< Use 1/2 bias and 3 commons. */
#define COMMAND_BIAS_HALF_4_COM   0b01010000 /*!< Use 1/2 bias and 4 commons. */
#define COMMAND_BIAS_THIRD_2_COM  0b01000010 /*!< Use 1/3 bias and 2 commons. */
#define COMMAND_BIAS_THIRD_3_COM  0b01001010 /*!< Use 1/3 bias and 3 commons. */
#define COMMAND_BIAS_THIRD_4_COM  0b01010010 /*!< Use 1/3 bias and 4 commons. */
#define COMMAND_IRQ_EN     0b00010000 /*!< Enables IRQ output. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_IRQ_DIS    0b00010000 /*!< Disables IRQ output. This needs to be excuted in SPECIAL_MODE. */

// WDT configuration commands
#define COMMAND_F1  0b01000000 /*!< Time base/WDT clock. Output = 1Hz. Time-out = 4s. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_F2  0b01000010 /*!< Time base/WDT clock. Output = 2Hz. Time-out = 2s. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_F4  0b01000100 /*!< Time base/WDT clock. Output = 4Hz. Time-out = 1s. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_F8  0b01000110 /*!< Time base/WDT clock. Output = 8Hz. Time-out = .5s. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_F16  0b01001000 /*!< Time base/WDT clock. Output = 16Hz. Time-out = .25s. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_F32  0b01001010 /*!< Time base/WDT clock. Output = 32Hz. Time-out = .125s. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_F64  0b01001100 /*!< Time base/WDT clock. Output = 64Hz. Time-out = .0625s. This needs to be excuted in SPECIAL_MODE. */
#define COMMAND_F128  0b01001110 /*!< Time base/WDT clock. Output = 128Hz. Time-out = .03125s. This needs to be excuted in SPECIAL_MODE. */

//Don't use
#define COMMAND_TEST_ON    0b11000000 /*!< Don't use! Only FOR manifacturers. This needs SPECIAL_MODE. */
#define COMMAND_TEST_OFF   0b11000110  /*!< Don't use! Only FOR manifacturers. This needs SPECIAL_MODE. */
#define uchar   unsigned char
#define uint   unsigned int16

// //Define port    HT1621 data port
//#define CS    HAL_GPIO//Pin 2 as chip selection output
//#define WR   PIN_B4  //Pin 3 as read clock  output
//#define DATA PIN_B3 //Pin 4 as Serial data output Khong dung duoc C4


#define CSH   	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);		//digitalWrite(CS, HIGH)
#define CSL   	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);	//digitalWrite(CS, LOW)
#define WRH   	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_SET);		//digitalWrite(WR, HIGH)
#define WRL   	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_RESET);	//digitalWrite(WR, LOW)
#define DATAH 	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET);	//digitalWrite(DATA, HIGH)
#define DATAL  	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);//digitalWrite(DATA, LOW)

void delay_us(uint16_t Time_us);
void SendBit_1621 (uchar sdata, uchar cnt);
void SendCmd_1621(uchar command);
void Write_1621(uchar addr, uchar sdata);
void HT1621_all_off(uchar num_small);
void HT1621_all_on(uchar num_small);
void HT1621_all_on_num(uchar num_small, uchar xx);
void Init_1621(void);
void LCDoff(void);
void LCDon(void);
void displayallnum(unsigned int n);
void displayall8(void);
void displaydata(uint16_t t);
void stop_display();
#endif /* INC_HT1621_H_ */

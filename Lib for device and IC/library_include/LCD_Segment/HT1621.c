/*
 * HT1621.c
 *
 *  Created on: Oct 13, 2020
 *      Author: Dang Van Hao
 */

#include "HT1621.h"
TIM_HandleTypeDef htim2;
char dispnum[3] = {0x00, 0x00, 0x00};
const char num_small[] = {0b10111111, 0b00000110, 0b01111101, 0b01011110, 0b11000110, 0b11011010, 0b11111010, 0b00001110, 0b11111110, 0b11011110};//LCD loai nho
const       char num[] = {0b01011111, 0b00000110, 0b01101011, 0b00101111, 0b00110110, 0b00111101, 0b01111101, 0b00000111, 0b01111111, 0b00111111};

void delay_us(uint16_t Time_us)
{
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while(__HAL_TIM_GET_COUNTER(&htim2) <= Time_us);
}
/*Name: SendBit_1621 (send data)
---------------------------------------------------------------------------*/
void SendBit_1621 (uchar sdata, uchar cnt) //High bit first
{
   uchar i;
   for (i = 0; i < cnt; i++)
   {
      WRL									//
      delay_us(20);
      if (sdata & 0x80) DATAH
      else DATAL
      delay_us(20);
      WRH
      delay_us(20);
      sdata <<= 1;
   }
   delay_us(20);

}

/**-------------------------------------------------------------------------

         Name: SendCmd(send cmd)
         //Write MODE"100" AND 9 bits command
---------------------------------------------------------------------------*/

void SendCmd_1621(uchar command)
{
   CSL
   SendBit_1621 (0x80, 4);
   SendBit_1621 (command, 8);
   CSH
}

/**-------------------------------------------------------------------------

         Name: Write_1621send data and cmd)
---------------------------------------------------------------------------*/

void Write_1621(uchar addr, uchar sdata)
{
   addr <<= 3;
   CSL
   SendBit_1621(0xa0, 3);    //Write MODE"101"
   SendBit_1621(addr, 6);    //Write addr high 6 bits
   SendBit_1621(sdata, 8);   //Write data  8 bits
   CSH
}


/**-------------------------------------------------------------------------

            Name: all_off(Clear Display)
---------------------------------------------------------------------------*/

void HT1621_all_off(uchar num_small)
{ uchar i;
   uchar addr = 0;
   for (i = 0; i < num_small; i++)
   {
      Write_1621(addr, 0x00);
      addr += 1;
   }
}
/****************************************************************************

            Name: all_on(All lit)
****************************************************************************/

void HT1621_all_on(uchar num_small)
{
   uchar i;//, j;
   uchar addr = 0;
   for (i = 0; i < num_small; i++)
   { Write_1621(addr, 0xff);
      addr += 1;
   }
}      /****************************************************************************

                  Name: all_on_num(All lit,Display the same number)
****************************************************************************/

void HT1621_all_on_num(uchar num_small, uchar xx)
{
   uchar i;//, j;
   uchar addr = 0;
   for (i = 0; i < num_small; i++)
   { Write_1621(addr, xx);
      addr += 1;
   }
}

/****************************************************************************

            Name: Init_1621(initialize 1621)
*****************************************************************************/

void Init_1621(void)
{
   SendCmd_1621(COMMAND_SYS_EN);  				/*!< System enable. It starts the bias generator and the system oscillator. */
   SendCmd_1621(COMMAND_RC256K);				/*!< System oscillator is the internal RC oscillator at 256kHz. */
   SendCmd_1621(COMMAND_BIAS_THIRD_4_COM);		/*!< Use 1/3 bias and 4 commons. */
   SendCmd_1621(COMMAND_LCD_ON);				/*!< Turn on the bias generator. */
}
/****************************************************************************

            Name: LCDoff_1(off 1621)
*****************************************************************************/

void LCDoff(void)
{
   SendCmd_1621(COMMAND_LCD_OFF);
}
/****************************************************************************

            Name: LCDon_1(on 1621)
*****************************************************************************/

void LCDon(void)
{
   SendCmd_1621(COMMAND_LCD_ON);
}


void displayallnum(unsigned int n)       //Display all digital characters
{// uchar i, j;
   uchar addr = 0;

   for (int i = 0; i < n; i++)
   { for (int j = 0; j < 27; j++)
      {
         Write_1621(addr, num_small[j]);
         HAL_Delay(100);		//delay_ms(100) ;
      }
      addr += 1;
   }

}


//By-bit display 8 characters and decimal point
void displayall8(void)
{ uchar i;
   HT1621_all_off(16);
   for (i = 0; i < 16; i++)
   {
      Write_1621(i, 0b11110111);
      HAL_Delay(50);
   }
}

//

/****************************************************************************

Name: displaydata_1(unsigned long int t) Display  data
t : Data to be displayed

*****************************************************************************/

void displaydata(uint16_t t)
{
   dispnum[0] = num_small[(t / 100)%10];
   dispnum[1] = num_small[(t / 10)%10];
   dispnum[2] = num_small[(t%10)];
   if(t>=100) Write_1621(0, dispnum[0]);
   else Write_1621(0, 0);
   if(t>=10)  Write_1621(1, dispnum[1]);
   else Write_1621(1, 0);
   if(t>=0)Write_1621(2, dispnum[2]);

   //!    uchar i;
   //!  for (i = 0; i < 3 ; i++)
   //!  {
   //!    Write_1621_1(i, dispnum[i]);
   //!  }
}


void stop_display()
{
 SendCmd_1621(COMMAND_LCD_OFF);
 SendCmd_1621(COMMAND_SYS_DIS);
}




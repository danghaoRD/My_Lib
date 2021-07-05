/* Dang Hao ---- K57 dh GTVT */
#include "stm32f1xx_hal.h"
 
void LCD_Enable(void);  

void LCD_Send4Bit(unsigned char Data);

void LCD_SendCommand(unsigned char command);

void LCD_Clear(void);

void LCD_Init(void);

void LCD_Gotoxy(unsigned char x, unsigned char y);

void LCD_PutChar(unsigned char Data);

void LCD_Puts(char *s); 
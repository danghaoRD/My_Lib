/* Dang Hao --K57_UTC-- RANG DONG */
/*LCD_5110C V1.0
	27/07/2020   */
#include "stm32f1xx_hal.h" 
void LCD_5110C_SendCommand(uint8_t com);
void LCD_5110C_SendData(uint8_t data);
void LCD_5110C_Reset();
void LCD_5110C_Set_Position(uint8_t PosX, uint8_t PosY);
void LCD_5110C_Init();
void LCD_5110C_Clear();
void LCD_5110C_WriteChar(uint8_t ch);
void LCD_5110C_WriteString(char *str);

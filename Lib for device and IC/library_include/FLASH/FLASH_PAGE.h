/*
 * FLASH_PAGE.h
 *
 *  Created on: 08-May-2020
 *      Author: controllerstech
 *
 *
 *      22/05/2020    Đ.V.Hào (k57 UTC) first edited line 18.  __IO --> volatile (or without __IO)
 *      23/May/2020   Đ.V.Hào (k57 UTC) add Flash_Erase.
 */

#ifndef INC_FLASH_PAGE_H_
#define INC_FLASH_PAGE_H_

#include "stm32f1xx_hal.h"


uint32_t Flash_Write_Data (uint32_t StartPageAddress, uint32_t * DATA_32);
void Flash_Read_Data (uint32_t StartPageAddress,   uint32_t * DATA_32);
void Convert_To_Str (uint32_t *data, char *str);
void Flash_Erase(uint32_t addr);


/********************  FLASH_Error_Codes   ***********************//*
HAL_FLASH_ERROR_NONE      0x00U  // No error
HAL_FLASH_ERROR_PROG      0x01U  // Programming error
HAL_FLASH_ERROR_WRP       0x02U  // Write protection error
HAL_FLASH_ERROR_OPTV      0x04U  // Option validity error
*/


#endif /* INC_FLASH_PAGE_H_ */

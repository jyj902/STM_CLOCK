/*
 * flash.c
 *
 *  Created on: Jan 19, 2021
 *      Author: s02
 */
#include "main.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "flash.h"

//extern
extern TimeTypeDef ctime;  // current time
extern TimeTypeDef stime; // setting time
extern TimeTypeDef atime;  // alarm time
NVitemTypeDef default_nvitem =
{
  MAGIC_NUM,
  {0,0,0},
  {0,0,0},
  0
};
void load_nvitems()
{
	uint32_t load_addr = ADDR_FLASH_SECTOR_8;/*
	default_nvitem.setting_time.hours = (*(uint8_t*)load_addr+4);
	default_nvitem.setting_time.minutes = (*(uint8_t*)load_addr+5);
	default_nvitem.setting_time.seconds = (*(uint8_t*)load_addr+6);*/
	ctime.hours = (*((uint8_t*)load_addr+4));
	ctime.minutes = (*((uint8_t*)load_addr+5));
	ctime.seconds = (*((uint8_t*)load_addr+6))
			;
}
HAL_StatusTypeDef update_nvitems(void)
{
	uint32_t FirstSector,NbOfSectors,SECTORError;
	FLASH_EraseInitTypeDef EraseInitStruct;
	HAL_StatusTypeDef error= HAL_OK;
    uint32_t Address,i;
    uint64_t Data;
    uint8_t *ptr;

	HAL_FLASH_Unlock();
	FirstSector = FLASH_SECTOR_8;
	NbOfSectors = 1;

	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector        = FirstSector;
	EraseInitStruct.NbSectors     = NbOfSectors;

	error = HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
	if(error != HAL_OK)
	{
		return error;
	}

	ptr = (uint8_t*)&default_nvitem;

	for(i=0;i<sizeof(NVitemTypeDef);i++)
	{
		Address = (uint8_t*)nv_items+i;
		Data = *((uint8_t*)ptr+ i);
		error = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,Address,Data);
		if(error != HAL_OK)
		{
			return error;
		}
	}

	HAL_FLASH_Lock();
}

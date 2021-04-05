/*
 * music.c
 *
 *  Created on: Jan 21, 2021
 *      Author: s02
 */

#include "music.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>

extern DAC_HandleTypeDef hdac;
int melody[] =
{
	NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,
	NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
	NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,
	NOTE_C5,NOTE_C5,NOTE_C5,

	NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
	NOTE_G5,NOTE_G5,NOTE_G5,
	NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
	NOTE_G5,NOTE_G5,NOTE_G5,

	NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
	NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5,
	NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5,
	NOTE_E5,NOTE_D5,NOTE_C5
};
int noteDurations[]=
{
	4,8,8,4,4,
	4,8,8,4,4,
	8,8,4,8,8,4,
	4,4,2,
	4,4,4,4,
	4,4,2,
	4,4,4,4,
	4,4,2,
	4,4,4,4,
	8,8,8,8,2,
	4,4,4,4,
	4,
	4,2
};
int melody1[] =
{
	NOTE_G4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_G4, 0,
	NOTE_G4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, 0,
	NOTE_A4, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_B4, 0,
	NOTE_G5, NOTE_G5, NOTE_F5, NOTE_D5, NOTE_E5, NOTE_C5, 0
};

int noteDurations1[] =
{
	1, 1, 1, 1, 3, 1,
	1, 1, 1, 1, 3, 1,
	1, 1, 1, 1, 3, 1,
	1, 1, 1, 1, 2, 1, 1
};
int melody2[] =
{
	NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5,
	NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4,
	NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E4, NOTE_B4, NOTE_E5,
	NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4,
	NOTE_F5, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4,
	NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E4, NOTE_E4, NOTE_E4,
	NOTE_D4, NOTE_B3, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_B3, NOTE_E4,
	NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4
};
int noteDurations2[] =
{
	8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,4,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,
	8,8,8,8,8,1,
	8,8,8,8,4,4,4,8,4,4,8,8,8,8,4,8,8,4,8,4,8,8,4,8,4,1
};
void music_0()
{
    for (int i = 0; i < (sizeof(melody1)/sizeof(int)); i++)
    {
      int Durations = noteDurations1[i];
      int pauseBetweenNotes = Durations *2.7 ;
  	  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, melody1[i]);
  	  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  	  HAL_Delay(Durations*50);
  	  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, 0);
  	  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  	  HAL_Delay(pauseBetweenNotes*50);
   }

}

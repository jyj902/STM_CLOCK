/*
 * adc.h
 *
 *  Created on: Jan 19, 2021
 *      Author: s02
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"

#define DOUBLE_CLICK_MIN 50
#define DOUBLE_CLICK_MAX 150
#define NORMAL_CLICK_MIN 500
#define LONG_CLICK_MIN 1500
#define LONG_CLICK_MAX 5000
#define LCD_DELAY_MS 5

ADC_HandleTypeDef hadc1;

typedef struct{
  uint16_t time;
  GPIO_PinState level;
}ClickInfoDef;

enum CLICK
{
	NORMAL,
	DOUBLE,
	LONG
};
enum KEY
{
	UP_btn,
	DOWN_btn,
	LEFT_btn,
	RIGHT_btn,
	SEL_btn
};
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
int ADC_key();
void Folling_ADC();

#endif /* INC_ADC_H_ */

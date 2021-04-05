/*
 * adc.c
 *
 *  Created on: Jan 19, 2021
 *      Author: s02
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "tim.h"
#include "flash.h"
ClickInfoDef click[3];
uint8_t old_key, user_btn = -1, y, key_w;
int8_t x;
uint16_t key_value;
uint32_t last_time,current_time,time_interval, last_time_interval;

enum BT_kEY
{
	BT_LEFT =1,
	BT_RIGHT,
	BT_UP,
	BT_DOWN,
	BT_ONE,
	BT_DOUBLE,
	BT_LONG
};

//extern
extern TimeTypeDef ctime;  // current time
extern TimeTypeDef stime; // setting time
extern TimeTypeDef atime;  // alarm time
extern struct clock_state current_state;
extern NVitemTypeDef default_nvitem;
extern uint8_t BT_buffer[10];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	GPIO_PinState pin;
	if (GPIO_Pin == GPIO_PIN_13)
	{
		current_time = HAL_GetTick();
		time_interval = current_time - last_time;
		last_time = current_time;
		pin = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
		if (time_interval <= 2)
		{
		}
		else
		{
			click[2].time = click[1].time;
			click[2].level = click[1].level;
			click[1].time = click[0].time;
			click[1].level = click[0].level;
			click[0].time = time_interval;
			click[0].level = pin;
			if (click[0].level == GPIO_PIN_RESET && click[0].time >= LONG_CLICK_MIN) // long click
			{
				user_btn = LONG;
			}
			else if (click[0].level == GPIO_PIN_RESET && click[0].time < LONG_CLICK_MIN && click[0].time > 75)
			{
				user_btn = NORMAL;
			}
			if (click[2].level == GPIO_PIN_RESET && click[1].level == GPIO_PIN_SET && click[0].level == GPIO_PIN_RESET)
			{
				volatile uint8_t i;
				for ( i = 0; i < 3; i++)
				{
					if ((click[i].time >= DOUBLE_CLICK_MIN) && (click[i].time <= DOUBLE_CLICK_MAX))
					{}
					else break;
				}
				if (i == 3)
				{
					user_btn = DOUBLE;
				}
			}
		}
	}

}
int ADC_key()
{
	key_value=HAL_ADC_GetValue(&hadc1);
	if(key_value<100) key_w = UP_btn;
	else if((key_value<1000)&&(key_value>500)) key_w = DOWN_btn;
	else if((key_value<2200)&&(key_value>1500)) key_w = LEFT_btn;
	else if((key_value<3200)&&(key_value>2500)) key_w = RIGHT_btn;
	else key_w =-1;
	return key_w;
}

void Folling_ADC()
{
	if(click[0].level ==GPIO_PIN_RESET)
	{
		if((user_btn == NORMAL)||(BT_buffer[0]==BT_ONE))
		{
			if(current_state.mode == NORMAL_STATE)
			{
				Clear();
				current_state.mode = TIME_SETTING;
			}
		}
		if((user_btn == DOUBLE)||(BT_buffer[0]==BT_DOUBLE))
		{
			noblink();
			if(current_state.mode == NORMAL_STATE)
			{
				Clear();
				current_state.mode = ALARM_TIME_SETTING;
			}
			else if(current_state.mode == TIME_SETTING)
			{
				Clear();
				current_state.mode = NORMAL_STATE;
				ctime = stime;
				default_nvitem.setting_time = stime;
				update_nvitems();
			}
			else if(current_state.mode == ALARM_TIME_SETTING)
			{
				Clear();
				current_state.mode = NORMAL_STATE;
				default_nvitem.alarm_time = atime;
			}
			else if(current_state.mode == MUSIC_SELECT)
			{
				Clear();
				current_state.mode = NORMAL_STATE;
				default_nvitem.alarm_music_num = x;
			}
		}
		if((user_btn == LONG)||(BT_buffer[0]==BT_LONG))
		{
			Clear();
			if(current_state.mode == NORMAL_STATE) current_state.mode = MUSIC_SELECT;
		}
		user_btn=-1;

	}
	uint8_t get_key;
	old_key = get_key;
	get_key = ADC_key();
	if(get_key != old_key)
	{
		if(current_state.mode == TIME_SETTING)
		{
			if((get_key == UP_btn)||(BT_buffer[0]==BT_UP))
			{
				if((y== 0)||(y==1)) stime.hours +=12;
				if(y==3) stime.hours +=10;
				if(y==4) stime.hours +=1;
				if(y==6) stime.minutes +=10;
				if(y==7) stime.minutes +=1;
				if(y==9) stime.seconds +=10;
				if(y==10) stime.seconds +=1;
			}
			if((get_key == DOWN_btn)||(BT_buffer[0]==BT_DOWN))
			{
				if((y== 0)||(y==1)) stime.hours -=12;
				if(y==3) stime.hours -=10;
				if(y==4) stime.hours -=1;
				if(y==6) stime.minutes -=10;
				if(y==7) stime.minutes -=1;
				if(y==9) stime.seconds -=10;
				if(y==10) stime.seconds -=1;
			}
			if((get_key == LEFT_btn)||(BT_buffer[0]==BT_LEFT))
			{
				if((--y)<0) y = 15;
			}
			if((get_key == RIGHT_btn)||(BT_buffer[0]==BT_RIGHT))
			{
				if((++y)>15) y = 0;

			}
		}
		if(current_state.mode == ALARM_TIME_SETTING)
		{
			if((get_key == UP_btn)||(BT_buffer[0]==BT_UP))
			{
				if((y== 0)||(y==1)) atime.hours +=12;
				if(y==3) atime.hours +=10;
				if(y==4) atime.hours +=1;
				if(y==6) atime.minutes +=10;
				if(y==7) atime.minutes +=1;
				if(y==9) atime.seconds +=10;
				if(y==10) atime.seconds +=1;
			}
			if((get_key == DOWN_btn)||(BT_buffer[0]==BT_DOWN))
			{
				if((y== 0)||(y==1)) atime.hours -=12;
				if(y==3) atime.hours -=10;
				if(y==4) atime.hours -=1;
				if(y==6) atime.minutes -=10;
				if(y==7) atime.minutes -=1;
				if(y==9) atime.seconds -=10;
				if(y==10) atime.seconds -=1;
			}
			if((get_key == LEFT_btn)||(BT_buffer[0]==BT_LEFT))
			{
				if((--y)<0) y = 15;
			}
			if((get_key == RIGHT_btn)||(BT_buffer[0]==BT_RIGHT))
			{
				if((++y)>15) y = 0;

			}
		}
		if(current_state.mode == MUSIC_SELECT)
		{
			if((get_key == UP_btn)||(BT_buffer[0]==BT_UP))
			{
				if(--x<0) x=0;
			}
			if((get_key == DOWN_btn)||(BT_buffer[0]==BT_DOWN))
			{
				if(++x>2) x=2;
			}
		}
	}
	BT_buffer[0] =0;
	HAL_ADC_Start(&hadc1);
}

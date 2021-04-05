/*
 * tim.c
 *
 *  Created on: Jan 19, 2021
 *      Author: s02
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include "tim.h"
#include "lcd.h"
volatile int timer_count,second,minute,hour;
char line[2][18], time_str[16];
struct clock_state current_state;
TimeTypeDef ctime;  // current time
TimeTypeDef stime; // setting time
TimeTypeDef atime;  // alarm time
TIM_HandleTypeDef htim3;
//extern
extern uint8_t y;
extern int8_t x;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM3)
  {
    if((timer_count%100)==0)
    {
      ctime.seconds++;

      if(ctime.seconds>=60)
      {
    	ctime.minutes++;
    	ctime.seconds = 0;
      }
      if(ctime.minutes>=60)
      {
    	ctime.hours++;
        ctime.minutes = 0;
      }
      if(ctime.hours>=24)
      {
    	ctime.hours = 0;
      }
#if 1
		  time_display();
#endif
    }
    Folling_ADC();
	  timer_count++;
  }
}

void time_display(void)
{
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;

  memset(line,0,sizeof(line));

  if(current_state.mode == NORMAL_STATE)
  {
	  sprintf(line[0],"Korea Polytech");
	  hours = ctime.hours;
	  minutes = ctime.minutes;
	  seconds = ctime.seconds;
  }
  else if(current_state.mode == TIME_SETTING)
  {
	  blink();
	  sprintf(line[0],"Time Setting");
	  hours = stime.hours;
	  minutes = stime.minutes;
	  seconds = stime.seconds;

  }
  else if(current_state.mode == ALARM_TIME_SETTING)
  {
	  blink();
	  sprintf(line[0],"Alarm Setting");
	  hours = atime.hours;
	  minutes = atime.minutes;
	  seconds = atime.seconds;
  }
  else if(current_state.mode == MUSIC_SELECT)
  {
	  blink();
	  Clear();
	  if(x==0)
	  {
	  sprintf(line[0], " 1. Three Bears");
	  sprintf(line[1], " 2. cycle");
	  }
	  if(x==1)
	  {
	  sprintf(line[0], " 2. cycle");
	  sprintf(line[1], " 3. Spring Water");
	  }
	  if(x==2)
	  {
	  sprintf(line[0], "3. Spring Water");
	  }
  }
  if(current_state.mode != MUSIC_SELECT)
  {
	  if(hours>=12)
	  {
		strncpy(line[1],"PM ",3);
		sprintf(time_str,"%02d:%02d:%02d",hours-12,minutes,seconds);
	  }
	  else
	  {
		strncpy(line[1],"AM ",3);
		sprintf(time_str,"%02d:%02d:%02d",hours,minutes,seconds);
	  }
	  strcat(line[1],time_str);

	  if(current_state.mode == ALARM_TIME_SETTING)
		  strcat(line[1]," AL");
  }
  setCursor(0,0);
  LCD_SendString(LCD_ADDR, line[0]);
  setCursor(1,0);
  LCD_SendString(LCD_ADDR, line[1]);
  setCursor(1,y);
  if(current_state.mode == MUSIC_SELECT) setCursor(0, 0);
}

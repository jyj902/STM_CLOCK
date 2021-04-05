/*
 * tim.h
 *
 *  Created on: Jan 19, 2021
 *      Author: s02
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

enum CLOCK_MODE{
	NORMAL_STATE,
	TIME_SETTING,
	ALARM_TIME_SETTING,
	MUSIC_SELECT
};

enum CLOCK_BUTTON{
	NO_KEY,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	SEL
};

struct clock_state{
	enum CLOCK_MODE mode;
	enum CLOCK_BUTTON button;
	int music_num;
};

typedef struct {
  int8_t hours;
  int8_t minutes;
  int8_t seconds;
}TimeTypeDef;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void time_display();

#endif /* INC_TIM_H_ */

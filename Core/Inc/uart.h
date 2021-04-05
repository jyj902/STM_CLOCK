/*
 * uart.c
 *
 *  Created on: Jan 19, 2021
 *      Author: s02
 */

#ifndef INC_UART_C_
#define INC_UART_C_
#include "main.h"
#include <stdio.h>
#include <string.h>

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC_UART_C_ */

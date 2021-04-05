/*
 * uart.c
 *
 *  Created on: Jan 5, 2021
 *      Author: user
 */
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "uart.h"

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

uint8_t rx_d=0;
uint8_t buffer[30];
uint8_t *ptr;
uint8_t BT_buffer[10];
uint8_t *BT_ptr;


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//HAL_UART_Receive(&huart2, BT_buffer, sizeof(BT_buffer),1000);
	//HAL_UART_Transmit(&huart3, BT_buffer, sizeof(BT_buffer), 1000);
	if(huart->Instance == USART3)
	{

	}
	if(huart->Instance == USART2)
	{

	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		HAL_UART_Receive_IT(&huart3, &rx_d, 1);
		HAL_UART_Transmit(&huart3, &rx_d, 1, 1000);
		*(ptr++) = rx_d;
		if((rx_d=='\r')||(rx_d=='\n'))
		{
			HAL_UART_Transmit(&huart2, buffer, ptr-buffer-1,1000);
			memset(buffer, 0, sizeof(buffer));
			ptr = buffer;

		}
	}
	if(huart->Instance == USART2)
	{
		HAL_UART_Transmit_IT(&huart3, BT_buffer, strlen(BT_buffer));
		HAL_UART_Receive_IT(&huart2, BT_buffer, strlen(BT_buffer));
	}
	/*
	HAL_UART_Receive_IT(&huart3, &rx_d, 1);
	if(rx_d == '1')
	{
		if(((GPIOB->IDR) & 0x1)==0x1)GPIOB->ODR &= ~(0x1);
		else GPIOB->ODR |= 0x1;
	}
	if(rx_d == '2')
	{
		if((GPIOB->IDR&0x80)==0x80)GPIOB->ODR &= ~(0x80);
		else GPIOB->ODR |= 0x80;
	}
	if(rx_d == '3')
	{
		if((GPIOB->IDR&0x4000)==0x4000)GPIOB->ODR &= ~(0x4000);
		else GPIOB->ODR |= 0x4000;
	}
*/
}

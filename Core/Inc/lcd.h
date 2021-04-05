/*
 * lcd.h
 *
 *  Created on: Jan 19, 2021
 *      Author: s02
 */
#ifndef INC_LCD_H_
#define INC_LCD_H_
#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>

#define LCD_ADDR (0x27 << 1)
#define LCD_SETDDRAMADDR 0x80
#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00
#define LCD_DISPLAYCONTROL 0x08
#define LCD_DELAY_MS 5

HAL_StatusTypeDef LCD_SendInternal(uint8_t lcd_addr, uint8_t data, uint8_t flags);
void LCD_SendCommand(uint8_t lcd_addr, uint8_t cmd);
void LCD_SendData(uint8_t lcd_addr, uint8_t data);
void LCD_Init(uint8_t lcd_addr);
void LCD_SendString(uint8_t lcd_addr, char *str);
void blink();
void loop();
void setCursor(uint8_t col, uint8_t row);
void Clear();
void noblink();
#endif /* INC_LCD_H_ */

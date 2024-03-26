/*
 * LCD.h
 *
 *  Created on: Sep 23, 2023
 *      Author: DELL
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_





#include "pico/stdlib.h"


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define E_ON   	gpio_put(11,1);
#define E_OFF  	gpio_put(11,0);

#define RS_ON 	gpio_put(12,1);
#define RS_OFF 	gpio_put(12,0);

#define D4_ON 	gpio_put(10,1);
#define D4_OFF 	gpio_put(10,0);

#define D5_ON 	gpio_put(9,1);
#define D5_OFF  gpio_put(9,0);

#define D6_ON 	gpio_put(8,1);
#define D6_OFF 	gpio_put(8,0);

#define D7_ON 	gpio_put(7,1);
#define D7_OFF 	gpio_put(7,0);

typedef enum{
	fila1=0,
	fila2,
	fila3,
	fila4
}Ubicacion;


void LCD_PICO_CMD(uint8_t a);
void LCD_PICO_BUS(uint8_t a);
void LCD_PICO_INIT(void);
void LCD_PICO_SET_CURSOR(uint8_t x,Ubicacion y);
void LCD_PICO_PRINT_CHAR(char a);
void LCD_PICO_PRINT_STRING(char *a);
void LCD_PICO_New_Char(uint8_t a,uint8_t b,uint8_t c,uint8_t d ,uint8_t e ,uint8_t f,uint8_t g,uint8_t h,uint8_t i);
void LCD_PICO_Print_New_Char(uint8_t a);
void LCD_PICO_Clear(void);
void LCD_PICO_Home(void);



#endif /* INC_LCD_H_ */

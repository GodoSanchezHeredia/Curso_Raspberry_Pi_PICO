/*
 * LCD.c
 *
 *  Created on: Sep 23, 2023
 *      Author: DELL
 */

#include "LCD.h"


void LCD_PICO_CMD(uint8_t a){
	E_OFF;
	E_ON;
	LCD_PICO_BUS(a);
	sleep_ms(2);
	E_OFF;
}
void LCD_PICO_BUS(uint8_t a){

	//0001
	if(a & 0x01){D4_ON;}
	else{D4_OFF};
	//0010
	if(a & 0x02){D5_ON;}
	else{D5_OFF};
	//0100
	if(a & 0x04){D6_ON;}
	else{D6_OFF};
	//1000
	if(a & 0x08){D7_ON;}
	else{D7_OFF};
}

void LCD_PICO_INIT(void){

gpio_init(7);//se habilita el clok del pin
gpio_set_dir(7,GPIO_OUT);//Le indicamos que sera salida digital
gpio_init(8);//se habilita el clok del pin
gpio_set_dir(8,GPIO_OUT);
gpio_init(9);//se habilita el clok del pin
gpio_set_dir(9,GPIO_OUT);
gpio_init(10);//se habilita el clok del pin
gpio_set_dir(10,GPIO_OUT);
gpio_init(11);//se habilita el clok del pin
gpio_set_dir(11,GPIO_OUT);
gpio_init(12);//se habilita el clok del pin
gpio_set_dir(12,GPIO_OUT);

	LCD_PICO_CMD(0x03);
	sleep_ms(3);
	LCD_PICO_CMD(0x03);
	LCD_PICO_CMD(0x03);
	LCD_PICO_CMD(0x02);
	LCD_PICO_CMD(0x02);
	LCD_PICO_CMD(0x08);
	LCD_PICO_CMD(0x00);
	LCD_PICO_CMD(0x08);
	LCD_PICO_CMD(0x00);
	LCD_PICO_CMD(0x01);
	LCD_PICO_CMD(0x00);
	//Con curso activado es 0XD,  sin cursor : 0xC
	LCD_PICO_CMD(0x0D);
}


void LCD_PICO_SET_CURSOR(uint8_t x,Ubicacion y){

	uint8_t m,n;

	RS_OFF;
	switch (y) {
		case fila1:
			m=0x80+x;
			n=(0x80+x)>>4;
			LCD_PICO_CMD(n);
			LCD_PICO_CMD(m);
			break;
		case fila2:
			m=0xC0+x;
			n=(0xC0+x)>>4;
			LCD_PICO_CMD(n);
			LCD_PICO_CMD(m);

		case fila3:

			break;
		case fila4:

			break;
	}


}
void LCD_PICO_PRINT_CHAR(char a){
	uint8_t m,n;
	m = a>>4;
    n = a;
	RS_ON;
	LCD_PICO_CMD(m);
	LCD_PICO_CMD(n);
  

}
void LCD_PICO_PRINT_STRING(char *a){


	while(*a){
			LCD_PICO_PRINT_CHAR(*a++);
	}
RS_OFF;
}

void LCD_PICO_New_Char(uint8_t a,uint8_t b,uint8_t c,uint8_t d ,uint8_t e ,uint8_t f,uint8_t g,uint8_t h,uint8_t i){

	  uint8_t m,n;
		  switch(a){
			  case 1:
			  LCD_PICO_CMD(0x04);
			  LCD_PICO_CMD(0x00);
			  RS_ON;
			  m=b>>4;
			  n=b;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=d>>4;
			  n=d;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=e>>4;
			  n=e;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=f>>4;
			  n=f;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=g>>4;
			  n=g;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=h>>4;
			  n=h;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=i>>4;
			  n=i;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  RS_OFF;
			  LCD_PICO_CMD(0x00);
			  LCD_PICO_CMD(0x01);
			  sleep_ms(100);
			  break;
			  case 2:
			  LCD_PICO_CMD(0x04);
			  LCD_PICO_CMD(0x08);
			  RS_ON;
			  m=b>>4;
			  n=b;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=d>>4;
			  n=d;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=e>>4;
			  n=e;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=f>>4;
			  n=f;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=g>>4;
			  n=g;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=h>>4;
			  n=h;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=i>>4;
			  n=i;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  RS_OFF;
			  LCD_PICO_CMD(0x00);
			  LCD_PICO_CMD(0x01);
			  sleep_ms(100);
			  break;
			  case 3:
			  LCD_PICO_CMD(0x04);
			  LCD_PICO_CMD(0xFF);
			  RS_ON;
			  m=b>>4;
			  n=b;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=d>>4;
			  n=d;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=e>>4;
			  n=e;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=f>>4;
			  n=f;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=g>>4;
			  n=g;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=h>>4;
			  n=h;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  m=i>>4;
			  n=i;
			  LCD_PICO_CMD(m);
			  LCD_PICO_CMD(n);
			  RS_OFF;
			  LCD_PICO_CMD(0x00);
			  LCD_PICO_CMD(0x01);
			  sleep_ms(100);
			  break;
		  }



}
void LCD_PICO_Print_New_Char(uint8_t a){
	RS_ON;
	LCD_PICO_CMD(0x00);
	LCD_PICO_CMD(a-1);
	RS_OFF;
}
void LCD_PICO_Clear(void){
	RS_OFF;
	LCD_PICO_CMD(0x00);
	LCD_PICO_CMD(0x01);
}
void LCD_PICO_Home(void){
	RS_OFF;
    LCD_PICO_CMD(0x00);
    LCD_PICO_CMD(0x02);
}

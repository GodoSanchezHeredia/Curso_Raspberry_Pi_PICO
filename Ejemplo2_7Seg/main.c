#include "pico/stdlib.h"
#include "Display7seg.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct{

    uint8_t a;//21
    uint8_t b;//6
    uint8_t c;//16
    uint8_t d;//17
    uint8_t e;//18
    uint8_t f;//20
    uint8_t g;//19

}Display7Seg;

void Write_Display7seg(Display7Seg *D7S,uint8_t val);
void Reset_Display7seg(void);

#define  LED1 16
#define  Boton 13

Display7Seg Display1 = {21,22,16,17,18,20,19};

void GpioInit(void){
gpio_init(21);//se habilita el clok del pin
gpio_set_dir(21,GPIO_OUT);
gpio_init(22);//se habilita el clok del pin
gpio_set_dir(22,GPIO_OUT);
gpio_init(16);//se habilita el clok del pin
gpio_set_dir(16,GPIO_OUT);
gpio_init(17);//se habilita el clok del pin
gpio_set_dir(17,GPIO_OUT);
gpio_init(18);//se habilita el clok del pin
gpio_set_dir(18,GPIO_OUT);
gpio_init(20);//se habilita el clok del pin
gpio_set_dir(20,GPIO_OUT);
gpio_init(19);//se habilita el clok del pin
gpio_set_dir(19,GPIO_OUT);
}
int i = 0;
int main(void) 
{
    
//definicion para Salida Digital

gpio_init(LED1);//se habilita el clok del pin
gpio_set_dir(LED1,GPIO_OUT);//Le indicamos que sera salida digital

//Definicion para entrada digital

gpio_init(Boton);//HABILITAMOS SU CLOCK
gpio_set_dir(Boton,GPIO_IN);
gpio_pull_down(Boton);


GpioInit();

for(;;){


  for(i = 0;i<10;i++){
        
            Write_Display7seg(&Display1,i);
            sleep_ms(1000);
        
        }
/*
gpio_put(LED1,1);
sleep_ms(500);
gpio_put(LED1,0);
sleep_ms(500);
*/

}


return 0;
	
}


void Write_Display7seg(Display7Seg *D7S,uint8_t val){

    const uint8_t Display_7Seg_C[] = {0x3F, 0X06 ,0X5B ,0x4f,0X66 ,0X6D, 0X7D, 0X07 ,0X7F, 0X67};
   // const uint8_t Display_7SegA[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};                        
    uint8_t data=Display_7Seg_C[val];
    Reset_Display7seg();
    
   

    if(data & 0x1)  gpio_put(D7S->a,1);
    if(data & 1<<1) gpio_put(D7S->b,1);
    if(data & 1<<2) gpio_put(D7S->c,1);
    if(data & 1<<3) gpio_put(D7S->d,1);
    if(data & 1<<4) gpio_put(D7S->e,1);
    if(data & 1<<5) gpio_put(D7S->f,1);
    if(data & 1<<6) gpio_put(D7S->g,1);
   
    return;
    
}

void Reset_Display7seg(void){

  gpio_put(21,0);
  gpio_put(22,0);
  gpio_put(16,0);
  gpio_put(17,0);
  gpio_put(18,0);
  gpio_put(20,0);
  gpio_put(19,0);
    
}

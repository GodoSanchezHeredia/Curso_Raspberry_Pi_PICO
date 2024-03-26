

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "stdint.h"
#include "stdbool.h"
#include "LCD.h"


volatile uint8_t count=0;
volatile bool flag = false;

char str_count[15];
void ISR_InterruptExtern(uint gpio);

int main() {


LCD_PICO_INIT();
LCD_PICO_SET_CURSOR(0,fila1);
LCD_PICO_PRINT_STRING("Clase Interrup");

gpio_init(16);
gpio_set_dir(16,GPIO_IN);
gpio_pull_up(16);
gpio_set_irq_enabled_with_callback(16,GPIO_IRQ_EDGE_FALL,true,&ISR_InterruptExtern);

gpio_init(17);
gpio_set_dir(17,GPIO_IN);
gpio_pull_down(17);
gpio_set_irq_enabled_with_callback(17,GPIO_IRQ_EDGE_RISE,true,&ISR_InterruptExtern);




for (;;)
{
    /* code */
    if(flag){

        LCD_PICO_SET_CURSOR(0,fila2);
        sprintf(str_count,"Count:%03u",count);
        LCD_PICO_PRINT_STRING(str_count);


        flag=false;
    }
}


}


void ISR_InterruptExtern(uint gpio){

    if (gpio==16)
    {
        count++;
    }
        if (gpio==17)
    {
        count--;
    }
    
    flag = true;
}


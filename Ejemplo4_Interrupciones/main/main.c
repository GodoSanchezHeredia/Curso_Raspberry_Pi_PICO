

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "stdint.h"
#include "stdbool.h"
#include "LCD.h"


volatile uint8_t count=0;
volatile bool flag = false;

char str_count[15];
void ISR_InterruptExtern(uint gpio,uint32_t event_mask);

int main() {

    hw_set_bits(&timer_hw->inte, 1u << 0);
LCD_PICO_INIT();
LCD_PICO_New_Char(1,0x0A,0x1F,0x1F,0x1F,0x0E,0x04,0x00,0x00);// corazon
LCD_PICO_New_Char(2,0x04,0x0E,0x0E,0x0E,0x0E,0x1F,0x00,0x00);//campana
LCD_PICO_New_Char(3,0x0E,0x1F,0x15,0x1F,0x1F,0x0E,0x0E,0x00);//calavera
LCD_PICO_SET_CURSOR(0,fila1);
LCD_PICO_PRINT_STRING("Clase Interrup");
LCD_PICO_Print_New_Char(1);
LCD_PICO_Print_New_Char(2);
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
        LCD_PICO_Print_New_Char(3);

        flag=false;
    }
}


}


void ISR_InterruptExtern(uint gpio,uint32_t event_mask){

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


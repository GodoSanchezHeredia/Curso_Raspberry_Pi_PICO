
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/multicore.h"
#include "stdlib.h"
#include "string.h"

#define Led1 17
#define Led2 16
#define Boton1 13
#define Boton2 15
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define PIN_PWM 2
 
char buffer_rx[100];
uint16_t i =0;
uint16_t ref;

void mainCore1(void);
void Uartinit(void);

void ISR_RX(void);


int main() {
stdio_init_all();
  gpio_init(PIN_PWM);
gpio_set_function(PIN_PWM, GPIO_FUNC_PWM);
    

    uint slice_num = pwm_gpio_to_slice_num(PIN_PWM);
     // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 1000);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
gpio_init(Boton1);//HABILITAMOS SU CLOCK
gpio_set_dir(Boton1,GPIO_IN);
gpio_pull_up(Boton1);
gpio_init(Boton2);//HABILITAMOS SU CLOCK
gpio_set_dir(Boton2,GPIO_IN);
gpio_pull_up(Boton2);

multicore_launch_core1(mainCore1);//Habilitamos el Core1


    while (1)
    {
        if (multicore_fifo_rvalid())
        {
            uint32_t msg_getcore0 = multicore_fifo_pop_blocking();
            pwm_set_chan_level(slice_num,PWM_CHAN_A,msg_getcore0);
        }
        

        
     if (gpio_get(Boton1))
     {
       
     multicore_fifo_push_blocking(1);
     }else{
        multicore_fifo_push_blocking(0);
     }
        if (gpio_get(Boton2))
     {
        /* code */
     multicore_fifo_push_blocking(3);
     }else{
        multicore_fifo_push_blocking(2);
     }
    sleep_ms(100);
    }
    
    
    return 0;
}


void mainCore1(void){
    
    gpio_init(Led1);//se habilita el clok del pin
    gpio_set_dir(Led1,GPIO_OUT);//Le indicamos que sera salida digital
    gpio_init(Led2);//se habilita el clok del pin
    gpio_set_dir(Led2,GPIO_OUT);//Le indicamos que sera salida digital   
    Uartinit();
    for(;;){
        if(multicore_fifo_rvalid()){
            uint32_t msg_getcore1 = multicore_fifo_pop_blocking();
            switch (msg_getcore1)
            {
            case 0:
                gpio_put(Led1,1);
                break;
            case 1:
                /* code */
                gpio_put(Led1,0);
                break;
            case 2:
                /* code */
                gpio_put(Led2,1);
                break;
            case 3:
                /* code */
                gpio_put(Led2,0);
                break;


            }

        }

    }
}

void Uartinit(void){
uart_init(UART_ID, 2400);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, ISR_RX);
    irq_set_enabled(UART_IRQ, true);

   
    uart_set_irq_enables(UART_ID, true, false);
}


void ISR_RX(void){

while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
         switch (ch)
        {
        
            case '*':
            ref = atoi(buffer_rx);
            memset(buffer_rx,0,i);
            i=0;
            multicore_fifo_push_blocking(ref);
           // uint slice_num = pwm_gpio_to_slice_num(PIN_PWM);
            //pwm_set_enabled(slice_num, false);
            //pwm_set_chan_level(slice_num, PWM_CHAN_A, ref);
            //pwm_set_enabled(slice_num, true);
            break;

        default:
        buffer_rx[i] =ch;
        i++;

            break;
        }
    }
}
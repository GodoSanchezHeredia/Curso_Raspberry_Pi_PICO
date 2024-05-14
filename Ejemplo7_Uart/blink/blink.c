/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

/// \tag::uart_advanced[]

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

 
char buffer_rx[100];

uint16_t i =0;

uint16_t ref;
// RX interrupt handler
void on_uart_rx();
int main() {
    
    uart_init(UART_ID, 2400);

       const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

     gpio_set_function(16, GPIO_FUNC_PWM);
    gpio_set_function(17, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(0);
     // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 1000);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
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
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

   
    uart_set_irq_enables(UART_ID, true, false);

    uart_puts(UART_ID, "\nINICIAMOS COMUNICACION\n");

    while (1){

            tight_loop_contents();
    }
        
}
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
         switch (ch)
        {
        case 'A':
            /* code */
            gpio_put(PICO_DEFAULT_LED_PIN,true);
           // uart_puts(uart0,"RELE ENCENDIDO\n\r");
            break;
        case 'B':
            gpio_put(PICO_DEFAULT_LED_PIN,false);
            //uart_puts(uart0,"RELE APAGADO\n\r");
            break;
        case 'C':
            /* code */
            gpio_put(16,true);
           // uart_puts(uart0,"RELE ENCENDIDO\n\r");
            break;
        case 'D':
            gpio_put(16,false);
            //uart_puts(uart0,"RELE APAGADO\n\r");
            break;
            case '*':
            ref = atoi(buffer_rx);
            memset(buffer_rx,0,i);
            i=0;
            uint slice_num = pwm_gpio_to_slice_num(0);
            pwm_set_enabled(slice_num, false);
            pwm_set_chan_level(slice_num, PWM_CHAN_A, ref);

    pwm_set_enabled(slice_num, true);
            break;

        default:
        buffer_rx[i] =ch;
        i++;

            break;
        }
    }
}

/// \end:uart_advanced[]

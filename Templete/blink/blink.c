/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
//#include "LCD.h

void ISR_RX(void);
volatile char rx_data='\0';
int main() {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
 uart_init(uart0, 2400);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Actually, we want a different speed
    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    int __unused actual = uart_set_baudrate(uart0, 115200);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(uart0, false, false);

    // Set our data format
    uart_set_format(uart0, 8, 1, UART_PARITY_NONE);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(uart0, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
  

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(uart0, ISR_RX);
    irq_set_enabled(uart0, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(uart0, true, false);
    while (true) {
        
        //tight_loop_contents();

        uart_puts(uart0,"Curso Pi Pico\n\r");
        sleep_ms(500);
        uart_putc(uart0,'G');        
        sleep_ms(500);
        uart_putc_raw(uart0,0x64);
        sleep_ms(500);
            }

}


void ISR_RX(void){
    
        rx_data = uart_getc(uart0);

       

        /* code */
    }
    






#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "PID.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define d1 14
#define d2 15

char buffer_rx[100];
 char data_TX[50];

uint16_t i = 0;
uint16_t ref;

volatile uint16_t Pulsos;
volatile float  rpm,FrecAngular;

volatile float U ;

void on_uart_rx();
void Gpio_init();
void timer_init();
void ts(uint alarm_num);
void ISR_InterruptExtern(uint gpio,uint32_t event_mask);

#define PID_KP 0.019664
#define PID_KI 0.46923
#define PID_KD 0.00020602
#define PID_TAU 0
#define PID_LMAX 12.0
#define PID_LMIN 0
#define PID_TS 10E-3

ControladorPID MotorDC = {PID_KP,PID_KI,PID_KD,PID_TAU,PID_LMAX,PID_LMIN,PID_TS};

int main() {
    stdio_init_all();
    sleep_ms(3000);
    Gpio_init();
    timer_init();
    Controlador_PID(&MotorDC);
    while (1)
    {
    
      



    }
    
    
    return 0;
}

void Gpio_init(){

    //pines del motor
    gpio_init(14);//se habilita el clok del pin
    gpio_set_dir(14,GPIO_OUT);
    gpio_init(15);//se habilita el clok del pin
    gpio_set_dir(15,GPIO_OUT);
    
   //PWM
    gpio_set_function(16, GPIO_FUNC_PWM);
    uint16_t slice_num = pwm_gpio_to_slice_num(16);
    pwm_set_wrap(slice_num, 1000);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    pwm_set_enabled(slice_num, true);



//Interrupcion externa
gpio_init(17);
gpio_set_dir(17,GPIO_IN);
//gpio_pull_down(17);
gpio_set_irq_enabled_with_callback(17,GPIO_IRQ_EDGE_RISE,true,&ISR_InterruptExtern);



//UART
  uart_init(UART_ID, BAUD_RATE);
   gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ID, false);
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    uart_set_irq_enables(UART_ID, true, false);

    gpio_put(d1, 0);
    gpio_put(d2, 0);
}
void timer_init(){

    if (!hardware_alarm_is_claimed(0)) {
        hardware_alarm_claim(0);
    }

    // Register the callback function
    hardware_alarm_set_callback(0, ts);

    // Set the initial target time to 20 ms from now
    absolute_time_t target_time = make_timeout_time_ms(10);
    hardware_alarm_set_target(0, target_time);

    
}
void ts(uint alarm_num) {
    // Recalculate the target time for the next 20 ms interval
    absolute_time_t target_time = make_timeout_time_ms(10);

    // Set the hardware alarm to trigger at the new target time
    hardware_alarm_set_target(alarm_num, target_time);

    // Callback action
    rpm = Pulsos*60.0/(0.01*120);
    Pulsos = 0;
    FrecAngular = rpm*(2*3.14159265359)/60;//W
    
    /*calculo del pid*/
    U = ControladorPID_Calculo(&MotorDC,ref,FrecAngular)*1000/12.0;
      uint16_t slice_num = pwm_gpio_to_slice_num(16);
                pwm_set_enabled(slice_num, false);
                pwm_set_chan_level(slice_num, PWM_CHAN_A, U);
                pwm_set_enabled(slice_num, true);
     sprintf(data_TX,"%.2f\n\r",FrecAngular);
    uart_puts(UART_ID,data_TX);
      memset(data_TX,0,49);           
}
void ISR_InterruptExtern(uint gpio,uint32_t event_mask){
 
 Pulsos++;

}
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        switch (ch) {

            case 'D':
                gpio_put(d1, 0);
                gpio_put(d2, 1);
                break;
            case 'I':
                gpio_put(d1, 1);
                gpio_put(d2, 0);
                break;
            case '*':
                ref = atof(buffer_rx);
                memset(buffer_rx, 0, i);
                i = 0;
                break;
            default:
                buffer_rx[i] = ch;
                i++;
                break;
        }
    }
}


#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const uint LED1_PIN = 1;
volatile bool timer_fired = false;
volatile uint8_t i = 0;
//
struct repeating_timer timer;

//Definicion de Funciones
void Timer_ISR(alarm_id_t id, void *user_data);
void Timer_Rep_ISR(alarm_id_t id, void *user_data);


int main() {
    stdio_init_all();
    uint16_t slice_num = pwm_gpio_to_slice_num(0);

      //Configuracion del PIN
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);
    sleep_ms(3000);
//Configuracion del Timer
add_alarm_in_ms(200,Timer_ISR,NULL,false);
while (!timer_fired)
{
  tight_loop_contents();
}

    while (1)
    {
      /* code */
    }
    
    
    return 0;
}

void Timer_ISR(alarm_id_t id, void *user_data){

timer_fired = true;
add_repeating_timer_ms(1,Timer_Rep_ISR,NULL,&timer);
return 1;

}

void Timer_Rep_ISR(alarm_id_t id, void *user_data){
i ^= (1<<0);
gpio_put(LED_PIN,i);
gpio_put(LED1_PIN,i);
return 1;
}
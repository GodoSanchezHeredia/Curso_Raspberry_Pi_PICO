
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
volatile bool timer_fired = false;
 const uint LED_PIN = PICO_DEFAULT_LED_PIN;
volatile uint8_t i = false;
int64_t ISR_TIMER(alarm_id_t id, void *user_data) {
    printf("Timer %d fired!\n", (int) id);
    timer_fired = true;
    
    return 0;
}
 

bool ISR_TIMER_REP(struct repeating_timer *t) {
    printf("Repeat at %lld\n", time_us_64());
    i ^= (1<<0) ;
    gpio_put(LED_PIN,i);
    return true;
}
 
int main() {
    stdio_init_all();
      
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    sleep_ms(3000);
    printf("Hello Timer!\n");
 
    //hacer la temporizacion en 2 Segundos a una ISR
    add_alarm_in_ms(2000, ISR_TIMER, NULL, false);
 
    //  esperamos que se setee la alarma
    while (!timer_fired) {
        tight_loop_contents();
    }
 
    for(;;){
          struct repeating_timer timer;
    add_repeating_timer_ms(1000, ISR_TIMER_REP, NULL, &timer);
    sleep_ms(3000);
    bool cancelled = cancel_repeating_timer(&timer);
    printf("cancelled... %d\n", cancelled);
    sleep_ms(2000);
 
    
    add_repeating_timer_ms(-1000, ISR_TIMER_REP, NULL, &timer);
    sleep_ms(3000);
    cancelled = cancel_repeating_timer(&timer);
    printf("cancelled... %d\n", cancelled);
    sleep_ms(2000);
    printf("Done\n");
    }
  
    return 0;
}
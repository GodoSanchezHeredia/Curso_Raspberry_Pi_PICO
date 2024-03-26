/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "LCD.h"
int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

 LCD_PICO_INIT();
 LCD_PICO_SET_CURSOR(0,fila1);
 LCD_PICO_PRINT_STRING("Curso Pi Pico");
 sleep_ms(200);
 LCD_PICO_SET_CURSOR(0,fila2);
 LCD_PICO_PRINT_STRING("Godo Sanchez");
 sleep_ms(500);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    }
#endif
}

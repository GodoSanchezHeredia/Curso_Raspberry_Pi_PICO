
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "LCD.h"


int main() {
    stdio_init_all();
    sleep_ms(3000);
    printf("LCD I2C INIT\r\n");
    i2c_init(&i2c1_inst, 100 * 1000); //100KHz
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

   // bi_decl(bi_2pins_with_func(15, 14, GPIO_FUNC_I2C));

    printf("configuracion hecha\n\r");
    
    LCD_PICO_INIT();
    LCD_PICO_SET_CURSOR(0,fila1);
    LCD_PICO_PRINT_STRING("I2C PI PICO");
    LCD_PICO_SET_CURSOR(0,fila2);
    LCD_PICO_PRINT_STRING("CURSO GSSH");
    
    while (1)
    {
    
      



    }
    
    
    return 0;
}
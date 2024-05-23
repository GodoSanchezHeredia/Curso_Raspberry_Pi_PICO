
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint8_t dato[2];
uint16_t dato_c;
float temperatura;

int main() {
    stdio_init_all();
    printf("CURSO PI PICO : TERMOCUPLA\r\n");
    spi_init(spi_default, 4000 * 1000); //4MHZ
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI); //MISO
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);//SCK
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);//MOSI
    gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);//CS

    bi_decl(bi_4pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI));

    while (1)
    {
      spi_read_blocking(spi0,0,dato,2);
      dato_c = (dato[0]<<8) +dato[1];
      temperatura = dato_c*0.250;// pasamos a temperatura
      printf("Valor Dato: %u\n\r",dato_c);
      printf("Temperatura termocupla:%0.2f\n\r",temperatura/10);
      sleep_ms(500);
    }
    
    
    return 0;
}
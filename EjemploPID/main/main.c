
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "PID.h"


ControladorPID Motor1;
ControladorPID ServoMotor1;
ControladorPID PlantaTemp;

int main() {
    stdio_init_all();
    sleep_ms(3000);

    
    
    while (1)
    {
    
      



    }
    
    
    return 0;
}
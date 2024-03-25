
#include "pico/stdlib.h"
#include "perf_counter.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define  LED1 16
#define  Boton 13



int main(void) 
{
    
//definicion para Salida Digital

gpio_init(LED1);//se habilita el clok del pin
gpio_set_dir(LED1,GPIO_OUT);//Le indicamos que sera salida digital

//Definicion para entrada digital


gpio_init(Boton);//HABILITAMOS SU CLOCK
gpio_set_dir(Boton,GPIO_IN);
gpio_pull_down(Boton);

for(;;){


if(gpio_get(Boton)){
gpio_put(LED1,1);
}else{
gpio_put(LED1,0);

}
}
return 0;
	
}

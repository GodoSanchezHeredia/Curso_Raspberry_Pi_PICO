/* 
 * File:   Configuracion.h
 * Author: DELL
 *
 * Created on 18 de marzo de 2024, 07:33 PM
 */

#ifndef CONFIGURACION_H
#define	CONFIGURACION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // trabajar con uint y int 
#include <stdbool.h> // boolenos
#include <string.h> // cadenas

    
    void HAL_PI_PICO_Clock_Init(void); // Vacia Sin Entradas de Argumento
    void HAL_PI_PICO_GPIO_Output(int PIN);//Vacia con entradas de parametros
    bool HAL_PI_PICO_GET_INPUT(void);//con retorno , pero sin entradas de argumento
    uint16_t HAL_PI_PICO_ADC_READ(int chanell);//con retorno , pero con entradas de argumento
    

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIGURACION_H */


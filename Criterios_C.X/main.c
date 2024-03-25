/* 
 * File:   main.c
 * Author: DELL
 *
 * Created on 18 de marzo de 2024, 07:32 PM
 */

#include "Configuracion.h"

/*Operadores a BIT

 | -> OR
 & -> AND      
 ^ -> XOR 
 ~ -> NOT
 
 Direccion de Memoria :W = 0b10101110
 - Ponga a 1 el bit numero 4 sin afectar al resto
 (1<<4) = 0b00010000
 OR = 0b10101110 |
      0b00010000
 -----------------
      0B10111110
 
 W |= (1<<4);
 * 
 * 
Direccion de Memoria :W = 0b10101110
 - Ponga a 0 el bit numero 5 sin afectar al resto
 (1<<5) =  0b00100000
 ~(1<<5) = 0b11011111
 AND =  0b10101110  &
        0b11011111
  -----------------
        0b10001110
 W &= ~(1<<5);
 * 
 LATB 1 ,el bit 4 y quiero a 0 el bit 3
 LATB |= (1<<4);
 LATB &= ~(1<<3);
 
 Leea el estado del bit 4 del registro PORTC
 
 if((1<<4) & PORTC){
 
 * }
 
 */


//Standar ANSI C

uint8_t valor1;
uint16_t valor2;

float temperatura;

uint8_t datosinit[5] = {1,2,3,4,5};
char palabra[4] = {'h','o','l','a',};
uint8_t dato[15] = "Hola mundo\n\r";
char msg2[15]  = "Hola mundo2\n\r";
/*
 uin8_t 0 255
 int8_t -127 128
 */


struct{

    float temperatura;
    float Humedad;
    uint8_t *Msg;
    bool Alarma;

}Planta1;

struct{

    float PosicionServo;
    float Angulo;
    uint8_t *Msgtx_Lora;
    uint8_t *MsgRx_Lora;
    bool Alarma;
    uint16_t TokenSesion;

}Planta2;


typedef struct{

    float Kp;
    float Ki;
    float Kd;
    float error;
    float error_anterior;
    float Medicion;
    float Medicion_anterior;
    float Ts;
    float Proporcioal;
    float Integral;
    float Derivativo;
    float UK;
}ControladorPID;


ControladorPID MotorDC;
ControladorPID Oven;
ControladorPID Servo;
ControladorPID PenduloInvertido;

int i , j;

int suma(int a , int b)
{
    return a +b;
}

float controlador(ControladorPID *pid){

    pid->Derivativo = 0;
    pid->Kd = 0.255;
    
    return;
}



int main(int argc, char** argv) {

    Planta1.Humedad = 23;
    Planta1.Msg = "hola planta1";
    Planta1.Alarma = true;
    
    
    Planta2.PosicionServo = 36.35;
    Planta2.TokenSesion = 24554;
            
    suma(i,j);
    controlador(&MotorDC);//vamor a pasar referenciar
    controlador(&Oven);
    for(;;){
    
    
    
    }
    
    return (EXIT_SUCCESS);
}


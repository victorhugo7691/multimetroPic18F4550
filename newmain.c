/*
 * File:   newmain.c
 * Author: Victor Hugo
 *
 * Created on 26 de Setembro de 2021, 16:01
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))

#pragma config WDT = OFF        // Watchdog Timer Enable bit 

#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

#define _XTAL_FREQ 4000000
#include <xc.h>

void verificaTensao(float tensao){
    if(tensao >=0 && tensao <1){
        PORTDbits.RD0 = 0xFF;
        __delay_ms(100);
    }
    if(tensao >= 1 && tensao < 2){
        PORTDbits.RD1 = 0xFF;
        __delay_ms(100);
    }
    if(tensao >= 2 && tensao < 3){
        PORTDbits.RD2 = 0xFF; 
        __delay_ms(100);
    }
    if(tensao >= 3 && tensao < 4){
        PORTDbits.RD3 = 0xFF; 
        __delay_ms(100);
    }
    if(tensao >= 4 && tensao <= 5){
        PORTDbits.RD4 = 0xFF; 
        __delay_ms(100);
    }
    
}

void main(void) {
    TRISD = 0x0; //configura portd como saida
    PORTD = 0; // 'zera portd
    PORTD = 0;    //LEDs  iniciam desligados
    float tensao = 0;
    float vetorDeTensao [] = {0, 1, 2, 3, 4};
    while(1){
        int i=0;
        tensao = vetorDeTensao[i];
        i++;
        verificaTensao(tensao);
    }
    return;
}

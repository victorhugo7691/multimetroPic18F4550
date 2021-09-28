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
#include <stdio.h>
#include <stdlib.h>
#include "lcd.intermed.h"

void verificaTensao(float tensao, char V[]){
    if(tensao >=0 && tensao <1){
        PORTDbits.RD0 = 0xFF;
        imprime_lcd(V);  
        __delay_ms(10);
    }
    if(tensao >= 1 && tensao < 2){
        PORTDbits.RD1 = 0xFF;
        imprime_lcd(V);  
        __delay_ms(10);
    }
    if(tensao >= 2 && tensao < 3){
        PORTDbits.RD2 = 0xFF; 
        imprime_lcd(V);  
        __delay_ms(10);
    }
    if(tensao >= 3 && tensao < 4){
        PORTDbits.RD3 = 0xFF; 
        imprime_lcd(V);  
        __delay_ms(10);
    }
    if(tensao >= 4 && tensao <= 5){
        PORTDbits.RD4 = 0xFF; 
        imprime_lcd(V);  
        __delay_ms(10);
    }
    limpa_lcd( );
}

void main(void) {
    char V[8];
    INTCONbits.GIE =1;
    INTCONbits.TMR0IE = 1;
    
    T0CON = 0B11000111;
    TMR0L = 5;
    
    TRISD = 0x0; //configura portd como saida
    TRISE = 0;
    ADCON1 = 15;
    PORTD = 0;    //LEDs  iniciam desligados
    
    INTCON3bits.INT1IE = 1;
   
    INTCON3bits.INT1IF = 0;
  
    INTCON2bits.INTEDG1 = 1;
      
    comando_lcd(0b00111100);
    comando_lcd(0b00001100);
    
    float tensao = 0;
    float vetorDeTensao [] = {0, 1, 2, 3, 4};
    while(1){
        int i=0;
        tensao = vetorDeTensao[i];
        i++;
        comando_lcd(128);
        imprime_lcd("Voltagem");
        comando_lcd(192);
        sprintf(V, "%3.2f", tensao);
        verificaTensao(tensao, V);
        if(tensao>=5){
            i=0;
        }
    }
    return;
}

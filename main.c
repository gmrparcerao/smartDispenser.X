// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <htc.h>
#define _XTAL_FREQ 500000
/*
 * File:   servopwm.c
 * Author: 2570901812011
 *
 * Created on 5 de Novembro de 2019, 16:38
 */
void configura(){
    OSCCON = 0b00110000;
    T2CON = 0b00000011; // prescaler + turn on TMR2;
    PR2 = 0b10011011;
    CCP1CON = 0b00111100; // duty lowest bits + PWM mode
    TRISB = 0b00000001;
    TRISC = 0;
    RB2 = 0;
    GIE = 1;
    PEIE = 1;
    INTE = 1;
    ANSEL = 0;
    ANSELH = 0;
}
void interrupt qqcoisa()
{
        RB1 = 1;
        INTF = 0;
        CCPR1L = 0b00001111;
        TMR2ON = 1;
        __delay_ms(1000);
        TMR2ON = 0;
        __delay_ms(5000);
}
void main() {
    configura();
    while(1){
        RB1 = 0;
        CCPR1L = 0b00000111;
        TMR2ON = 1;
        __delay_ms(1000);
        TMR2ON = 0;
        __delay_ms(5000);
    }
}

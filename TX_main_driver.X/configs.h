/* 
 * File:   configs.h
 * Author: Cody Howard
 * Comments: Configurations for PIC16F18344 1MHz internal oscillator
 * Revision history: 10/1/20
 * Final design 11/13/20
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f18344.h>
#define _XTAL_FREQ  1000000       // 1 MHz program frequency
#pragma config FEXTOSC = OFF      // Internal Oscillator mode S
#pragma config RSTOSC = HFINT1    // 1 MHz interrnal clock
#pragma config CLKOUTEN = OFF     // Clock Out Enable bit->CLKOUT function is disabled; I/O or oscillator function on OSC2
#pragma config CSWEN = ON         // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = OFF        // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is disabled
#pragma config WDTE = OFF
#pragma config LVP = OFF
//LED pins
#define sample_LED RB4
#define TX_LED RB5
#define WIND RA2
#define Wind_LED RA5

/* 
 * File:   ADC.h
 * Author: Sean
 *
 * Created on November 2, 2020, 10:12 PM
 */

#include "configs.h"


void ADC_Init();
int ADC_Read(int);
int Temp_Conv();
int Pres_Conv();

void ADC_Init(){
    ADCON1 = 0b11110000;    //Right Justified, Use ADCRC, Vdd is Vref
    ADCON0 = 0b00000001;    //Turn on ADC.
    ADRESH = 0;             //Clear Registers
    ADRESL = 0;
}

int ADC_Read(int channel){
    int val = 0;
    ADCON0 &= 0b00000001;   //Clear Channel Selection Bits
    ADCON0 |= channel<<2;   //Select Input Channel         
    ADCON0bits.GO_nDONE = 1; //Initialize Conversion
    while (ADCON0bits.GO_nDONE); //Wait for conversion
    val = (ADRESH<<8)+ADRESL; //Digital conversion is 10 bits
    return val;  //Return Conversion Value
}

int Temp_Conv(int V2T){
    int temp = 0.28*V2T-62;
    return temp;
}

int Pres_Conv(int V2P){
    int pres = 0.15*V2P+96;
    return pres;
}


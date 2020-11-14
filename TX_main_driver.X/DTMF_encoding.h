/* 
 * File:   
 * Author: C Howard
 * Comments: creates DTMF tones and sends packet of DTMF tones
 * Revision history: 
 */
#include "configs.h"

//PIC connections to NTE 1690
#define COL1 RC2 
#define COL2 RC1 
#define COL3 RC0
#define COL4 RC5 
#define ROW1 RC7 
#define ROW2 RC6  
#define ROW3 RC3 
#define ROW4 RC4 


void nib_to_DTMF(int);
void Send_DTMF_pack(int,int,int);

//function takes a nibble of an integer and
//converts it into a DTMF tone according to a DTMF table
void nib_to_DTMF(int nib){
    PORTC=0xFF;                                 //clear port and reset NTE 1690
    switch (nib){                               //test 4-bit number
        case 0:                  //hex 0
            ROW4 = 0;                           //set appropriate pins on NTE 1690 
            COL4 = 0;           //DTMF D
        break;
        case 1:                 //hex 1
            ROW1 = 0;
            COL1 = 0;           //DTMF 1
        break;
        case 2:                 //hex 2
            ROW1 = 0;
            COL2 = 0;           //DTMF 2
        break;
        case 3:                 //hex 3
            ROW1 = 0;
            COL3 = 0;           //DTMF 3
        break;
        case 4:                 //hex 4
            ROW2 = 0;
            COL1 = 0;           //DTMF 4
        break;
        case 5:                 //hex 5
            ROW2 = 0;
            COL2 = 0;           //DTMF 5
        break;
        case 6:                 //hex 6
            ROW2 = 0;
            COL3 = 0;           //DTMF 6
        break;
        case 7:                 //hex 7
            ROW3 = 0;
            COL1 = 0;           //DTMF 7
        break;
        case 8:                 //hex 8
            ROW3 = 0;
            COL2 = 0;           //DTMF 9
        break;
        case 9:                 //hex 9
            ROW3 = 0;
            COL3 = 0;           //DTMF 9
        break;
        case 10:                 //hex A
            ROW4 = 0;
            COL2 = 0;           //DTMF 0
        break;
        case 11:                 //hex B
            ROW4 = 0;
            COL1 = 0;           //DTMF *
        break;
        case 12:                 //hex C
            ROW4 = 0;
            COL3 = 0;           //DTMF #
        break;
        case 13:                 //hex D
            ROW1 = 0;
            COL4 = 0;           //DTMF A
        break;
        case 14:                 //hex E
            ROW2 = 0;
            COL4 = 0;           //DTMF B
        break;
        case 15:                 //hex F
            ROW3 = 0;
            COL4 = 0;           //DTMF C
        break;
}

}

//function to transmit 3 bytes of data as DTMF tones
void Send_DTMF_pack(int wind,int temperature,int press){
    int high, low = 0;
     nib_to_DTMF(0x01);                 //start tone
     __delay_ms(500);
     PORTC=0xFF; 
     __delay_ms(500);                   //half second on half second off
     
    high = temperature>>4 & 0x0F;      // start of temperature data
    nib_to_DTMF(high);                 //upper nib tone
    __delay_ms(500);
    PORTC=0xFF; 
    __delay_ms(500);                   //half second on; half second off
    low = temperature & 0x0F;
    nib_to_DTMF(low);                 //lower nib tone
    __delay_ms(500);
    PORTC=0xFF; 
    __delay_ms(500);                   //half second on; half second off
     
    high = wind>>4 & 0x0F;              // start of wind data
    nib_to_DTMF(high);                 //upper nib tone
    __delay_ms(500);
    PORTC=0xFF; 
    __delay_ms(500);                   //half second on; half second off
    low = wind & 0x0F;
    nib_to_DTMF(low);                 //lower nib tone
    __delay_ms(500);
    PORTC=0xFF; 
    __delay_ms(500);                   //half second on; half second off
    
    high = press >>4 & 0x0F;              // start of pressure data
    nib_to_DTMF(high);                 //upper nib tone
    __delay_ms(500);
    PORTC=0xFF; 
    __delay_ms(500);                   //half second on; half second off
    low = press & 0x0F;
    nib_to_DTMF(low);                 //lower nib tone
    __delay_ms(500);
    PORTC=0xFF; 
    __delay_ms(500);                   //half second on; half second off
    
    nib_to_DTMF(0x00);                 //end tone
     __delay_ms(5);
     PORTC=0xFF; 
}
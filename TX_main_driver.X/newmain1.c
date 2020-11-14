/* 
 * File:   Main.c
 * Main TX Driver (This gets the Wind and displays over the LCD ) 
 * Author: Skyler
 *
 * Created on September 30, 2020, 7:43 PM
 */
//#include "LCD_Drivers.h"
//#include "DTMF_Drivers.h"
#include "DTMF_encoding.h"
int wind_set = 0;
int wind_time_low = 0;
int wind_time_high = 0;
#define LED RB4


void main(void) 
{
    LATC = 0;
    TRISC = 0;                  //portC = output
    ANSELC = 0;                 //digital
    
    TRISB = 0b00000000;         //portB = input
    ANSELB = 0;                 //digital
    
    TRISA = 0b00100100;         //RA2 AND RA5 = input
    ANSELA = 0;                 //digital
    
    
   
    
    void ConfigInterrupts(void);
    void ConfigTimers(void);
   // LCD_init();
    //Lcd_Print_String("LCD status:");
    //__delay_ms(2000);
    //LCD_row_set(2);
    //Lcd_Print_String("WORKING");
    //LCD_row_set(1);
    //__delay_ms(2000);
    //LDC_clear();
      ConfigInterrupts();
      ConfigTimers();
      int wind_mph;
  while(1){
      int temperature; 
      int pressure ;
      
      int wind_sample[9] = {0};
      
      for(int x=0; x<=9; x++){
          if(wind_time_high == 0 ){
          
          wind_sample[x] = 1789 / ( wind_time_low * 4 ) ;}
      
      else
      { wind_sample[x] = 0;}
          __delay_ms(1000);
          wind_mph = wind_sample[x] + wind_mph;
      }
      
      wind_mph = wind_mph / 10;
      
      
    
      //__delay_ms(1000);
      //LCD_row_set(1);
      
      
      //if(WIND == 0) LED = 1 ;
      //__delay_ms(500); 
      
     // LDC_clear();
      //Lcd_Print_String("ih");
      //LED = 0;
     // __delay_ms(1000); 
      
     
    
    temperature = 15;
    pressure = 95;
    Send_DTMF_pack(wind_mph, temperature, pressure);
      
   /* if(wind_time_high == 0 ){
      LCD_Print_num(wind_time_low);
      LCD_row_set(2);
      wind_mph = 1789 / ( wind_time_low * 4 ) ; // wind in mph
      LCD_Print_num(wind_mph);
      Lcd_Print_String(" MPH");
      }
      else { 
          Lcd_Print_String("Wind too slow :( ");
      }*/
      
    
   // __delay_ms(2000);
    //LDC_clear();
    //LCD_row_set(1);
    //LCD_Print_num(temperature);
    //__delay_ms(2000);
    //LDC_clear();
    //LCD_Print_num(pressure);
    //__delay_ms(2000);
    //LDC_clear();
    //LCD_Print_num(wind_mph);
    
      
    }

}

void ConfigInterrupts(void) {
  //Configure your interrupts here
    
    INTCONbits.PEIE = 1; // Enables Peripheral Interrupts.
    INTCONbits.INTEDG = 0; // Interrupt occurs on a falling edge.
    
    
    PIE0bits.INTE = 1 ; // Enables the INT external interrupt
 
    INTPPSbits.INTPPS = 0b00000010; // Pin 17 as the input, RA2.
    
    PIR0bits.INTF = 0 ; // Clear the flag before enabling interrupts. 
    
    INTCONbits.GIE = 1; // Turn on interrupts.
    
   
}

void ConfigTimers(void) {
    T0CON0bits.T0EN = 1; // Enable Timer 0
    T0CON0bits.T016BIT = 1; // Enable 16 bit mode
    T0CON1bits.T0CS = 0b010; // Internal source Fosc / 4
    T0CON1bits.T0ASYNC = 0 ; // Syncronised to Fosc / 4
    T0CON1bits.T0CKPS = 0b1010; // divide the timer 
    
    TMR0Lbits.TMR0L = 0b00000000; // Set the timer to zero
    TMR0Hbits.TMR0H = 0b00000000; // set the timer to zero 
}

void __interrupt(high_priority) HighIsr(void) {

    if ( PIR0bits.INTF == 1) {
        if(wind_set == 0) {
            LED = 1;          // immediately turn on the LED

            wind_set = 1;
            TMR0L = 0;
            TMR0H = 0;
        }
        else{
            LED = 0;
            wind_set = 0;
            wind_time_low = TMR0L;
            wind_time_high = TMR0H;
        }
        
       
       PIR0bits.INTF = 0; //clear the flag
    }

       
    }

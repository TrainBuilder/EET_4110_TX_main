/* 
 * File:   TX_main.c
 * Author: Cody Howard, Skyler Fennel,, Sean Simons
 *
 * Created on October 22, 2020, 4:22 PM
 * Final revision 11/13/20
 * total TX_main_driver SLOC = 334
 */

#include "DTMF_encoding.h"
#include "ADC.h"
int wind_set = 0;
int wind_time_low = 0;
int wind_time_high = 0;
double Dig_val = 0;                //Digital output value

void ConfigInterrupts(void);
void ConfigTimers(void);

void main(void) 
{
    TRISC = 0;                  //portC = output,
    ANSELC = 0;                 //digital
    TRISA = 0b00000100;         //RA = output RA2 = input
    ANSELA = 0;                 //digital
    TRISB = 0b11000000;         //RB7 RB6 = input, RB5 RB5 = output
    ANSELB =0b11000000;         //RB7 RB6 = analog, RB5 RB5 = digital
    PORTB = 0x00;
       
    const int TX_rate = 30;     //how many seconds data is sampled before being transmitted
    ConfigInterrupts();
    ConfigTimers();
    ADC_Init();
    __delay_ms(3000);           //boot time 
    
    while(1){
        int temperature = 0;
        int wind_mph = 0;
        int pressure = 0;
        int wind_avg[29] = {0};                                                 //must change array length if TX_rate changes
        
            ///////////wind data////////////
        for(int x = 0; x <= TX_rate; x++){                                      // sample the data every second TX_rate amount of times
            if(wind_time_high == 0 ){
               wind_avg[x] = 1789 / ( wind_time_low * 4 ) ;                     // wind in mph at time = x     
            }
            else wind_avg[x] = 0;
            wind_mph += wind_avg[x];                                            //add all array together for average
            sample_LED = 1;                                                     //flash led to show system is sampling data
            __delay_ms(500);                                                    //sample every second 
            sample_LED = 0;
            __delay_ms(500);
        }                             
        wind_mph = wind_mph / TX_rate;                                          //average over TX time
        
            ///////////temperature data////////////
        Dig_val = ADC_Read(14);                                                 //Read input on RB6 (Thermistor)
        temperature = Temp_Conv(Dig_val);
        
           ///////////pressure data////////////
        Dig_val = ADC_Read(15);      //Read input on RA5 (Pressure Sensor)
        pressure = Pres_Conv(Dig_val);
        
        
        //pressure = 115;
        TX_LED = 1;                                                             //turn on transmit LED
        Send_DTMF_pack(wind_mph, temperature, pressure);                        //send weather data to DTMF conversion function
        TX_LED = 0;
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
          Wind_LED = 1;          // immediately turn on the LED

            wind_set = 1;
            TMR0L = 0;
            TMR0H = 0;
        }
        else{
          Wind_LED = 0;
            wind_set = 0;
            wind_time_low = TMR0L;
            wind_time_high = TMR0H;
        }
        
       
       PIR0bits.INTF = 0; //clear the flag
    }

       
    }


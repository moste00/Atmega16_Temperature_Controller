/*
 * GccApplication1.c
 *
 * Created: 9/8/2020 1:39:54 PM
 * Author : Mostafa
 */ 

#include <avr/io.h>
#include <util/delay.h>

//circuit and micro-controller parameters 
#define Refrence_Voltage_mv   5000
#define sensor_sensitivity_mv 10
#define ADC_num_bits		  10
//IO channels , you can change it BUT YOU MUST (1) keep TEMPERATURE_CHANNEL between 0 and 7 inclusive , (2) keep the LEDs and buzzer >7 and <32
#define TEMPERATURE_CHANNEL 0
#define YELLO_LED 8
#define GREEN_LED 9
#define RED_LED 10
#define BUZZER 11
//wrapper enums for "0" and "1" for better readability 
typedef enum {IN , OUT}   Pin_State;
typedef enum {LOW , HIGH} Pin_Val  ;

//Hardware layer subroutines :

//Subroutines that allows for individual addressing of the 32 pins directly (0 to 31)	
void    set_Pin_DDR(char, Pin_State)  ;
void    write_Pin(char,  Pin_Val) ;
Pin_Val read_Pin(char)         ;
//ADC routines
void ADC_initialize();
uint16_t ADC_READ(uint8_t channel);


int main(void)
{
	ADC_initialize();
	//initialize four output pins for peripherals 
	set_Pin_DDR(YELLO_LED,OUT);
	set_Pin_DDR(GREEN_LED,OUT);
	set_Pin_DDR(RED_LED,OUT);
	set_Pin_DDR(BUZZER,OUT);
	
	//sensor reading should be divided by this factor 
	//const int normalization_factor = (sensor_sensitivity_mv / 2*Refrence_Voltage_mv) * ( (1 << ADC_num_bits)  - 1 ) ;
	
	while(1){
		uint16_t temp = ADC_READ(TEMPERATURE_CHANNEL) / 2;
		
		if(temp < 20){
			write_Pin(GREEN_LED,HIGH);
		}
		
		if(temp >= 20 && temp <= 40){
			write_Pin(YELLO_LED,HIGH);
		}
		if(temp > 40 ){
			write_Pin(RED_LED,HIGH);
		}
		
		write_Pin(GREEN_LED,LOW);
		write_Pin(YELLO_LED,LOW);
		write_Pin(RED_LED,LOW);
	}
}


void set_Pin_DDR(char Pin_Number, Pin_State st){
	 if(Pin_Number >= 0 && Pin_Number < 8){
			if(st){
				DDRA = DDRA | (0b00000001 << Pin_Number) ;
			}
			else {
				DDRA =  DDRA & ( ~(0b00000001 << Pin_Number) );
			}
			return ;
	 }
	 
	 if(Pin_Number >= 8 && Pin_Number < 16){
		    Pin_Number -= 8 ;
		 	if(st){
			 	 DDRB = DDRB | (0b00000001 << Pin_Number) ;
		 	 }
		 	else {
			 	 DDRB = DDRB & ( ~(0b00000001 << Pin_Number) );
		 	 }
		 	return ;
	 }
		  
	 if(Pin_Number >= 16 && Pin_Number < 24){
		    Pin_Number -= 2*8 ;
			if(st){
				  	 DDRC = DDRC | (0b00000001 << Pin_Number) ;
			}
			else {
				  	 DDRC = DDRC & ( ~(0b00000001 << Pin_Number) );
			}
			return ;
	 }
			   
	 if(Pin_Number >= 24 && Pin_Number < 32){
		    Pin_Number -= 3*8 ;
			if(st){
					   	 DDRD = DDRD | (0b00000001 << Pin_Number) ;
			}
			else {
					   	 DDRD = DDRD & ( ~(0b00000001 << Pin_Number) );
			}
	 }
	 
	 return ;
}

void write_Pin(char Pin_Number,  Pin_Val val) {
		 if(Pin_Number >= 0 && Pin_Number < 8){
			 if(val){
				 PORTA = PORTA | (0b00000001 << Pin_Number) ;
			 }
			 else {
				 PORTA = PORTA & ( ~(0b00000001 << Pin_Number) );
			 }
			 return ;
		 }
		 
		 if(Pin_Number >= 8 && Pin_Number < 16){
			 Pin_Number -= 8 ;
			 if(val){
				 PORTB = PORTB | (0b00000001 << Pin_Number) ;
			 }
			 else {
				 PORTB = PORTB & ( ~(0b00000001 << Pin_Number) );
			 }
			 return ;
		 }
		 
		 if(Pin_Number >= 16 && Pin_Number < 24){
			 Pin_Number -= 2*8 ;
			 if(val){
				 PORTC = PORTC | (0b00000001 << Pin_Number) ;
			 }
			 else {
				 PORTC = PORTC & ( ~(0b00000001 << Pin_Number) );
			 }
			 return ;
		 }
		 
		 if(Pin_Number >= 24 && Pin_Number < 32){
			 Pin_Number -= 3*8 ;
			 if(val){
				 PORTD = PORTD | (0b00000001 << Pin_Number) ;
			 }
			 else {
				 PORTD = PORTD & ( ~(0b00000001 << Pin_Number) );
			 }
		 }
		 
		 return ;
	 
}

Pin_Val read_Pin(char Pin_Number)    {
		 if(Pin_Number >= 0 && Pin_Number < 8){
			 return ( PINA & (0b00000001 << Pin_Number) ) != 0;
		 }
		 
		 if(Pin_Number >= 8 && Pin_Number < 16){
			 Pin_Number -= 8 ;
			 return ( PINB & (0b00000001 << Pin_Number) ) != 0;
		 }
		 
		 if(Pin_Number >= 16 && Pin_Number < 24){
			 Pin_Number -= 2*8 ;
			 return ( PINC & (0b00000001 << Pin_Number) ) != 0;
		 }
		 
		 if(Pin_Number >= 24 && Pin_Number < 32){
			 Pin_Number -= 3*8 ;
			 return ( PIND & (0b00000001 << Pin_Number) ) != 0;
		 }
		 
		 //invalid addresses are LOW by convention
		 return LOW;	
}

void ADC_initialize(){
	ADMUX  = (1<<REFS0);
	
	ADCSRA = (1<<ADEN) |				//sets the enable bit in the control register
			 (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;	//sets the frequency to clockRate/128
}

uint16_t ADC_READ(uint8_t channel){
	//Maximum number of analog channels are 8, 0 to 7
	channel = channel & 0b00000111;
	//clear the 3 LSBs from the previous read, then set them to the new channel
	ADMUX = (ADMUX & 0xF8)|channel;     
	
	//start a conversion by writing to ADSC control bit in the ASCSRA
	ADCSRA |= (1<<ADSC);
	//then wait till it's complete
	while(	!(ADCSRA & (1<<ADIF)) );
	
	return (ADC);
}
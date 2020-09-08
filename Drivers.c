#include "Drivers.h"
#include <avr/io.h>

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
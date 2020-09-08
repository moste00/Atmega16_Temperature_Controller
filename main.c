/*
 * GccApplication1.c
 *
 * Created: 9/8/2020 1:39:54 PM
 * Author : Mostafa
 */ 

#include <avr/io.h>
#include "Drivers.h"


int main(void)
{
	ADC_initialize();
	//initialize four output pins for peripherals 
	set_Pin_DDR(YELLO_LED,OUT);
	set_Pin_DDR(GREEN_LED,OUT);
	set_Pin_DDR(RED_LED,OUT);
	set_Pin_DDR(BUZZER,OUT);
	
	
	while(1){
		//2 is a normalization factor to get temperature in Celsius
		//Its bad practice to hard-code it like that but i can't get the symbolic calculation for it right so hack it will be
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

/*
 * GccApplication1.c
 *
 * Created: 9/8/2020 1:39:54 PM
 * Author : Mostafa
 */ 

#include <avr/io.h>
#include "Drivers.h"


int main(void){
	Initialize_All();
	
	//*****************************************************************************************************************************************************//
	//*****************************************************************************************************************************************************//
	/*
	The main idea of the routine is to keep track of two variables :
	 
																previous_LED : the LED that was on at the previous timestep
																current_LED  : the LED that should be on this timestep
					
	  At each timestep we update current_LED based on the temperature reading, and if it doesn't match previous_LED we turn one off and light the other
	*/
	//*****************************************************************************************************************************************************//
	//*****************************************************************************************************************************************************//
	 
	//previous_LED should always have a value (so that we can always compare it against current_LED)
	char previous_LED = YELLO_LED ; //arbitrary .... could be initialized to any LED 
	char current_LED ;
	
	while(1){
		//2 is a normalization factor to get temperature in Celsius
		//Its bad practice to hard-code it like that but i can't get the symbolic calculation for it right 
		uint16_t temp = ADC_READ(TEMPERATURE_CHANNEL) / 2;
			
		current_LED = (temp < 20)? GREEN_LED :
											 (		(temp <= 40)? YELLO_LED : RED_LED		);
										  
		if(current_LED != previous_LED){
			write_Pin(previous_LED , LOW);
			if(previous_LED == RED_LED) write_Pin(BUZZER , LOW);
			
		}
		write_Pin(current_LED , HIGH);
		if(current_LED == RED_LED) write_Pin(BUZZER , HIGH);
					
		previous_LED = current_LED ;
	}
}

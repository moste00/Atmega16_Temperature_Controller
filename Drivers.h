//IO channels , you can change it BUT YOU MUST (1) keep TEMPERATURE_CHANNEL between 0 and 7 inclusive , (2) keep the LEDs and buzzer >7 and <32
//DON'T FORGET TO CHANGE THE CONNECTIONS IN PROTUES IF YOU CHANGE SOMETHING HERE
#ifndef DRIVERS__
#define DRIVERS__

 #include <avr/io.h>
 
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

#endif
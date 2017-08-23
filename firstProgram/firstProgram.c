// Include Header Files
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// Define Constant Variables
#define F_CPU 1000000

// Function Declaration
void LED();

// main
int main(){

	DDRB = 11111111; // 0xFF
	LED();

	return 0;
}

void LED(){

	while(1){ // for(::)
	
		PORTB = ~PORTB; // ~ - negation
		_delay_ms(1000);
	}
}

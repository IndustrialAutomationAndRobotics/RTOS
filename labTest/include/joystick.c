/*
**	FreeRTOS Demo app for the AVR Butterfly
**
**	Joystick driver and support routines
**
**	Copyright (c) 2007 Steve Judd, Tentacle Robotics
**	All Rights Reserved
**
**	vJoystickInit(queueDepth)	Initialize the joystick
**	char = 	xJoystickGetChar()	get input char from the joystick. Returns zero if none.
**
**	include "joystick.h"
*/

#include <avr/interrupt.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "digital.h"
#include "joystick.h"

static xQueueHandle xJoystickMoves;

unsigned char xJoystickGetChar(unsigned char ucWait) {
	unsigned char ucJoy;
	if (xQueueReceive(xJoystickMoves,&ucJoy,ucWait)==pdTRUE) {
		return(ucJoy);
	} else {
		return(0);
	}
}
void vJoystickInit(unsigned char ucQueueDepth) {

	portENTER_CRITICAL();
	{	// queue for delivering joystick moves
		xJoystickMoves = xQueueCreate( ucQueueDepth, 1);

		// Init ports and interrupts

		_DDRB.B4 = 0;
		_DDRB.B6 = 0;
		_DDRB.B7 = 0;
		PORTB |= PINB_MASK;
		
		DDRE   = 0x00;
		PORTE |= PINE_MASK;

	// Enable pin change interrupts

		PCMSK0  = PINE_MASK;
		PCMSK1  = PINB_MASK;
		EIFR = (1<<PCIF0)|(1<<PCIF1);
		EIMSK = (1<<PCIE0)|(1<<PCIE1);
	}
	portEXIT_CRITICAL();
}

void vJoystickOn() {
	taskENTER_CRITICAL();
	{
		EIFR = (1<<PCIF0)|(1<<PCIF1);
		EIMSK = (1<<PCIE0)|(1<<PCIE1);
	}
	taskEXIT_CRITICAL();			
}

void vJoystickOff() {
	taskENTER_CRITICAL();
	{
		EIFR ^= (1<<PCIF0)|(1<<PCIF1);
		EIMSK ^= (1<<PCIE0)|(1<<PCIE1);
	}
	taskEXIT_CRITICAL();			
}

void vJoystickInterrupt() {
	unsigned char ucJoyMove;
	
	ucJoyMove = (~PINE & PINE_MASK) | (~PINB & PINB_MASK);
	if( xQueueSendFromISR(xJoystickMoves, &ucJoyMove, pdFALSE ) )
	{
		taskYIELD();
	}
}

ISR( SIG_PIN_CHANGE0 ) {
	vJoystickInterrupt();	
}

ISR(SIG_PIN_CHANGE1) {
	vJoystickInterrupt();	
}


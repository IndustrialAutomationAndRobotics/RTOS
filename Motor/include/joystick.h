/*
**	FreeRTOS Demo app for the AVR Butterfly
**
**	Joystick driver and support routines: Definitions
**
**	Copyright (c) 2007 Steve Judd, Tentacle Robotics
**	All Rights Reserved
**
**	vJoystickInit(queueDepth)	Initialize the joystick
**	char = 	xJoystickGetChar()	get input char from the joystick. Returns zero if none.
**
**	include "joystick.h"
*/
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#define	JOY_UP		1<<PIN6		// Port B
#define JOY_LEFT	1<<PIN2		// Port E
#define JOY_RIGHT	1<<PIN3		// Port E
#define JOY_DOWN	1<<PIN7		// Port B
#define JOY_PUSH	1<<PIN4		// Port B

#define PINB_MASK	((1<<PINB4)|(1<<PINB6)|(1<<PINB7))
#define PINE_MASK	((1<<PINE2)|(1<<PINE3))

	void vJoystickInit(unsigned char);
	void vJoystickOff(void);
	void vJoystickOn(void);
	void vJoystickInterrupt(void);
	unsigned char xJoystickGetChar(unsigned char);
	
#endif

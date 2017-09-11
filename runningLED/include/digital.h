//
// Orangutan / Baby Orangutan
//
// Utility Library - Digital Routines
//
// Version 0.23 - 27 Dec 2006
//
// Revision History:
//
// Commands:
//
////// Bitfield Registers //////
//
// _DDRB.B2 = 1;
// _PORTC.B2 = 1;
// _PORTD.B7 = _PINC.B3;
// _PORTD.B5 ^= 1;
//							All this stuff works so you can read
//							write and otherwise fiddle with bits
//							on port registers
//
////// Digital Routines //////
//
// digital_set(port, bit)	Set a bit on a digital port register
// digital_clr(port, bit)	Clear a bit on a digital port register
// digital_get(pin, bit)	Get a bit from a digital port register
//
// Credit where credit is due:
//
// Bitfield registers came from a series of posts on the AVRFreaks
// GCC forum.
// http://www.avrfreaks.net
//
// Digital I/O stuff was written by me, and is the simplest part of
// this whole library.  I don't take a whole lot of credit here.
//
// Tom Benedict
//

#include <avr/io.h>

#ifndef __DIGITAL_
#define __DIGITAL_

/////////////////////////////////////////////////////////////////////
//
// BITFIELD DIGITAL INLINE ROUTINES
//
/////////////////////////////////////////////////////////////////////

// This is an attempt to add the bitfield-style behavior of the CodeVision
// compiler to WinAVR.  For more information search AVRFreaks on
// "bitfield".  Apparently there's a fair bit of disagreement on using
// this approach.  (By the same token there's a fair bit of disagreement
// between owners of Fords and Chevys, so keep this in mind when reading
// the threads on AVRFreaks.)

// In use you'd do something like this:
//
//	_PORTD.B7 = _PINC.B2;
//
// This sets bit 7 on PORTD to the value of bit 2 on PINC.
// Not as clean as the CodeVision implementation, but it works.

typedef struct
   {
      uint8_t B0 : 1;
      uint8_t B1 : 1;
      uint8_t B2 : 1;
      uint8_t B3 : 1;
      uint8_t B4 : 1;
      uint8_t B5 : 1;
      uint8_t B6 : 1;
      uint8_t B7 : 1;
   } bitfield;

#define _PORTA (*((volatile bitfield*)&PORTA))
#define _PINA  (*((volatile bitfield*)&PINA))
#define _DDRA  (*((volatile bitfield*)&DDRA))
#define _PORTB (*((volatile bitfield*)&PORTB))
#define _PINB  (*((volatile bitfield*)&PINB))
#define _DDRB  (*((volatile bitfield*)&DDRB))
#define _PORTC (*((volatile bitfield*)&PORTC))
#define _PINC  (*((volatile bitfield*)&PINC))
#define _DDRC  (*((volatile bitfield*)&DDRC))
#define _PORTD (*((volatile bitfield*)&PORTD))
#define _PIND  (*((volatile bitfield*)&PIND))
#define _DDRD  (*((volatile bitfield*)&DDRD))

/////////////////////////////////////////////////////////////////////
//
// DIGITAL INLINE ROUTINES
//
/////////////////////////////////////////////////////////////////////

// There are three routines, one each to set, clear, or get a bit
// value out of a port register.  Note:  These are inline #defines,
// so there's no penalty for a routine call.  There's also no mode
// checking on the bit, so be sure you know what mode your bits are
// in before using the commands!  
//
// For example, if you don't know the status of the bits on PORTD,
// to get the value on pin 2 you'd run:
//
//		digital_clr(DDRD, PD2);
//		value = digital_get(PIND, PD2);
//
// Likewise, to set the value on pin 2 you'd run:
//
//		digital_set(DDRD, PD2);
//		digital_set(PORTD, PD2);
//
// And to clear the value on pin 2 you'd run:
//
//		digital_set(DDRD, PD2);
//		digital_clr(PRORTD, PD2);
//

// digital_set(PORTN, BIT)
// 		e.g. digital_set(PORTD, PD1);
//		e.g. digital_set(DDRC, PC1);
//
#define digital_set(sfr, bit) ((sfr) |= (1 << (bit)))

// digital_clr(PORTN, BIT)
//		e.g. digital_clr(PORTD, PD1);
//		e.g. digital_clr(DDRC, PC2);
//
#define digital_clr(sfr, bit) ((sfr) &= ~(1 << (bit)))

// digital_get(PINN, BIT)
//		e.g. digital_get(PIND, PD1);
//
#define digital_get(sfr, bit) (bit_is_set((sfr), (bit)))

#endif

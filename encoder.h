/*
  encoder.h - Library for encoder.
  Created by Roman V. Prikhodchenko, 2012.12.21
  Released into the GPLv3.
 */

#ifndef encoder_h
#define encoder_h

#include "Arduino.h"
#include "avr/interrupt.h"

class encoder
{
public:
	encoder(int start_angle);
	int get_angle();
	int set_angle(int angle);
	int get_state();
	byte encoderhalf(byte a, byte b); // return        0 - good: encoder rotated        1 - default, no changes (error)        2 - very strange error
	byte encoderfull(byte a, byte b); // return        0 - good: encoder rotated        1 - default, no changes (error)        2 - very strange error

private:
	volatile int _encoder_angle;
	volatile byte _encoder_state; // == FIFO (Queue)
};

#endif

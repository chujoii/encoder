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
	encoder(int pina, int pinb, int start_angle); // fixme move pina->encoder_pin_a intera->encoder_interrupt_a
	int get_angle();
	void encoderhalf();
private:
	int _encoder_angle;
	byte _encoder_state; // == FIFO (Queue)
	int8_t _interra;
	uint8_t _interrb;
	int _pina;
	int _pinb;

	//void encodersimply();
	//void encoderhalf();
	//void encoderfull();
};

#endif

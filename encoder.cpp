/*
  encoder.cpp - Library for encoder.
  Created by Roman V. Prikhodchenko, 2012.12.21
  Released into the GPLv3.
 */

#include <encoder.h>




encoder::encoder(int pina, int pinb, int start_angle) // fixme move pina->encoder_pin_a intera->encoder_interrupt_a
{
	_encoder_angle = start_angle;
	_encoder_state = 0x1E; // == FIFO (Queue)

	_pina = pina;
	_pinb = pinb;

	pinMode(_pina, INPUT);
	pinMode(_pinb, INPUT);
}









/*
void encoder::encodersimply()
{
	// fixme need use readPort(byte)
	int ra = digitalRead(_pina);
	int rb = digitalRead(_pinb);
	
	if ((HIGH == ra) && (LOW  == rb)) {_encoder_angle++;}
	if ((LOW  == ra) && (HIGH == rb)) {_encoder_angle--;}
}
*/

boolean encoder::encoderhalf()
{
	/*
	  see description in README.org
	  
	  --------------------------------
          xx xx 10 11 0x0B                          xx xx 01 11 0x07
          
	  correct numbers full turn: 0x4B 0x87
	  --------------------------------
	  

          --------------------------------
          xx xx 10 11          = 0x0B     xx xx 01 11          = 0x07
             xx xx 11 01       = 0x0D        xx xx 11 10       = 0x0E
                xx xx 01 00    = 0x04           xx xx 10 00    = 0x08
                   xx xx 00 10 = 0x02              xx xx 00 01 = 0x01             
          correct numbers half turn:
          --------------------------------
	*/


	// fixme need use readPort(byte)

	int ra = digitalRead(_pina);
	int rb = digitalRead(_pinb);
	int a;
	int b;

	int local_encoder_angle = _encoder_angle;
	byte local_encoder_state = _encoder_state;
	boolean clash = true; // if (clash == false) -> no clash: good    if (clash == true) -> clash exist

	if (ra == HIGH) {a = 1;} else {a = 0;}
	if (rb == HIGH) {b = 1;} else {b = 0;}

	local_encoder_state = local_encoder_state << 1;
	local_encoder_state = local_encoder_state | a;
	local_encoder_state = local_encoder_state << 1;
	local_encoder_state = local_encoder_state | b;

	local_encoder_state = local_encoder_state & 0x0F;

	if ((0x0B == local_encoder_state) ||
	    (0x0D == local_encoder_state) ||
	    (0x04 == local_encoder_state) ||
	    (0x02 == local_encoder_state)) {local_encoder_angle--; clash=false;}
	
	if ((0x07 == local_encoder_state) ||
	    (0x0E == local_encoder_state) ||
	    (0x08 == local_encoder_state) ||
	    (0x01 == local_encoder_state)) {local_encoder_angle++; clash=false;}

	if (_encoder_state == local_encoder_state) {clash=true;	return (!clash);}
	
	if (!clash) { // if no_clash -> store angle state
		_encoder_angle = local_encoder_angle;
		_encoder_state = local_encoder_state;
	}

	return (!clash);
}


boolean encoder::encoderfull()
{


	// fixme need use readPort(byte)
	int ra = digitalRead(_pina);
	int rb = digitalRead(_pinb);
	int a;
	int b;
	

	int local_encoder_angle = _encoder_angle;
	byte local_encoder_state = _encoder_state;
	boolean clash = true; // if (clash == false) -> no clash: good    if (clash == true) -> clash exist

	if (ra == HIGH) {a = 1;} else {a = 0;}
	if (rb == HIGH) {b = 1;} else {b = 0;}

	local_encoder_state = local_encoder_state << 1;
	local_encoder_state = local_encoder_state | a;
	local_encoder_state = local_encoder_state << 1;
	local_encoder_state = local_encoder_state | b;

	if ((0x4B == local_encoder_state) ||
            (0x2D == local_encoder_state) ||
            (0xB4 == local_encoder_state) ||
            (0xD2 == local_encoder_state)) {local_encoder_angle--; clash=false;};
	
	if ((0x87 == local_encoder_state) ||
            (0x1E == local_encoder_state) ||
            (0x78 == local_encoder_state) ||
            (0xE1 == local_encoder_state)) {local_encoder_angle++; clash=false;};

	if (_encoder_state == local_encoder_state) {clash=true;} // fixme ????????????????????

	if (!clash) { // if no_clash -> store angle state
		_encoder_angle = local_encoder_angle;
		_encoder_state = local_encoder_state;
	}

	return (!clash);
}




int encoder::get_angle()
{
	return _encoder_angle;
}

int encoder::set_angle(int angle)
{
	_encoder_angle = angle;
	return _encoder_angle;
}

int encoder::get_state()
{
	return _encoder_state;
}

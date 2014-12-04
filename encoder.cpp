/*
  encoder.cpp - Library for encoder.
  Created by Roman V. Prikhodchenko, 2012.12.21
  Released into the GPLv3.
 */

#include <encoder.h>



encoder::encoder(int start_angle)
{
	_encoder_angle = start_angle;
	_encoder_state = 0x1E; // == FIFO (Queue) start good value
}



/*
void encoder::encodersimply(int ra, int rb)
{
	if ((HIGH == ra) && (LOW  == rb)) {_encoder_angle++;}
	if ((LOW  == ra) && (HIGH == rb)) {_encoder_angle--;}
}
*/



byte encoder::encoderhalf(byte a, byte b)
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


	int local_encoder_angle = _encoder_angle;
	byte local_encoder_state = _encoder_state;
	byte result = 1;

	local_encoder_state = ((((local_encoder_state << 1) | a ) << 1 ) | b ) & 0x0F;


	if ((0x0B == local_encoder_state) ||
	    (0x0D == local_encoder_state) ||
	    (0x04 == local_encoder_state) ||
	    (0x02 == local_encoder_state)) {local_encoder_angle--; result=0;}
	
	if ((0x07 == local_encoder_state) ||
	    (0x0E == local_encoder_state) ||
	    (0x08 == local_encoder_state) ||
	    (0x01 == local_encoder_state)) {local_encoder_angle++; result=0;}

	if (_encoder_state == local_encoder_state) {result=2;}
	
	if (0 == result) { // if no_clash -> store angle state
		_encoder_angle = local_encoder_angle;
		_encoder_state = local_encoder_state;
	}
	
	return result; // return        0 - good: encoder rotated        1 - default, no changes (error)        2 - very strange error
}



byte encoder::encoderfull(byte a, byte b)
{
	int local_encoder_angle = _encoder_angle;
	byte local_encoder_state = _encoder_state;
	byte result = 1;

	local_encoder_state = (((local_encoder_state << 1) | a ) << 1 ) | b;

	if ((0x4B == local_encoder_state) ||
            (0x2D == local_encoder_state) ||
            (0xB4 == local_encoder_state) ||
            (0xD2 == local_encoder_state)) {local_encoder_angle--; result=0;};
	
	if ((0x87 == local_encoder_state) ||
            (0x1E == local_encoder_state) ||
            (0x78 == local_encoder_state) ||
            (0xE1 == local_encoder_state)) {local_encoder_angle++; result=0;};

	if (_encoder_state == local_encoder_state) {result=2;} // fixme ????????????????????

	if (0 == result) { // if no_clash -> store angle state
		_encoder_angle = local_encoder_angle;
		_encoder_state = local_encoder_state;
	}

	return result; // return        0 - good: encoder rotated        1 - default, no changes (error)        2 - very strange error
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

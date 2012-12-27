/*
  encoder.cpp - Library for encoder.
  Created by Roman V. Prikhodchenko, 2012.12.21
  Released into the GPLv3.
 */

#include <encoder.h>




encoder::encoder(int pina, int pinb, int start_angle) // fixme move pina->encoder_pin_a intera->encoder_interrupt_a
{
	_encoder_angle = start_angle;
	_encoder_state = 0x00; // == FIFO (Queue)

	//_interra = interra;
	//_interrb = _interrb;
	_pina = pina;
	_pinb = pinb;

	pinMode(_pina, INPUT);
	pinMode(_pinb, INPUT);
	digitalWrite(_pina, HIGH);
	digitalWrite(_pinb, HIGH);

	/*
 	attachInterrupt(_interra, encodersimply, FALLING);
	attachInterrupt(_interrb, encodersimply, FALLING);

	attachInterrupt(_interra, encoderhalf, CHANGE);
	attachInterrupt(_interrb, encoderhalf, CHANGE);
	
	attachInterrupt(_interra, encoderfull, CHANGE);
	attachInterrupt(_interrb, encoderfull, CHANGE);
	*/


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

void encoder::encoderhalf()
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
	
	if (ra == HIGH) {a = 1;} else {a = 0;}
	if (rb == HIGH) {b = 1;} else {b = 0;}

	_encoder_state = _encoder_state << 1;
	_encoder_state = _encoder_state | a;
	_encoder_state = _encoder_state << 1;
	_encoder_state = _encoder_state | b;

	_encoder_state = _encoder_state & 0x0F;

	if ((0x0B == _encoder_state) ||
	    (0x0D == _encoder_state) ||
	    (0x04 == _encoder_state) ||
	    (0x02 == _encoder_state)) {_encoder_angle--;}
	if ((0x07 == _encoder_state) ||
	    (0x0E == _encoder_state) ||
	    (0x08 == _encoder_state) ||
	    (0x01 == _encoder_state)) {_encoder_angle++;}

}

/*
void encoder::encoderfull()
{


	// fixme need use readPort(byte)
	int ra = digitalRead(_pina);
	int rb = digitalRead(_pinb);
	int a;
	int b;
	
	if (ra == HIGH) {a = 1;} else {a = 0;}
	if (rb == HIGH) {b = 1;} else {b = 0;}

	_encoder_state = _encoder_state << 1;
	_encoder_state = _encoder_state | a;
	_encoder_state = _encoder_state << 1;
	_encoder_state = _encoder_state | b;

	if ((0x4B == _encoder_state) ||
            (0x2D == _encoder_state) ||
            (0xB4 == _encoder_state) ||
            (0xD2 == _encoder_state)) {_encoder_angle--;}
	if ((0x87 == _encoder_state) ||
            (0x1E == _encoder_state) ||
            (0x78 == _encoder_state) ||
            (0xE1 == _encoder_state)) {_encoder_angle++;}
}
*/



int encoder::get_angle()
{
	return _encoder_angle;
}

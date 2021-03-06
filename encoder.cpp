/*	
        encoder.cpp - Library for encoder.
        Copyright (C) 2012 Roman V. Prikhodchenko

        This file is part of encoder.

        encoder is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        encoder is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with encoder.  If not, see <http://www.gnu.org/licenses/>.
*/



#include <encoder.h>



encoder::encoder(int start_angle)
{
	_encoder_angle = start_angle;
	_encoder_state = 0x1E; // == FIFO (Queue) start good value
}



byte encoder::encoderhalf(byte a, byte b)
{
	int local_encoder_angle = _encoder_angle;
	byte local_encoder_state = _encoder_state;
	byte result = 1;

	local_encoder_state = ((((local_encoder_state << 1) | a ) << 1 ) | b ) & 0x0F;


	//see description in README.org
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

	//see description in README.org
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

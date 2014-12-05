/*	
        encoder.h - Library for encoder.
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



#ifndef encoder_h
#define encoder_h

#include "Arduino.h"

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

/*
  created 2012.12.21
  by Roman V. Prikhodchenko chujoii@gmail.com
  license GPL
*/

#include <encoder.h>

const int ec_pin_a = 2;
const int ec_pin_a_interrupt = 0;
const int ec_pin_b = 3;
const int ec_pin_b_interrupt = 1;

encoder enc(30);

volatile byte changes = 1;



void eintrptwrapper()
{
	byte a;
	byte b;

	byte ec_port = PIND;

	if ((ec_port & B00001000) != 0) {a = 1;} else {a = 0;}
	if ((ec_port & B00000100) != 0) {b = 1;} else {b = 0;}

	changes = enc.encoderhalf(a, b);
	// or try
	//changes = enc.encoderfull(a, b);
}



void setup ()
{
	pinMode(ec_pin_a, INPUT);
	pinMode(ec_pin_b, INPUT);
	
	digitalWrite(ec_pin_a, HIGH); // uncomment if you need PushUp
	digitalWrite(ec_pin_b, HIGH); // uncomment if you need PushUp
	
	attachInterrupt(ec_pin_a_interrupt, eintrptwrapper, CHANGE);
	attachInterrupt(ec_pin_b_interrupt, eintrptwrapper, CHANGE);
	
	delay(1000);
	Serial.begin(9600);
	Serial.println("start");
}



void print_zero_fill_binary(byte n){
	int mask = 1<<(sizeof(n)*8 - 1); //B10000000;
	while (mask){
		if (n & mask)
			Serial.print("1");
		else
			Serial.print("0");
		mask >>= 1;
	}
}



void loop ()
{

	if (0 == changes) { // return        0 - good: encoder rotated        1 - default, no changes (error)        2 - very strange error
		changes = 1;

		byte ec_state = enc.get_state();
		int ec_angle = enc.get_angle();

		print_zero_fill_binary(ec_state); Serial.print("\t");
		Serial.println(ec_angle);
	}
}

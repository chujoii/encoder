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

encoder enc(ec_pin_a, ec_pin_b, 30);

volatile boolean changes = false;

void eintrptwrapper()
{
	changes = enc.encoderhalf();
	// or try
	//changes = enc.encoderfull();
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
	int mask = 1<<(sizeof(n)*8); //B10000000;
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
	if (changes){
		byte ec_state = enc.get_state();
		int ec_angle = enc.get_angle();
		Serial.print("0x");Serial.print(ec_state, HEX); Serial.print("    ");
		print_zero_fill_binary(ec_state);Serial.print("    ");
		
		Serial.println(ec_angle);
		changes = 0;
	}
}

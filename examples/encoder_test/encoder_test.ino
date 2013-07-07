/*
  created 2012.12.21
  by Roman V. Prikhodchenko chujoii@gmail.com
  license GPL
*/


#include <encoder.h>


encoder enc(2, 3, 30);

boolean changes = true;

void eintrptwrapper()
{
	enc.encoderhalf();
	changes = true;
}

void setup ()
{

	attachInterrupt(0, eintrptwrapper, CHANGE);
	attachInterrupt(1, eintrptwrapper, CHANGE);

	delay(1000);
	Serial.begin(9600);
}



void loop ()
{
	if (changes){
		Serial.println(enc.get_angle());
		changes = false;
	}
	
	delay(100);
}

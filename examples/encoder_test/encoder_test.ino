/*
  created 2012.12.21
  by Roman V. Prikhodchenko chujoii@gmail.com
  license GPL
*/

#include <ssdrcs.h>
#include <encoder.h>

ssdrcs ssegment(7);

encoder enc(2, 3, 30);


void eintrptwrapper()
{
	enc.encoderhalf();
}

void setup ()
{
	attachInterrupt(0, eintrptwrapper, CHANGE);
	attachInterrupt(1, eintrptwrapper, CHANGE);
}



void loop ()
{
	ssegment.SSDdecimal(enc.get_angle(), true);
	delay(100);
}

/*
  created 2012.12.21
  by Roman V. Prikhodchenko chujoii@gmail.com
  license GPL
*/


#include <Ssdrcs.h>

Ssdrcs ssegment(7);

int pina = 2;
int pinb = 3;
uint8_t interra = 0;
uint8_t interrb = 1;

byte encoderstate = 0;
int encoderangle = 50;



void setup ()
{
	pinMode(pina, INPUT);
	pinMode(pinb, INPUT);
	digitalWrite(pina, HIGH);
	digitalWrite(pinb, HIGH);

	attachInterrupt(interra, encoder, CHANGE);
	attachInterrupt(interrb, encoder, CHANGE);

	ssegment.testSSD();
}

void encoder()
{
	/* encoderstate == FIFO (Queue)

	   00 00 00 00 start        B0000 0000=0x00
	   ab ab ab ab







	   correct
	        01 00 10 11        B0100 1011=0x4B
	    ____      _____
	   a    \____|     
	    _______      ____
           b       \____|



	   correct
	        10 00 01 11        B1000 0111=0x87
	    _______      ____
           a       \____|
	    ____      _____
	   b    \____|     


	   other incorrect or not finished:


	   not finished (for example)
	      11   10 00 01   (11)        B1110 0001=0xE1
	       _______          .......
           a__|       \_____...|
	    ________      __..........
	   b        \____|




	   incorrect (small motion)
	    xx xx  01   11        Bxxxx 0111=0x?7 (0x87 imposible ?)
	    _______      _____
	   a       \____|     
	    _______________
           b
	   



	   incorrect (small motion)
	    xx xx 10    11        Bxxxx1011=0x?B (0x4B imposible ?)
	    _______________
           a
	    _______      _____
	   b       \____|     
	   



	   incorrect (small motion)
	        10  11   01    11        B1011 0111=0xB7
	    ______________      ____
           a              \____|
	    ____      ______________
	   b    \____|     



	   incorrect (small motion)
	        01   11   10   11        B0111 1011=0x7B
	    ____      ______________
	   a    \____|     
	    ______________      ____
           b              \____|



	  --------------------------------
	  correct numbers: 0x4B 0x87
	  --------------------------------
	 */


	// fixme need use read(byte)
	int ra = digitalRead(pina);
	int rb = digitalRead(pinb);
	int a;
	int b;
	
	if (ra == HIGH) {a = 1;} else {a = 0;}
	if (rb == HIGH) {b = 1;} else {b = 0;}

	encoderstate = encoderstate << 1;
	encoderstate = encoderstate | a;
	encoderstate = encoderstate << 1;
	encoderstate = encoderstate | b;

	if (0x4B == encoderstate) {encoderangle++;}
	if (0x87 == encoderstate) {encoderangle--;}
		
}


void loop ()
{
	ssegment.SSDdecimal(encoderangle, true);
	delay(100);
}

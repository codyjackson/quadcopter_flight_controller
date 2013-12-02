#include "time.h"
#include "async_reader.h"
#include <Arduino.h>


Pwm::InputPin receiver1(5);
Pwm::InputPin receiver2(6);
void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Time::Microseconds r1 = Time::Microseconds(0);
	Time::Microseconds r2 = Time::Microseconds(0);
	const Time::Microseconds ZERO = Time::Microseconds(0);

	while((r1 == ZERO)||(r2 == ZERO))
	{
		r1 = (r1 == ZERO) ? receiver1.tick() : r1;
		r2 = (r2 == ZERO) ? receiver2.tick() : r2;
	}

	Serial.print(r1.raw());
	Serial.print("  ");
	Serial.print(r2.raw());
	Serial.println("");
}


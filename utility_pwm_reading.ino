#include "pwm_parallel_reader.h"
#include "pwm_parallel_writer.h"

#include <Arduino.h>


Pwm::InputPin receiver(5);

void setup()
{
	Serial.begin(9600);
	receiver.initialize();
	Time::Milliseconds ms(1000);

}

unsigned long cur = 0;

void loop()
{
	receiver.tick();
	if(receiver.get_current_width() != cur)
		Serial.println(cur = receiver.get_current_width());
}


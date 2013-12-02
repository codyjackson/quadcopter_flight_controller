#include "async_reader.h"
#include <Arduino.h>


Pwm::InputPin receiver(5);
void setup()
{
	Serial.begin(9600);
	receiver.initialize();

}

unsigned long cur = 0;
void loop()
{
	receiver.tick();
	if(receiver.get_current_width() != cur)
	{
		Serial.println(cur = receiver.get_current_width());
		receiver = Pwm::InputPin(5);
	}
}


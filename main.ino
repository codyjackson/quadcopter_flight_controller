#include "pwm_parallel_reader.h"

#include <Arduino.h>

Pwm::InputPin pins[2] = {Pwm::InputPin(5),Pwm::InputPin(6)};

void setup()
{
	Serial.begin(9600);
	for(int i = 0; i < sizeof(pins)/sizeof(Pwm::InputPin); ++i)
		pins[i].initialize();
}

void loop()
{
	Pwm::ParallelReader::update_pins<2>(pins);
	Serial.println(pins[0].get_current_width());
	Serial.println(pins[1].get_current_width());
	Serial.println("end");
	delay(500);
}


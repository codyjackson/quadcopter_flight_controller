#include "pwm_parallel_reader.h"
#include "pwm_parallel_writer.h"

#include <Arduino.h>

Pwm::OutputPin opins[2] = {Pwm::OutputPin(6, 0), Pwm::OutputPin(5, 200)};

void setup()
{
	for(char i = 0; i < sizeof(opins)/sizeof(Pwm::OutputPin); ++i)
		opins[i].initialize();
}

void loop()
{
  Pwm::ParallelWriter::send_pulse_to_pins<2>(opins);
  delayMicroseconds(10);
}


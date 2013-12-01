#include <Arduino.h>
#include "time.h"
#include "async_reader.h"
#include "async_writer.h"




Pwm::InputPin p(5);
Pwm::OutputPin p2(5,Time::Microseconds(20000));
Time::Milliseconds ms(1000);

void setup()
{
	
}

void loop()
{
  delayMicroseconds(10);
}


#include "time.h"
#include "async_reader.h"
#include "receiver.h"
#include <Arduino.h>


Receiver r;
void setup()
{
	Serial.begin(9600);
}

void loop()
{
	r.update();
	Serial.print(r.get_thrust_percentage());
	Serial.print(" ");
	Serial.print(r.get_roll_percentage());
	Serial.print(" ");
	Serial.println(r.get_pitch_percentage());
}


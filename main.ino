#include <Arduino.h>
#include <Wire.h>

#include "time.h"
#include "async_reader.h"
#include "async_writer.h"
#include "receiver.h"
#include "accelerometer.h"
#include "gyroscope.h"
#include "i2c.h"
#include "imu.h"
#include "vec.h"
#include "motor.h"
#include "copter.h"
#include "pi_controller.h"




class ScopedTimer
{
public:
	ScopedTimer()
		:m_start(micros())
	{}

	~ScopedTimer()
	{
		Serial.println(micros()-m_start);
	}

private:
	ScopedTimer(const ScopedTimer&);
	const ScopedTimer& operator =(const ScopedTimer&);

	unsigned long m_start;
};


Copter copter;
Receiver receiver;
void setup()
{
	Serial.begin(9600);
	copter.initialize();               
}

void loop()
{
	receiver.update();
	float rollDegrees = receiver.get_roll_percentage()*45.0f;
	float pitchDegrees = -receiver.get_pitch_percentage()*45.0f;
	copter.set_thrust_percentage(receiver.get_thrust_percentage());
	copter.set_target_roll(rollDegrees);
	copter.set_target_pitch(pitchDegrees);
	Serial.print(rollDegrees);
	Serial.print(" ");
	Serial.println(pitchDegrees);
}


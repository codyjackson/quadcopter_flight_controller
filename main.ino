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


//Copter copter;
Receiver r;
Imu imu;
void setup()
{
	Serial.begin(9600);
	imu.initialize();               
}

void loop()
{
	//r.update();
	imu.update();
	Serial.print(imu.get_roll());
	Serial.print("  ");
	Serial.println(imu.get_pitch());

	/*
	m.adjust_output(r.get_thrust_percentage());
	m2.adjust_output(r.get_thrust_percentage());
	m3.adjust_output(r.get_thrust_percentage());
	m4.adjust_output(r.get_thrust_percentage());

	m.send_signal();
	m2.send_signal();
	m3.send_signal();
	m4.send_signal();
	*/
}


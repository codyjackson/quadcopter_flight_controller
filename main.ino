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

Motor m(OutputPin(8), 180);
Receiver r;
Imu imu;
void setup()
{
	Serial.begin(9600);
	imu.initialize();
}

void loop()
{
	r.update();
	imu.update();
	m.adjust_output(0.05);
	m.send_signal();
}


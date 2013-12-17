#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "./../pwm/async_reader.h"

class Receiver
{
public:
	Receiver();

	void update();

	float get_thrust_percentage() const;
	float get_roll_percentage() const;
	float get_pitch_percentage() const;

private:
	void update_thrust();
	void update_roll();
	void update_pitch();

	InputPin _thrustPin;
	InputPin _rollPin;
	InputPin _pitchPin;

	float _thrust;
	float _roll;
	float _pitch;

	enum Channel
	{
		THRUST,
		ROLL,
		PITCH,
		COUNT
	};

	Channel _channel;
};

#endif
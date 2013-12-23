#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "./../pwm/async_reader.h"

class Receiver
{
public:
	Receiver();

	void update();
	float get_left_joy_vertical_percentage() const;
	float get_right_joy_vertical_percentage() const;
	float get_right_joy_horizontal_percentage() const;

	bool is_in_configuration_mode() const;
	enum PiTarget
	{
		PROPORTIONAL,
		INTEGRAL,
		NONE
	};
	PiTarget get_pi_target() const;
	float get_pi_constant() const;

private:
	void update_right_joy_vertical();
	void update_right_joy_horizontal();
	void update_left_joy_vertical();
	void update_left_toggle();

	InputPin _rightJoyVerticalPin;
	InputPin _rightJoyHorizontalPin;
	InputPin _leftJoyVerticalPin;
	InputPin _leftTogglePin;

	float _rightJoyVertical;
	float _rightJoyHorizontal;
	float _leftJoyVertical;
	bool _leftToggle;

	enum Channel
	{
		RIGHT_JOY_VERTICAL,
		RIGHT_JOY_HORIZONTAL,
		LEFT_JOY_VERTICAL,
		LEFT_TOGGLE,
		COUNT
	};

	Channel _channel;
};

#endif
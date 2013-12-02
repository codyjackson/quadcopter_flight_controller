#ifndef __RECEIVER_H__
#define __RECEIVER_H__

class Receiver
{
public:
	Receiver();

	void update();

	float get_thrust_percentage() const;
	float get_roll_percentage() const;
	float get_pitch_percentage() const;

private:
	float _thrust;
	float _roll;
	float _pitch;
};

#endif
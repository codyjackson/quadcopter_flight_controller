#ifndef __COPTER_H__
#define __COPTER_H__

#include "./../imu/imu.h"
#include "./../motor/motor.h"
#include "./../pi_controller/pi_controller.h"

class Copter
{
public:
	Copter();

	void initialize();
	void update();

	void set_thrust_percentage(float thrust);
	void set_target_roll(float roll);
	void set_target_pitch(float pitch);

	void update_pi_constants(float p, float i);

	void turn_on_stabalization();
	void turn_off_stabalization();

private:
	float _thrust;
	PiController _rollPi;
	PiController _pitchPi;
	Imu _imu;

	Motor _frontLeftMotor;
	Motor _frontRightMotor;
	Motor _backLeftMotor;
	Motor _backRightMotor;
};
#endif
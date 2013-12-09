#ifndef __COPTER_H__
#define __COPTER_H__

class Copter
{
public:
	Copter();

	void update();

	void set_thrust_percentage(float thrust);
	void set_target_roll(float roll);
	void set_target_pitch(float pitch);

private:
	float _thrust;
	Pid _rollPid;
	Pid _pitchPid;
	Imu _imu;

	Motor _frontLeftMotor;
	Motor _frontRightMotor;
	Motor _backLeftMotor;
	Motor _backRightMotor;
};
#endif
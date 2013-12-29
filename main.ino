#include <Arduino.h>
#include <EEPROM.h>
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
#include "storage.h"


Copter copter;
Receiver receiver;
float proportionalConstant = 0;
float integralConstant = 0;
const int PROPORTIONAL_ADDRESS = 0;
const int INTEGRAL_ADDRESS = PROPORTIONAL_ADDRESS + sizeof(proportionalConstant);

void* copterTick();

void* endConfigurationTick()
{
	storageWrite<float>(PROPORTIONAL_ADDRESS, proportionalConstant);
	storageWrite<float>(INTEGRAL_ADDRESS, integralConstant);
	copter.update_pi_constants(proportionalConstant, integralConstant);

	return reinterpret_cast<void*>(copterTick);
}

void* configurationTick()
{
	if(!receiver.is_in_configuration_mode())
		return reinterpret_cast<void*>(endConfigurationTick);

	Receiver::PiTarget target = receiver.get_pi_target();
	if(target == Receiver::PROPORTIONAL)
		proportionalConstant = receiver.get_pi_constant();
	else if(target == Receiver::INTEGRAL)
		integralConstant = receiver.get_pi_constant();

	return reinterpret_cast<void*>(configurationTick);
}

void* copterTick()
{
	if(receiver.is_in_configuration_mode())
		return reinterpret_cast<void*>(configurationTick);

	float rollDegrees = receiver.get_right_joy_horizontal_percentage()*45.0f;
	float pitchDegrees = receiver.get_right_joy_vertical_percentage()*45.0f;
	float thrustPercentage = receiver.get_left_joy_vertical_percentage();

	//If thrust is zero I turn stabalization off to prevent the copter from using the
	//motors to reorient it'self when the copter shouldn't be moving.
	if(abs(thrustPercentage) < 0.0001f)
		copter.turn_off_stabalization();
	else
		copter.turn_on_stabalization();

	copter.set_thrust_percentage(thrustPercentage);
	copter.set_target_roll(rollDegrees);
	copter.set_target_pitch(pitchDegrees);
	copter.update();

	return reinterpret_cast<void*>(copterTick);
}

void* (*currentTick)() = reinterpret_cast<void*(*)()>(copterTick);
void setup()
{
	//Delayed copter initialization by 4 seconds so that the IMU averaging takes place 
	//after the copter is on the ground stable since I don't have an on/off switch.
	delay(4000);
	copter.initialize(); 

	proportionalConstant = storageRead<float>(PROPORTIONAL_ADDRESS);
	integralConstant = storageRead<float>(INTEGRAL_ADDRESS);
	copter.update_pi_constants(proportionalConstant, integralConstant);
}

void loop()
{
	receiver.update();
	currentTick = reinterpret_cast<void*(*)()>(currentTick());
}


#ifndef __PARALLEL_WRITER_H__
#define __PARALLEL_WRITER_H__

namespace Pwm
{
	class OutputPin
	{
	public:
		OutputPin(unsigned char pinNumber, const Microseconds& frameWidth);
		void initialize();

		void set_pulse_width(Microseconds pulseWidth);
		void tick();

	private:
		unsigned char _pinNumber;
		Microseconds _pulseWidth;
		Microseconds _frameWidth;
		Microseconds _nextToggle;
	};
}

#endif
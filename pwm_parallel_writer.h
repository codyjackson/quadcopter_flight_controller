#ifndef __PARALLEL_WRITER_H__
#define __PARALLEL_WRITER_H__

namespace Pwm
{
	class OutputPin
	{
	public:
		OutputPin(unsigned char pinNumber, unsigned short width);
		void initialize();

		void set_width(unsigned short width);

		unsigned char get_pin_number() const;
		unsigned short get_width() const;

	private:
		unsigned char _pinNumber;
		unsigned short _width;
	};

	//This does not maintain a constant frame length. This is nice because then we don't 
	//need to spend time blocking.
	class ParallelWriter
	{
	public:
		template <unsigned char NUM_PINS>
		static void send_pulse_to_pins(const OutputPin pins[])
		{
			PinWriter pinWriters[NUM_PINS];
			for(char i = 0; i < NUM_PINS; ++i)
				pinWriters[i] = PinWriter(pins[i]);

			for(;;)
			{
				bool completed = true;
				for(char i = 0; i < NUM_PINS; ++i)
					completed = completed && pinWriters[i].send_pulse();
				if(completed)
					break;
			}
		}

	private:
		class PinWriter
		{
		public:
			PinWriter();
			PinWriter(const OutputPin& pin);

			bool send_pulse();

		private:
			unsigned char _pinNumber;
			unsigned short _width;
			unsigned long _startTime;
			unsigned long _targetEndTime;
		};
	};
}

#endif
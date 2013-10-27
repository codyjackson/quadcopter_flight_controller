#ifndef __PARALLEL_READER_H__
#define __PARALLEL_READER_H__

namespace Pwm
{
	class InputPin
	{
	public:
		InputPin(char pinNumber);
		void initialize();

		short get_current_width() const;
		char get_pin_number() const;

	private:
		void update_width(short width);

		friend class ParallelReader;
		char _pinNumber;
		short _currentWidth;
	};

	//I'm making this parallel reader instead of using the pulsein function in order to avoid having 
	//to pay the 20 ms cost for each channel I want to read. Unfortunately my receiver doesn't support 
	//PPM or I'd use that. I also don't want to buy a PPM encoder so there's that too.
	class ParallelReader
	{
	public:
		//I was trying to figure out some other method of another method of performing parallel 
		//reading but couldn't think of one. There just doesn't seem to be a way of getting around 
		//tight coupling between the PIN class and the update method if I want to be able to perform
		//multiple PWM readings at the same time.
		template<char NUM_PINS>
		static void update_pins(InputPin pins[])
		{
			PinReader pinReaders[NUM_PINS];
			for(char i = 0; i < NUM_PINS; ++i)
				pinReaders[i] = PinReader(pins[i]);


			bool completed = true;
			do
			{
				completed = true;
				for(char i = 0; i < NUM_PINS; ++i)
					completed = completed && pinReaders[i].look_for_width_update_tick();
			}
			while(!completed);

			for(char i = 0; i < NUM_PINS; ++i)
				pins[i].update_width(pinReaders[i].get_updated_width());
		}

	private:
		//I made this class so that I don't have to keep the additional state in the PIN class.
		//This should free up memory for other useful computation.
		class PinReader
		{
		public:
			PinReader();
			PinReader(const InputPin& pin);

			short get_updated_width() const;
			//Returns false if the a new width has been recorded. It will only record a single update.
			bool look_for_width_update_tick();

		private:
			char _pinNumber;
			bool _previousPinValue;
			bool _currentPinValue;
			unsigned long _startTime;
			unsigned long _endTime;
		};
	};
}

#endif
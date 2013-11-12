#include "time.h"

#include <Arduino.h>

namespace Time
{

	Milliseconds::Milliseconds()
		:_ms(0)
	{}

	Milliseconds::Milliseconds(unsigned long ms)
		:_ms(ms)
	{}

	unsigned long Milliseconds::raw() const
	{
		return _ms;
	}


	Milliseconds::operator Microseconds() const
	{
		return Microseconds(*this);
	}

	Milliseconds Milliseconds::since_start()
	{
		return Milliseconds(millis());
	}



	Microseconds::Microseconds()
		:_us(0)
	{}

	Microseconds::Microseconds(unsigned long us)
		:_us(us)
	{}

	Microseconds::Microseconds(const Milliseconds& ms)
		:_us(static_cast<Milliseconds>(ms).raw()*1000)
	{}


	unsigned long Microseconds::raw() const
	{
		return _us;
	}

	Microseconds Microseconds::since_start()
	{
		return Microseconds(micros());
	}


	bool operator<(const Microseconds& lhs, const Microseconds& rhs)
	{
		return lhs.raw() < rhs.raw();
	}

	bool operator>(const Microseconds& lhs, const Microseconds& rhs)
	{
		return lhs.raw() > rhs.raw();
	}

	bool operator==(const Microseconds& lhs, const Microseconds& rhs)
	{
		return lhs.raw() == rhs.raw();
	}

	bool operator<=(const Microseconds& lhs, const Microseconds& rhs)
	{
		return lhs.raw() <= rhs.raw();
	}

	bool operator>=(const Microseconds& lhs, const Microseconds& rhs)
	{
		return lhs.raw() >= rhs.raw();
	}


	bool operator<(const Milliseconds& lhs, const Milliseconds& rhs)
	{
		return lhs.raw() < rhs.raw();
	}

	bool operator>(const Milliseconds& lhs, const Milliseconds& rhs)
	{
		return lhs.raw() > rhs.raw();
	}

	bool operator==(const Milliseconds& lhs, const Milliseconds& rhs)
	{
		return lhs.raw() == rhs.raw();
	}

	bool operator<=(const Milliseconds& lhs, const Milliseconds& rhs)
	{
		return lhs.raw() <= rhs.raw();
	}

	bool operator>=(const Milliseconds& lhs, const Milliseconds& rhs)
	{
		return lhs.raw() >= rhs.raw();
	}


	bool operator<(const Milliseconds& lhs, const Microseconds& rhs)
	{
		return static_cast<Microseconds>(lhs) < rhs;
	}

	bool operator>(const Milliseconds& lhs, const Microseconds& rhs)
	{
		return static_cast<Microseconds>(lhs) > rhs;
	}

	bool operator==(const Milliseconds& lhs, const Microseconds& rhs)
	{
		return static_cast<Microseconds>(lhs) == rhs;
	}

	bool operator<=(const Milliseconds& lhs, const Microseconds& rhs)
	{
		return static_cast<Microseconds>(lhs) <= rhs;
	}

	bool operator>=(const Milliseconds& lhs, const Microseconds& rhs)
	{
		return static_cast<Microseconds>(lhs) >= rhs;
	}


	bool operator<(const Microseconds& lhs, const Milliseconds& rhs)
	{
		return lhs < static_cast<Microseconds>(rhs);
	}

	bool operator>(const Microseconds& lhs, const Milliseconds& rhs)
	{
		return lhs > static_cast<Microseconds>(rhs);
	}

	bool operator==(const Microseconds& lhs, const Milliseconds& rhs)
	{
		return lhs == static_cast<Microseconds>(rhs);
	}

	bool operator<=(const Microseconds& lhs, const Milliseconds& rhs)
	{
		return lhs <= static_cast<Microseconds>(rhs);
	}

	bool operator>=(const Microseconds& lhs, const Milliseconds& rhs)
	{
		return lhs >= static_cast<Microseconds>(rhs);
	}

}
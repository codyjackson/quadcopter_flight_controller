#ifndef __TIME_H__
#define __TIME_H__

namespace Time
{
	class Milliseconds;

	class Microseconds
	{
	public:
		Microseconds();
		explicit Microseconds(unsigned long ms);
		explicit Microseconds(const Milliseconds& us);

		unsigned long raw() const;

		operator Milliseconds() const;

		static Microseconds since_start();

	private:
		unsigned long _us;
	};

	class Milliseconds
	{
	public:
		Milliseconds();
		explicit Milliseconds(unsigned long ms);

		unsigned long raw() const;

		operator Microseconds() const;

		static Milliseconds since_start();

	private:
		unsigned long _ms;
	};

	bool operator<(const Microseconds& lhs, const Microseconds& rhs);
	bool operator>(const Microseconds& lhs, const Microseconds& rhs);
	bool operator==(const Microseconds& lhs, const Microseconds& rhs);
	bool operator!=(const Microseconds& lhs, const Microseconds& rhs);
	bool operator<=(const Microseconds& lhs, const Microseconds& rhs);
	bool operator>=(const Microseconds& lhs, const Microseconds& rhs);
	Microseconds operator+(const Microseconds& lhs, const Microseconds& rhs);
	Microseconds operator-(const Microseconds& lhs, const Microseconds& rhs);

	bool operator<(const Milliseconds& lhs, const Milliseconds& rhs);
	bool operator>(const Milliseconds& lhs, const Milliseconds& rhs);
	bool operator==(const Milliseconds& lhs, const Milliseconds& rhs);
	bool operator!=(const Milliseconds& lhs, const Milliseconds& rhs);
	bool operator<=(const Milliseconds& lhs, const Milliseconds& rhs);
	bool operator>=(const Milliseconds& lhs, const Milliseconds& rhs);
	Milliseconds operator+(const Milliseconds& lhs, const Milliseconds& rhs);
	Milliseconds operator-(const Milliseconds& lhs, const Milliseconds& rhs);
}

#endif
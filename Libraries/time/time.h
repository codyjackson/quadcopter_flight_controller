#ifndef __TIME_H__
#define __TIME_H__

namespace Time
{
	class Milliseconds;

	class Microseconds
	{
	public:
		Microseconds();
		explicit Microseconds(long ms);
		explicit Microseconds(const Milliseconds& us);

		long raw() const;

		operator Milliseconds() const;

		static Microseconds since_start();

	private:
		long _us;
	};

	class Milliseconds
	{
	public:
		Milliseconds();
		explicit Milliseconds(long ms);

		long raw() const;

		operator Microseconds() const;

		static Milliseconds since_start();

	private:
		long _ms;
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
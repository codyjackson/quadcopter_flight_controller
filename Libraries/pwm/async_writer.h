#ifndef __PARALLEL_WRITER_H__
#define __PARALLEL_WRITER_H__

#include "./../time/time.h"


class OutputPin
{
public:
	OutputPin(unsigned char pinNumber);

	void turn_on();
	void turn_off();

private:
	unsigned char _pinNumber;
};

#endif
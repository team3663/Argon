#ifndef PIDULTRASONIC_H
#define PIDULTRASONIC_H

#include "PIDSource.h"
//#include "Robot.h"

class PIDUltrasonic: public PIDSource
{
private:

public:
	virtual double PIDGet();
};

#endif

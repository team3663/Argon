#ifndef PIDDRIVE_H
#define PIDDRIVE_H

//#include "Robot.h"
#include "PIDOutput.h"

class PIDDrive: public PIDOutput
{
public:
	void PIDWrite(float output);
};

#endif

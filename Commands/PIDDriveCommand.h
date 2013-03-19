#ifndef PIDCOMMAND_H
#define PIDCOMMAND_H

#include "../Robot.h"

class PIDDriveCommand: public PIDCommand
{
public:
	PIDDriveCommand(float distance);
protected:
	float _distance;
	void UsePIDOutput(double output);
	double ReturnPIDInput();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

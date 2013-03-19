#ifndef DRIVETESTCOMMAND_H
#define DRIVETESTCOMMAND_H

#include "../Robot.h"

class DriveTestCommand: public Command
{
public:
	DriveTestCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

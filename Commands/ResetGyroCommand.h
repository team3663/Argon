#ifndef RESETGYROCOMMAND_H
#define RESETGYROCOMMAND_H

#include "../Robot.h"

class ResetGyroCommand: public Command
{
public:
	ResetGyroCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

#ifndef TARGETTING_COMMAND_H
#define TARGETTING_COMMAND_H

#include "../Robot.h"
#include "Commands/Command.h"

class TargettingCommand: public Command
{
public:
	TargettingCommand();
	~TargettingCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};
#endif

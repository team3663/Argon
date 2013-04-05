#ifndef HORIZONTAL_TARGET_COMMAND_H
#define HORIZONTAL_TARGET_COMMAND_H

#include "../Robot.h"
#include "TurnDegreesCommand.h"

class HorizontalTargetCommand: public Command
{
public:
	HorizontalTargetCommand();
	~HorizontalTargetCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool done;
	float constant;
};

#endif

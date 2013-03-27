#ifndef VERTICAL_TARGET_COMMAND_H
#define VERTICAL_TARGET_COMMAND_H

#include "Commands/Command.h"
#include "../Robot.h"

class VerticalTargetCommand: public Command
{
public:
	VerticalTargetCommand();
	~VerticalTargetCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool done;
};

#endif

#ifndef SHOOT_UNTIL_EMPTY_COMMAND_H
#define SHOOT_UNTIL_EMPTY_COMMAND_H

#include "Commands/Command.h"
#include "ShootPistonCommand.h"

class ShootUntilEmptyCommand: public Command
{
public:
	ShootUntilEmptyCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

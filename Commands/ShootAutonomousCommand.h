#ifndef SHOOT_AUTONOMOUS_COMMAND_H
#define SHOOT_AUTONOMOUS_COMMAND_H

#include "Commands/CommandGroup.h"

class ShootAutonomousCommand: public CommandGroup {
public:
	ShootAutonomousCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

#ifndef TELEOP_INIT_COMMAND_H
#define TELEOP_INIT_COMMAND_H

#include "../Robot.h"
#include "Commands/Command.h"

class TeleopInitCommand: public Command
{
public:
	TeleopInitCommand();
	~TeleopInitCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	static const float maxDriveSpeed = 0.8;
	static const float minDriveSpeed = 0.4;
};

#endif

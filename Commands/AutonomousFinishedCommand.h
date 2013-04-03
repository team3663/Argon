#ifndef AUTONOMOUS_FINISHED_COMMAND_H
#define AUTONOMOUS_FINISHED_COMMAND_H

#include "../Robot.h"
#include "Commands/Command.h"

/*
 * A command that sets the boolean autonomousFinished to true,
 * indicating that TeleopInitCommand can begin. This command should be placed 
 * as a AddSequential() at the point in any autonomous command where the command 
 * has reached the point where the robot is in a position to start TeleopInitCommand()
 */

class AutonomousFinishedCommand: public Command
{
public:
	AutonomousFinishedCommand();
	~AutonomousFinishedCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

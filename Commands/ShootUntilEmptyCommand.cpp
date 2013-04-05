#include "ShootUntilEmptyCommand.h"

ShootUntilEmptyCommand::ShootUntilEmptyCommand()
{
	
}

void ShootUntilEmptyCommand::Initialize()
{
	
}

void ShootUntilEmptyCommand::Execute()
{
	ShootPistonCommand().Run(); // command ends immediatly, no need to put in while loop
}

bool ShootUntilEmptyCommand::IsFinished()
{
	WaitCommand command(0.5);
	while (!command.Run()) {} // wait until a frisbee can drop down
	if (Robot::photoelectric->GetShooterStatus())
		return true;
	else
		return false;
}

void ShootUntilEmptyCommand::End()
{
	
}

void ShootUntilEmptyCommand::Interrupted()
{
	
}

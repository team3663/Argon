#include "ResetGyroCommand.h"

ResetGyroCommand::ResetGyroCommand()
{
	
}

void ResetGyroCommand::Initialize()
{
	Robot::driveTrain->ResetGyro();
}

void ResetGyroCommand::Execute()
{
	
}

bool ResetGyroCommand::IsFinished()
{
	return true;
}

void ResetGyroCommand::End()
{
	
}

void ResetGyroCommand::Interrupted()
{
	
}

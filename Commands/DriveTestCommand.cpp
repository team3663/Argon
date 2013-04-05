#include "DriveTestCommand.h"

DriveTestCommand::DriveTestCommand()
{
	Requires(Robot::driveTrain);
	SetTimeout(1.0);
}

void DriveTestCommand::Initialize()
{
	
}

void DriveTestCommand::Execute()
{
	Robot::driveTrain->Drive(0.6,0);
}

bool DriveTestCommand::IsFinished()
{
	return IsTimedOut();
}

void DriveTestCommand::End()
{
	
}

void DriveTestCommand::Interrupted()
{
	End();
}


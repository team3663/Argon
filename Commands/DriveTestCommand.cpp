#include "DriveTestCommand.h"

DriveTestCommand::DriveTestCommand()
{
	
}

void DriveTestCommand::Initialize()
{
	
}

void DriveTestCommand::Execute()
{
	RobotMap::driveTrainSpeedControlLeft1->Set(0.5);
	
}

bool DriveTestCommand::IsFinished()
{
	return false;
}

void DriveTestCommand::End()
{
	
}

void DriveTestCommand::Interrupted()
{
	End();
}


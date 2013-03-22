#include "TurnDegreesCommand.h"

TurnDegreesCommand::TurnDegreesCommand()
{
	Requires(Robot::driveTrain);
	Robot::driveTrain->ResetGyro();
	_newAngle = 60;
}

void TurnDegreesCommand::Initialize()
{
	Robot::driveTrain->Drive(0.0, 0.5);
}

void TurnDegreesCommand::Execute()
{
	
}

bool TurnDegreesCommand::IsFinished()
{
	_currAngle = Robot::driveTrain->GetAngle();
	if((_newAngle + 5 > _currAngle) && (_currAngle > _newAngle - 5))
	{
		return true;
	}
	return false;
	
	
}

void TurnDegreesCommand::End()
{
	Robot::driveTrain->Stop();
}

void TurnDegreesCommand::Interrupted()
{
	End();
}


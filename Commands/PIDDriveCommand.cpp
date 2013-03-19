#include "PIDDriveCommand.h"

PIDDriveCommand::PIDDriveCommand(float distance): PIDCommand(0.5, 0.3, 0.2)
{
	Requires(Robot::driveTrain);
	_distance = distance;
	SetTimeout(15.0);
}

void PIDDriveCommand::UsePIDOutput(double output)
{
	Robot::driveTrain->Drive(output * 0.8, 0.0);
}

double PIDDriveCommand::ReturnPIDInput()
{
	//return Robot::rangeFinder->Distances[0];
	return Robot::driveTrain->GetRotations();
}

void PIDDriveCommand::Initialize()
{
	SetSetpointRelative(_distance);
}

void PIDDriveCommand::Execute()
{
	
}

bool PIDDriveCommand::IsFinished()
{
	return GetPIDController()->OnTarget() || IsTimedOut();
}

void PIDDriveCommand::End()
{
	
}

void PIDDriveCommand::Interrupted()
{
	End();
}


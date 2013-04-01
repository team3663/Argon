#include "TeleopInitCommand.h"

TeleopInitCommand::TeleopInitCommand()
{
	Requires(Robot::driveTrain);
	SetTimeout(10.0);
}

TeleopInitCommand::~TeleopInitCommand()
{

}

void TeleopInitCommand::Initialize()
{
	
}

void TeleopInitCommand::Execute()
{
	float driveSpeed;
	float distance = Robot::rangeFinder->Distances[1]; // read from the back ultrasonic
	
	if (distance > 24)
		driveSpeed = maxDriveSpeed;
	else if (distance > 12)
		driveSpeed = minDriveSpeed;
	else
		driveSpeed = 0.0;
	
	Robot::driveTrain->Drive(driveSpeed, 0.0);
}

bool TeleopInitCommand::IsFinished()
{
	if (Robot::oi->GetX() < -0.3 || Robot::oi->GetX() > 0.3)
		return true;
	if (Robot::oi->GetY() < -0.3 || Robot::oi->GetY() > 0.3)
		return true;
	if (IsTimedOut())
		return true;
	if (TimeSinceInitialized() > 1.0 && Robot::photoelectric->GetGroundStatus())
		return true; // Dont start checking for the line until weve driven for a while in case were on top of it at the start of the command
	
	return false;
	
}

void TeleopInitCommand::End()
{
	Robot::driveTrain->Drive(0.0, 0.0);
}

void TeleopInitCommand::Interrupted()
{
	End();
}

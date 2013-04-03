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
	// make sure we are in low gear in case we get hit while driving
	Robot::driveTrain->GearShift(false);

	// reset encoder to zero, then drive a short bit to get encoder values working
	Robot::driveTrain->DriveEncoderReset();  // reset encoder to zero to start;
	Robot::driveTrain->Drive(0.5,0);         // short drive to start the encoder counting
	Wait(0.25);                               // drive a short bit
}

void TeleopInitCommand::Execute()
{
	float driveSpeed;
	float obstacleDistance  = Robot::rangeFinder->Distances[0]; // read from the front ultrasonic
	// use right encoder to calculate how far is left to drive potentially
	float distanceRemaining = distanceToDrive - Robot::driveTrain->GetRightDistance(); 
	
	if (distanceRemaining > 12 && obstacleDistance < 24) { // check for obstacle in our path
		driveSpeed = minDriveSpeed; // drive at slow speed to push obstacle aside
	}
	else {  // simple decay calculation, since we aren't driving that fast
		if (distanceRemaining > 24)
			driveSpeed = maxDriveSpeed;
	    else if (distanceRemaining > 12)
		    driveSpeed = minDriveSpeed;
	    else
		    driveSpeed = 0.0;
	}
	
	float leftDistance = Robot::rangeFinder->Distances[2];
	float curve = (leftDistance / 12) - 1; // change the curve so we stay one foot from the wall
	
	if (curve > 0.5)
		curve = 0.5;
	else if (curve < -0.5)
		curve = -0.5;
	
	Robot::driveTrain->Drive(driveSpeed, curve);
}

bool TeleopInitCommand::IsFinished()
{
	if (Robot::oi->GetX() < -0.3 || Robot::oi->GetX() > 0.3)
		return true;
	if (Robot::oi->GetY() < -0.3 || Robot::oi->GetY() > 0.3)
		return true;
	if (IsTimedOut())
		return true;
	if ((distanceToDrive - Robot::driveTrain->GetRightDistance()) > 36 && Robot::photoelectric->GetGroundStatus())
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

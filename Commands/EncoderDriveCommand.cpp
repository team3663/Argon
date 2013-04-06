/*#include "EncoderDriveCommand.h"

EncoderDriveCommand::EncoderDriveCommand(float distanceToDrive, float maxSpeed, float decayFactor) {
	Requires(Robot::driveTrain);

	this->distanceToDrive = distanceToDrive;
	this->maxSpeed    = maxSpeed;    // maximum speed for driving
	this->decayFactor = decayFactor; // how rapidly to decrease speed as approaching target
	driveSpeed      = 0;      // speed value for robot drive
	curve           = 0;      // curve value for robot drive
	driveProgress   = 0;      // distance traveled so far
	reachedEndpoint = false;  // whether command is completed or not
	
	if (distanceToDrive < 0)
		driveDirection = -1;
	else
		driveDirection = 1;
	
	SetTimeout(10.0);  // set the command to end at 10 seconds if not yet completed
}

void EncoderDriveCommand::Initialize() {
	//check how far we want to go and make it out of 100%
	
	Robot::driveTrain->DriveEncoderReset();  // reset encoder to zero to start;
	//Robot::driveTrain->Drive(0.5,0);         // short drive to start the encoder counting
	//Wait(0.5);                               // drive a half second
	Robot::driveTrain->Drive(maxSpeed * driveDirection, 0.0);
}

void EncoderDriveCommand::Execute() {
	// get distance traveled as reported by right encoder
//	driveProgress = Robot::driveTrain->GetRightDistance();
	
	// set drive speed
//	driveSpeed = ((distanceToDrive - (driveProgress * driveDirection))/distanceToDrive) * decayFactor * maxSpeed;
//	if (driveSpeed > maxSpeed) driveSpeed  = maxSpeed; // just in case, make sure it doesn't drive too fast
//	if (driveSpeed < 0.40) driveSpeed = 0.40;     // don't drive any slower than that or it doesn't move
    // check that both encoders are measuring the same
	// This creates a ratio around 1, then subtracts to make it vary around 0 instead
	// Use this as the correcting curve in the drive command
	//curve = (Robot::driveTrain->GetRightDistance() / Robot::driveTrain->GetLeftDistance()) - 1;
	// now drive
//	Robot::driveTrain->Drive(-driveSpeed * driveDirection, 0.0);
	Robot::driveTrain->Drive(maxSpeed * driveDirection, 0.0);
}
// Make this return true when this Command no longer needs to run execute()
bool EncoderDriveCommand::IsFinished() {
	if ((driveDirection * Robot::driveTrain->GetRightDistance()) >= (driveDirection * distanceToDrive)) // if we are at or past the target distance
		return true;
	else if (IsTimedOut()) // if the time has run out
		return true;
	else
		return false;
}
// Called once after isFinished returns true
void EncoderDriveCommand::End() {
	Robot::driveTrain->Stop();
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EncoderDriveCommand::Interrupted() {
	End();
}
*/
#include "EncoderDriveCommand.h"

EncoderDriveCommand::EncoderDriveCommand(float finishPoint) {
	
	Requires(Robot::driveTrain);
	
	destination = finishPoint;

	driveSpeed = 0;
	curve = 0;
	driveProgress = 0;
	finished = false;
	
	if (finishPoint > 0)
		driveDirection = 1;
	else
		driveDirection = -1;

	SetTimeout(10.0);
}

void EncoderDriveCommand::Initialize() {
	//check how far we want to go and make it out of 100%
	//limit power to 80% max
	//increase speed up until 50% then decrease

	Robot::driveTrain->DriveEncoderReset();
}

void EncoderDriveCommand::Execute() {
	
	driveProgress = Robot::driveTrain->GetRightDistance() / destination;

	if (driveProgress > 1)
	{
		driveProgress = 1;
	}
	
	if (driveProgress < 0.5)
	{
		driveSpeed = 0.4;
	}
	else if (driveProgress > 0.5 && driveProgress < 1.0)
	{
		driveSpeed = 1 - driveProgress;
	}
	else if (driveProgress >= 1)
	{
		driveSpeed = 0;
		finished = true;
	}
	else
	{
		
	}

	if (driveSpeed > 0.8)
		driveSpeed = 0.8;
	else if (driveSpeed < 0.3)
		driveSpeed = 0.3;

	Robot::driveTrain->Drive(driveSpeed * driveDirection, 0.0);
}

bool EncoderDriveCommand::IsFinished() {
	return finished || IsTimedOut();
}

void EncoderDriveCommand::End() 
{
	Robot::driveTrain->Stop();
}

void EncoderDriveCommand::Interrupted() {
	End();
}

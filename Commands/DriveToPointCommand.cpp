#include "DriveToPointCommand.h"

#define MIN_DRIVE_SPEED  0.40   //minimum percent drive speed to use
#define MIN_CORRECTION_DIST  6  // minimum distance at which to check for curve correction

DriveToPointCommand::DriveToPointCommand(float targetDistance, float maxSpeed, int frontSonic) {
	Requires(Robot::driveTrain);
	
	this->targetDistance = targetDistance;
	this->maxSpeed  = maxSpeed;    // maximum speed for driving
	this->frontSonic = frontSonic; // ultrasonic of the direction we are traveling
	currDistance = Robot::rangeFinder->Distances[frontSonic]; // how far away are we at start? 
	driveSpeed      = 0;      // speed value for robot drive
	curve           = 0;      // curve value for robot drive
	distanceToDrive = 0;      // how far to drive
	decayFactor     = 4;      // how rapidly to decrease speed as approaching target
	reachedEndpoint = false;  // whether command is completed or not
	
	SetTimeout(10.0);  // set the command to end at 10 seconds if not yet completed
}

void DriveToPointCommand::Initialize() {
	if (frontSonic == 0)
		Robot::driveTrain->Drive(0.3,0.0);   // short drive to start without tipping over
	else
		Robot::driveTrain->Drive(-0.3,0.0);   // short drive to start without tipping over
	
	WaitCommand(0.2).Run();          	// drive for a short while
    // figure out how far we need to go
	distanceToDrive = Robot::rangeFinder->Distances[frontSonic] - targetDistance;
}

void DriveToPointCommand::Execute() {
	// check our current location
	currDistance = Robot::rangeFinder->Distances[frontSonic];
	// set drive speed
	driveSpeed = ((currDistance - targetDistance)/distanceToDrive) * decayFactor * maxSpeed;
	if (driveSpeed > maxSpeed) driveSpeed = maxSpeed; // just in case, make sure it doesn't drive too fast
	if (driveSpeed < MIN_DRIVE_SPEED) driveSpeed = MIN_DRIVE_SPEED;     // don't drive any slower than that or it doesn't move
    // check that both encoders are measuring the same
	// This creates a ratio around 1, then subtracts to make it vary around 0 instead
	// Use this as the correcting curve in the drive command
	if ((distanceToDrive - currDistance) > MIN_CORRECTION_DIST) { // if we have moved far enough that they are both positive
	    //curve = (Robot::driveTrain->GetRightDistance() / Robot::driveTrain->GetLeftDistance()) - 1;
	    Robot::driveTrain->Drive(-driveSpeed,0.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToPointCommand::IsFinished() {
	// end if we are now at or beyond the target distance from the obstacle
	if (Robot::rangeFinder->Distances[frontSonic] <= targetDistance)
		return true;
	else if (IsTimedOut())
		return true;
	else
		return false;
}
// Called once after isFinished returns true
void DriveToPointCommand::End() {
	Robot::driveTrain->Stop();
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToPointCommand::Interrupted() {
	End();
}

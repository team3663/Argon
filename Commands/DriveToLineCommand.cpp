#include "DriveToLineCommand.h"
#define MIN_SPEED 0.3

DriveToLineCommand::DriveToLineCommand(float distanceToDrive, float maxSpeed, int decay) {
	Requires(Robot::driveTrain);
	
	driveSpeed      = 0;      // speed value for robot drive
	_maxSpeed        = maxSpeed;    // maximum speed for driving
	curve           = 0;      // curve value for robot drive
	driveProgress   = 0;      // distance traveled so far
	decayFactor     = decay;      // how rapidly to decrease speed as approaching target
	reachedEndpoint = false;  // whether command is completed or not
	driveDistance = distanceToDrive;
	
	SetTimeout(10.0);  // set the command to end at 10 seconds if not yet completed
}

void DriveToLineCommand::Initialize() {
	Robot::driveTrain->DriveEncoderReset();  // reset encoder to zero to start;
	Robot::driveTrain->Drive(0.4,0);        // short drive to start the encoder counting
	WaitCommand(0.25).Run();               
}

void DriveToLineCommand::Execute() {
	// check distance traveled relative to total distance to drive (value always < 1 ) 
	driveProgress = Robot::driveTrain->GetRightDistance();
	if (driveProgress >= driveDistance) {
		driveSpeed = 0;  // done driving, we are past the target point
		reachedEndpoint = true;
	}
	// if we haven't reached target point, set drive speed
	driveSpeed = ((driveDistance - driveProgress)/driveDistance) * decayFactor * _maxSpeed;
	if (driveSpeed > _maxSpeed) driveSpeed  = _maxSpeed; // just in case, make sure it doesn't drive too fast
	if (driveSpeed < MIN_SPEED) driveSpeed = MIN_SPEED;     // don't drive any slower than that or it doesn't move
    // check that both encoders are measuring the same
	// This creates a ratio around 1, then subtracts to make it vary around 0 instead
	// Use this as the correcting curve in the drive command
	curve = (Robot::driveTrain->GetRightDistance() / Robot::driveTrain->GetLeftDistance()) - 1;
	Robot::driveTrain->Drive(driveSpeed,curve);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToLineCommand::IsFinished() {
	return reachedEndpoint || IsTimedOut() || Robot::photoelectric->GetGroundStatus();  // returns true if endpoint or timed out
}

// Called once after isFinished returns true
void DriveToLineCommand::End() {
	// we should stop the drive here
	Robot::driveTrain->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToLineCommand::Interrupted() {
	End();
}

// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "DriveToPointCommand.h"
DriveToPointCommand::DriveToPointCommand(float targetDistance, bool frontSonic): rfPort(frontSonic), currDistance(Robot::rangeFinder->Distances[rfPort ? 0 : 1]) {
	// driveDirection: 1 = forward, -1 = backward (other sides can't drive straight)
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain);
	
	driveSpeed      = 0;      // speed value for robot drive
	maxSpeed        = 1.0;    // maximum speed for driving
	curve           = 0;      // curve value for robot drive
	distanceToDrive = 0;      // how far to drive
	decayFactor     = 4;      // how rapidly to decrease speed as approaching target
	reachedEndpoint = false;  // whether command is completed or not
	_targetDistance = targetDistance;

	
	SetTimeout(10.0);  // set the command to end at 10 seconds if not yet completed
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

void DriveToPointCommand::Initialize() {
	if (rfPort){
		Robot::driveTrain->Drive(0.5,0.0);   // short drive to start without tipping over	
	}
	else
	{
		Robot::driveTrain->Drive(-0.5,0.0);   // short drive to start without tipping over
	}
	Wait(0.2);          	// drive for a short while
	//currDistance = Robot::rangeFinder->GetDistance();

	distanceToDrive = currDistance - _targetDistance;
}

void DriveToPointCommand::Execute() {
	// check distance traveled relative to total distance to drive (value always < 1 ) 
	//currDistance = Robot::rangeFinder->GetDistance();
	if (currDistance <= _targetDistance) {
		driveSpeed = 0;  // done driving, we are past the target point
		reachedEndpoint = true;
	}
	// if we haven't reached target point, set drive speed
	driveSpeed = ((currDistance - _targetDistance)/distanceToDrive) * decayFactor * maxSpeed;
	if (driveSpeed > maxSpeed) driveSpeed  = maxSpeed; // just in case, make sure it doesn't drive too fast
	if (driveSpeed < 0.20) driveSpeed = 0.20;     // don't drive any slower than that or it doesn't move
    // check that both encoders are measuring the same
	// This creates a ratio around 1, then subtracts to make it vary around 0 instead
	// Use this as the correcting curve in the drive command
	Robot::driveTrain->Drive(driveSpeed,0);
	
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line4, "DriveSpeed: %f", driveSpeed);
	DriverStationLCD::GetInstance()->UpdateLCD();
}
// Make this return true when this Command no longer needs to run execute()
bool DriveToPointCommand::IsFinished() {
	return reachedEndpoint || IsTimedOut();  // returns true if endpoint or timed out
}
// Called once after isFinished returns true
void DriveToPointCommand::End() {
	// we should stop the drive here
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToPointCommand::Interrupted() {
	End();
}
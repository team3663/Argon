#include "TurnDegreesCommand.h"

TurnDegreesCommand::TurnDegreesCommand(float degreesToTurn)
{
	Requires(Robot::driveTrain);
	_degreesToTurn = degreesToTurn;
	turnProgress  = 0;    // how far we have turned so far
	driveSpeed    = 0;    // how quickly to drive while turning
	maxSpeed      = 0.8;  // the fastest to drive while turning
	decayFactor   = 3;    // how quickly to slow down as approaching goal
	turnDirection = 0;    // which direction we are rotating
}

void TurnDegreesCommand::Initialize()
{
	Robot::driveTrain->ResetGyro();
	WaitCommand(1.0).Run();
	// drive initially to start up a little gracefully
	//Robot::driveTrain->Drive(0.0, 0.4);   // with 0.0 for forward progress, this rotates in place
	// check whether we are turning clockwise or counter
	if (_degreesToTurn < 0) { 
		turnDirection = -1;
	}
	else {
		turnDirection = 1;
	}
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line6, "turnDirection: %i", turnDirection);
	DriverStationLCD::GetInstance()->UpdateLCD();
}

void TurnDegreesCommand::Execute()
{
	turnProgress = Robot::driveTrain->GetAngle();  // how far have we turned
	driveSpeed = ((_degreesToTurn - turnProgress) / _degreesToTurn) * decayFactor * maxSpeed;
	if (driveSpeed > 1.0) driveSpeed  = maxSpeed * turnDirection; // just in case, make sure it doesn't drive too fast
	if (driveSpeed < 0.20) driveSpeed = 0.20 * turnDirection;     // don't drive any slower than that or it doesn't move
	Robot::driveTrain->Drive(0.0, driveSpeed);
}

bool TurnDegreesCommand::IsFinished()
{
	// negative turnDirection cancels negative degree measurements
	if ((turnDirection * turnProgress) >= (turnDirection * _degreesToTurn)) 
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


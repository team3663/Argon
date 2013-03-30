#include "TurnDegreesCommand.h"
#include "math.h"

TurnDegreesCommand::TurnDegreesCommand(float degreesToTurn, float maxSpeed, float decay)
{
	Requires(Robot::driveTrain);
	SetTimeout(10.0);
	_degreesToTurn = degreesToTurn;
	turnProgress  = 0;    // how far we have turned so far
	driveSpeed    = 0;    // how quickly to drive while turning
	_maxSpeed      = maxSpeed;  // the fastest to drive while turning
	decayFactor   = decay;    // how quickly to slow down as approaching goal
	turnDirection = (_degreesToTurn < 0.0 ? -1 : 1);    // which direction we are rotating
}

void TurnDegreesCommand::Initialize()
{
	Robot::driveTrain->ResetGyro();
	WaitCommand(1.0).Run();
	// drive initially to start up a little gracefully
	//Robot::driveTrain->Drive(0.0, 0.4);   // with 0.0 for forward progress, this rotates in place
	// check whether we are turning clockwise or counter
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line6, "turnDirection: %i", turnDirection);
	DriverStationLCD::GetInstance()->UpdateLCD();
	
	Robot::driveTrain->Drive(0.0, 0.5 * turnDirection);
}

void TurnDegreesCommand::Execute()
{
	/*
	turnProgress = Robot::driveTrain->GetAngle();  // how far have we turned
	driveSpeed = ((_degreesToTurn - turnProgress) / _degreesToTurn) * decayFactor * _maxSpeed;
	if (driveSpeed > 1.0) driveSpeed  = _maxSpeed; // just in case, make sure it doesn't drive too fast
	if (driveSpeed < 0.20) driveSpeed = 0.20;     // don't drive any slower than that or it doesn't move
	Robot::driveTrain->Drive(0.0, driveSpeed * turnDirection);
	*/
	/*
	if (turnDirection == 1)
	{
		turnProgress = Robot::driveTrain->GetAngle();
		driveSpeed = ((_degreesToTurn - turnProgress) / _degreesToTurn) * decayFactor;
		if (driveSpeed > _maxSpeed) 
			driveSpeed = _maxSpeed;
		else if (driveSpeed < 0.3)
			driveSpeed = 0.3;
		
		Robot::driveTrain->Drive(0.0, driveSpeed * turnDirection);
	}
	else
	{
		turnProgress = Robot::driveTrain->GetAngle();
		driveSpeed = ((_degreesToTurn - turnProgress) / _degreesToTurn) * decayFactor;
		
		if (driveSpeed > _maxSpeed) 
			driveSpeed = _maxSpeed;
		else if (driveSpeed < 0.3)
			driveSpeed = 0.3;
		
		Robot::driveTrain->Drive(0.0, driveSpeed * turnDirection);
	}
	*/
}

bool TurnDegreesCommand::IsFinished()
{
	if (fabs(Robot::driveTrain->GetAngle()) >= fabs(_degreesToTurn) || IsTimedOut()) 
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


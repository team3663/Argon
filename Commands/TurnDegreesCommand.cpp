#include "TurnDegreesCommand.h"
#include "math.h"

TurnDegreesCommand::TurnDegreesCommand(float degreesToTurn, float turnSpeed)
{
	Requires(Robot::driveTrain);
	_degreesToTurn = degreesToTurn;
	_turnSpeed    = turnSpeed;  // the fastest to drive while turning
	//_turnProgress  = 0;           // how far we have turned so far
	// figure out which direction we are turning and set drive speed for that direction
	if (_degreesToTurn > 0)
		_turnSpeed = -turnSpeed;
}

void TurnDegreesCommand::Initialize()
{
	// we want gyro to start at 0 degrees
	Robot::driveTrain->ResetGyro();
	// wait long enough for it to reset
	WaitCommand(1.0).Run();
	// print out debug info to drive station
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line6, "turn speed: %i", _turnSpeed);
	DriverStationLCD::GetInstance()->UpdateLCD();
	// start turning - this will keep running until stopped
	// Drive 0.0 means don't go forward/backward - just turn in place
	Robot::driveTrain->Drive(0.0, _turnSpeed);
}

void TurnDegreesCommand::Execute()
{
	Robot::driveTrain->Drive(0.0, _turnSpeed);
}

bool TurnDegreesCommand::IsFinished()
{
	float turnProgress = Robot::driveTrain->GetAngle();
	SmartDashboard::PutNumber("Turn Progress", turnProgress);
	if ((_turnSpeed > 0) && (turnProgress >= _degreesToTurn)) 
		return false;
	else if ((_turnSpeed < 0) && (turnProgress <= _degreesToTurn))
		return false;
	else
		return true;
}

void TurnDegreesCommand::End()
{
	Robot::driveTrain->Stop();
}

void TurnDegreesCommand::Interrupted()
{
	End();
}


#include "VerticalTargetCommand.h"

VerticalTargetCommand::VerticalTargetCommand()
{
	Requires(Robot::pitch);
	done = false;
	SetTimeout(8.0);
}

VerticalTargetCommand::~VerticalTargetCommand()
{

}

void VerticalTargetCommand::Initialize()
{
	
}

void VerticalTargetCommand::Execute()
{
	if (Robot::targetting->Target())
	{
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Worked");
		DriverStationLCD::GetInstance()->UpdateLCD();
		double difference = Robot::targetting->GetNewestRect()->center_mass_y_normalized;
		if (difference > 0.0)
			Robot::pitch->IncreasePitch(difference * 5);
		else
			Robot::pitch->DecreasePitch(difference * -5);
		
		if (difference < 0.03 && difference > -0.03)
			done = true;
	}
	else
	{
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Failed");
		DriverStationLCD::GetInstance()->UpdateLCD();
		done = true;
	}
}

bool VerticalTargetCommand::IsFinished()
{
	return done || IsTimedOut();
}

void VerticalTargetCommand::End()
{

}

void VerticalTargetCommand::Interrupted()
{
	End();
}

#include "VerticalTargetCommand.h"

VerticalTargetCommand::VerticalTargetCommand()
{
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
		{
			//Robot::pitch->IncreasePitch(difference * 5);
			IncreasePitchCommand(difference * 5).Run();
		}
		else
		{
			//Robot::pitch->DecreasePitch(difference * -5);
			IncreasePitchCommand(difference * 5).Run();
		}
		
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

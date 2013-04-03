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
		// get the number of pixels off in y-axis from ideal target
		double difference = Robot::targetting->GetTargetRect()->center_mass_y_normalized;
		if (difference > 0.0)
		{
			// make sure this runs in sequence, not parallel
			IncreasePitchCommand(0.8, difference * 5).Run();
		}
		else
		{
			DecreasePitchCommand(-0.8, difference * -5).Run();
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

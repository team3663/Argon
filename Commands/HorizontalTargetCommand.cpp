#include "HorizontalTargetCommand.h"

HorizontalTargetCommand::HorizontalTargetCommand()
{
	Requires(Robot::driveTrain);
	SetTimeout(8.0);
	done = false;
}

HorizontalTargetCommand::~HorizontalTargetCommand()
{

}

void HorizontalTargetCommand::Initialize()
{
	if (Robot::targetting->Target())
		{
			DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Worked");
			DriverStationLCD::GetInstance()->UpdateLCD();
			double difference = Robot::targetting->GetNewestRect()->center_mass_x_normalized;
			float waitTime = difference * 5;
			if (difference > 0.0)
				Robot::driveTrain->Drive(0, 0.4);
			else
				Robot::driveTrain->Drive(0, -0.4);
			
			WaitCommand(waitTime).Run();
			
			if (difference < 0.06 && difference > -0.06)
				done = true;
			
			Robot::targetting->Target();
			float newDifference = Robot::targetting->GetNewestRect()->center_mass_x_normalized;
			if (newDifference > difference)
				constant = waitTime / (newDifference - difference);
			else
				constant = waitTime / (difference - newDifference);
		}
		else
		{
			DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Failed");
			DriverStationLCD::GetInstance()->UpdateLCD();
			done = true;
		}
}

void HorizontalTargetCommand::Execute()
{
	if (Robot::targetting->Target())
	{
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Worked");
		DriverStationLCD::GetInstance()->UpdateLCD();
		double difference = Robot::targetting->GetNewestRect()->center_mass_x_normalized;
		if (difference > 0.0)
			Robot::driveTrain->Drive(0, 0.4);
		else
			Robot::driveTrain->Drive(0, -0.4);
		
		WaitCommand(constant * difference).Run();
		
		if (difference < 0.06 && difference > -0.06)
			done = true;
	}
	else
	{
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Failed");
		DriverStationLCD::GetInstance()->UpdateLCD();
		done = true;
	}
}

bool HorizontalTargetCommand::IsFinished()
{
	return done || IsTimedOut();
}

void HorizontalTargetCommand::End()
{
	Robot::driveTrain->Stop();
}

void HorizontalTargetCommand::Interrupted()
{
	End();
}

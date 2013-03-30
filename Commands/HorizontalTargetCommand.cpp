#include "HorizontalTargetCommand.h"

#define TARGET_POINT 520
#define TOLERANCE 50

HorizontalTargetCommand::HorizontalTargetCommand()
{
	//Requires(Robot::driveTrain);
	SetTimeout(8.0);
	done = false;
}

HorizontalTargetCommand::~HorizontalTargetCommand()
{

}

void HorizontalTargetCommand::Initialize()
{
	/*
	if (Robot::targetting->Target())
		{
			DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Worked");
			DriverStationLCD::GetInstance()->UpdateLCD();
			double difference = Robot::targetting->GetTargetRect()->center_mass_x_normalized;
			float waitTime = difference * 5;
			if (difference > 0.0)
				Robot::driveTrain->Drive(0, 0.4);
			else
				Robot::driveTrain->Drive(0, -0.4);
			
			WaitCommand(waitTime).Run();
			
			if (difference < 0.06 && difference > -0.06)
				done = true;
			
			Robot::targetting->Target();
			float newDifference = Robot::targetting->GetTargetRect()->center_mass_x_normalized;
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
		*/
	if(!Robot::targetting->Target())
	{
		done = true;
	}
}

void HorizontalTargetCommand::Execute()
{/*
	if (Robot::targetting->Target())
	{
		DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line5, "Targetting Worked");
		DriverStationLCD::GetInstance()->UpdateLCD();
		double difference = Robot::targetting->GetTargetRect()->center_mass_x_normalized;
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
	*/
	ParticleAnalysisReport* rect = Robot::targetting->GetTargetRect();
	if (rect != NULL && done == false)
	{
		float distance = Robot::targetting->CalcDistance(rect);
		float difference = abs(TARGET_POINT - rect->center_mass_x);
		float degreesToTurn = (TARGET_POINT - rect->center_mass_x) * 67 / 640;
		//float degreesToTurn = difference / (3.14 * 2 * distance) * 100 / 360; // find percentage of circle we have to travel then convert to degrees
		TurnDegreesCommand(degreesToTurn, 0.5, 5).Run();
	}
}

bool HorizontalTargetCommand::IsFinished()
{
	if (Robot::targetting->Target())
	{
		ParticleAnalysisReport* rect = Robot::targetting->GetTargetRect();
		return IsTimedOut() || (rect->center_mass_x < TARGET_POINT + TOLERANCE && rect->center_mass_x > TARGET_POINT - TOLERANCE);
	}
	else
		return true;
}

void HorizontalTargetCommand::End()
{
	Robot::driveTrain->Stop();
}

void HorizontalTargetCommand::Interrupted()
{
	End();
}

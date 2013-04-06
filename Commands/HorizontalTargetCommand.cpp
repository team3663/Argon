#include "HorizontalTargetCommand.h"

// these need to be replaced. It should look up the center of the target rectangle from wherever we record which target we are aiming for.
// For now, it just aims for the three point target
#define TARGET_POINT 400   // 400 pixels on the screen where 0,0 is top-left
#define TOLERANCE 5        // can be five pixels off either way and still fine, but that is a guess

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
	// Target gets the image, analyzes it for rectangles, and stores info on all of them
	if(!Robot::targetting->Target())
	{
		// if it fails to get an image for targeting, we are done
		SmartDashboard::PutString("Horiz. Targetting State", "No Image Found");
		done = true;
	}
}

void HorizontalTargetCommand::Execute()
{
	// This step gets the info on rectangles and selects the one we want to target based on menu on SmartDashboard
	ParticleAnalysisReport* rect = Robot::targetting->GetTargetRect();
	if (rect != NULL && done == false)
	{
//		float distance = Robot::targetting->CalcDistance(rect);
//		int difference = abs(TARGET_POINT - rect->center_mass_x);
		// camera sees 67 degrees of width and image is 640 pixels wide
		float degreesToTurn = (TARGET_POINT - rect->center_mass_x) * 67 / 640;
		// make sure this command runs in series, not parallel
		SmartDashboard::PutString("Horiz. Targetting State", "Turning");
		SmartDashboard::PutNumber("Horiz. Targetting Degrees", degreesToTurn);
		TurnDegreesCommand command(degreesToTurn, 0.5);
		while(!command.Run()) {} // TODO find out if this is the right way to run commands within commands
	}
}

bool HorizontalTargetCommand::IsFinished()
{
	if (Robot::targetting->Target())
	{
		ParticleAnalysisReport* rect = Robot::targetting->GetTargetRect();
//		return IsTimedOut() || rect == NULL || (rect->center_mass_x < TARGET_POINT + TOLERANCE && rect->center_mass_x > TARGET_POINT - TOLERANCE);
		if (IsTimedOut())
		{
			SmartDashboard::PutString("Horiz. Targetting State", "Timed Out");
			return true;
		}
		if (rect == NULL)
		{
			SmartDashboard::PutString("Horiz. Targetting State", "Rect Not Found");
			return true;
		}
		if (rect->center_mass_x < TARGET_POINT + TOLERANCE && rect->center_mass_x > TARGET_POINT - TOLERANCE)
		{
			SmartDashboard::PutString("Horiz. Targetting State", "On Target");
			return true;
		}
		return false;
	}
	else
	{
		SmartDashboard::PutString("Horiz. Targetting State", "No Image Found");
		return true;
	}
}

void HorizontalTargetCommand::End()
{
	Robot::driveTrain->Stop();
}

void HorizontalTargetCommand::Interrupted()
{
	End();
}

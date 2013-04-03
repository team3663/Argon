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
	// Target gets the image, analyzes it for rectangles, and stores info on all of them
	if(!Robot::targetting->Target())
	{
		// if it fails to get an image for targeting, we are done
		done = true;
	}
}

void HorizontalTargetCommand::Execute()
{
	// This step gets the info on rectangles and selects the one we want to target based on menu on SmartDashboard
	ParticleAnalysisReport* rect = Robot::targetting->GetTargetRect();
	if (rect != NULL && done == false)
	{
		float distance = Robot::targetting->CalcDistance(rect);
		int difference = abs(TARGET_POINT - rect->center_mass_x);
		// camera sees 67 degrees of width and image is 640 pixels wide
		float degreesToTurn = (TARGET_POINT - rect->center_mass_x) * 67 / 640;
		// make sure this command runs in series, not parallel
		TurnDegreesCommand(degreesToTurn, 0.5).Run();
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

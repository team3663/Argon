#include "VerticalTargetCommand.h"
#include "math.h"

// This currently only aims for the three point target
#define TARGET_CENTER  100   // center x pixel of the three point target where 0,0 is top-left of the image
#define TOLERANCE        2   // number of pixels to allow the target to be off and still accept as centered

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
	if (!Robot::targetting->Target())
	{
		done = true;
	}
}

void VerticalTargetCommand::Execute()
{
	ParticleAnalysisReport* rect = Robot::targetting->GetTargetRect();
	if (rect != NULL && done == false)
	{
		float degreesToMove; // = (targetPoint - rect->center_mass_y) / 480 * degreesOfVision;
		float timeToRun = 1 / (degreesPerSecond / degreesToMove);
		int runDirection = timeToRun > 0.0 ? 1 : -1;
		
		//SmartDashboard::PutString("Vertical Targetting Status", timeToRun);
		ChangePitchCommand command(0.8 * runDirection, fabs(timeToRun));
		while(!command.Run()) {} // TODO find out if this is the right way to run commands within commands
	}
	else
	{
		done = true;
	}
}

bool VerticalTargetCommand::IsFinished()
{
	if (Robot::targetting->Target())
	{
		return IsTimedOut() || done; 
	}
	else
		return true;
}

void VerticalTargetCommand::End()
{

}

void VerticalTargetCommand::Interrupted()
{
	End();
}

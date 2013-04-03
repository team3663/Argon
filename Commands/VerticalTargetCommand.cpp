#include "VerticalTargetCommand.h"

// This currently only aims for the three point target
#define TARGET_CENTER  200   // center x pixel of the three point target where 0,0 is top-left of the image
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
	
}

void VerticalTargetCommand::Execute()
{
	if (Robot::targetting->Target())
	{
		// get the number of pixels off in y-axis from ideal target
		// UPDATE THIS TO USE PIXELS WITH 0,0 AT TOP_LEFT OF IMAGE
		float difference = Robot::targetting->GetTargetRect()->center_mass_y_normalized;
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

#include "AutonomousFinishedCommand.h"

AutonomousFinishedCommand::AutonomousFinishedCommand()
{

}

AutonomousFinishedCommand::~AutonomousFinishedCommand()
{

}

void AutonomousFinishedCommand::Initialize()
{
	Robot::autonomousFinished = true;
}

void AutonomousFinishedCommand::Execute()
{

}

bool AutonomousFinishedCommand::IsFinished()
{
	return true;
}

void AutonomousFinishedCommand::End()
{

}

void AutonomousFinishedCommand::Interrupted()
{

}

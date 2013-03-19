#include "TargettingCommand.h"

TargettingCommand::TargettingCommand()
{

}

TargettingCommand::~TargettingCommand()
{

}

void TargettingCommand::Initialize()
{
	Robot::targetting->Target();
}

void TargettingCommand::Execute()
{

}

bool TargettingCommand::IsFinished()
{
	return true;
}

void TargettingCommand::End()
{

}

void TargettingCommand::Interrupted()
{

}

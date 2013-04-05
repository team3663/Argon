// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "AutonomousCommand.h"
AutonomousCommand::AutonomousCommand() {
	//Turns on shooter motor
	AddSequential(new SetShootSpeedCommand(0.9));
	// set riser to top while spinning up
	AddSequential(new IncreasePitchCommand(1.0, 6.0));
	//wait to allow full wheel spin up
//	AddSequential(new WaitCommand(1.5));
	// shift to low for stability
	AddSequential(new GearShiftDown()); 
	//shoot three frisbees
	for (int i = 0; i < 3; i++)
	{
		AddSequential(new ShootPistonCommand());
		AddSequential(new WaitCommand(0.8));
	}
	// In case a frisbee got stuck
	AddSequential(new NudgeFlipperCommand()); 
	AddSequential(new WaitCommand(0.3));
	AddSequential(new ShootPistonCommand());
	//drive forward to get clear of pyramid
	AddSequential(new DriveTestCommand());
	AddSequential(new WaitCommand(0.5));
	//AddSequential(new EncoderDriveCommand(12, 0.8, 1));
	//turn to left to face feeder
	AddSequential(new TurnDegreesCommand(90, 0.6));
	//lower pitch to approximate feeder shooting
	AddParallel(new DecreasePitchCommand(-0.6));
	/*
	AddSequential(new DriveToPointCommand(12, 0.4, 0));
	AddSequential(new WaitCommand(0.25));
	AddSequential(new TurnDegreesCommand(90, 0.6));
	AddSequential(new AutonomousFinishedCommand());
	AddSequential(new DriveToLineCommand(84, 0.6, 3));
	*/
}
// Called just before this Command runs the first time
void AutonomousCommand::Initialize() {

}
// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
	
}
// Make this return true when this Command no longer needs to run execute()
bool AutonomousCommand::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void AutonomousCommand::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousCommand::Interrupted() {
}

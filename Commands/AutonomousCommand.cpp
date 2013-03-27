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
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	AddSequential(new SpinUpCommand());
	AddSequential(new WaitCommand(3.0));
	for (int i = 0; i < 3; i++)
	{
		AddSequential(new ShootPistonCommand());
		AddSequential(new WaitCommand(0.5));
	}
	AddSequential(new SetShootSpeedCommand(0.9));
	AddSequential(new SpinDownCommand());
	AddSequential(new TurnDegreesCommand(-25, 0.6, 3));
	AddSequential(new DriveToPointCommand(12, false));
	AddSequential(new WaitCommand(0.25));
	AddSequential(new TurnDegreesCommand(90, 0.6, 3));
}
// Called just before this Command runs the first time
void AutonomousCommand::Initialize() {
	/*
	 * turn 60 degrees (DriveTrain->Drive(0,0.3)
	 * Spin up shooter (spinup command)
	 * Fire 5 times (shoot command x5)
	 * Spin down shooter
	 * adjust pitch (all the way up, then down for predetermined time)
	 * turn -30 degrees (Drivetrain->Drive)
	 * drive 10ft to wall
	 * turn 90 degrees
	 * drive until white line
	 */
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

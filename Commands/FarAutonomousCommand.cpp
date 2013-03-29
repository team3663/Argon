#include "FarAutonomousCommand.h"

FarAutonomousCommand::FarAutonomousCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	AddSequential(new SetShootSpeedCommand(0.9));
	AddSequential(new IncreasePitchCommand(6.0)); // set riser to top while spinning up
	AddSequential(new WaitCommand(1.5));
	AddSequential(new GearShiftUp());
	for (int i = 0; i < 3; i++)
	{
		AddSequential(new ShootPistonCommand());
		AddSequential(new WaitCommand(0.5));
	}
	AddSequential(new NudgeFlipperCommand()); // In case a frisbee got stuck
	AddSequential(new WaitCommand(0.2));
	AddSequential(new ShootPistonCommand());
	AddParallel(new SpinDownCommand());
	AddSequential(new TurnDegreesCommand(70, 0.6, 3));
	AddSequential(new EncoderDriveToCommand(36));
	AddSequential(new WaitCommand(0.25));
	AddSequential(new TurnDegreesCommand(-90, 0.6, 3));
	AddSequential(new DriveToPointCommand(12.0, 0.6, 1));
	AddSequential(new TurnDegreesCommand(90, 0.6, 3));
}
// Called just before this Command runs the first time
void FarAutonomousCommand::Initialize() {
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
void FarAutonomousCommand::Execute() {
	
}
// Make this return true when this Command no longer needs to run execute()
bool FarAutonomousCommand::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void FarAutonomousCommand::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FarAutonomousCommand::Interrupted() {
}
#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AdjustShootSpeedCommand.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/CheckCompressorSwitch.h"
#include "Commands/CheckForLinesCommand.h"
#include "Commands/ClimbDownCommand.h"
#include "Commands/ClimbUpCommand.h"
#include "Commands/DecreasePitchCommand.h"
#include "Commands/DriveCommand.h"
#include "Commands/DriveToPointCommand.h"
#include "Commands/EncoderDriveToCommand.h"
#include "Commands/FlipperCommand.h"
#include "Commands/NudgeFlipperCommand.h"
#include "Commands/GearShiftCommand.h"
#include "Commands/GearShiftDown.h"
#include "Commands/GearShiftUp.h"
#include "Commands/HorizontalTargetCommand.h"
#include "Commands/VerticalTargetCommand.h"
#include "Commands/IncreasePitchCommand.h"
#include "Commands/ShootPistonCommand.h"
#include "Commands/SpinCommand.h"
#include "Commands/SpinDownCommand.h"
#include "Commands/SpinUpCommand.h"
#include "Commands/TargettingCommand.h"
#include "Commands/TurnDegreesCommand.h"
#include "Commands/TurnLeftCommand.h"
#include "Commands/TurnRightCommand.h"
#include "Commands/ResetGyroCommand.h"
#include "Commands/PIDDriveCommand.h"
#include "Commands/EncoderDriveToCommand.h"
#include "Commands/TurnDegreesCommand.h"
//#include "Commands/VerticalTargetCommand.h"

OI::OI() {
	// Process operator interface input here.

	driveJoystick = new Joystick(1);
	
	targetButton = new JoystickButton(driveJoystick, 1);
	targetButton->WhenPressed(new TargettingCommand());
	
	gearShift = new JoystickButton(driveJoystick, 3);
	gearShift->WhenPressed(new GearShiftUp());
	
	resetGyro = new JoystickButton(driveJoystick, 2);
	resetGyro->WhenPressed(new GearShiftDown());
	
	climbDown = new JoystickButton(driveJoystick, 10);
	climbDown->WhileHeld(new ClimbDownCommand());
	
	climbUp = new JoystickButton(driveJoystick, 11);
	climbUp->WhileHeld(new ClimbUpCommand());
	
	htarget = new JoystickButton(driveJoystick, 8);
	htarget->WhenPressed(new HorizontalTargetCommand());
	
	//vtarget = new JoystickButton(driveJoystick, 9);
	//vtarget->WhenPressed(new VerticalTargetCommand());
	///////////////////////////////////////////////////////////////////
	
	targetJoystick = new Joystick(2);
	
	turnLeft = new JoystickButton(targetJoystick, 5);
	turnLeft->WhileHeld(new TurnLeftCommand());
	
	turnRight = new JoystickButton(targetJoystick, 4);
	turnRight->WhileHeld(new TurnRightCommand());
	
	changeShooter = new JoystickButton(targetJoystick, 11);
	changeShooter->WhenPressed(new SpinCommand());
	
	flipFrisbees = new JoystickButton(targetJoystick, 6);
	flipFrisbees->WhenPressed(new FlipperCommand());
	
	nudgeFrisbees = new JoystickButton(targetJoystick, 7);
	nudgeFrisbees->WhenPressed(new NudgeFlipperCommand());
	
	decreasePitch = new JoystickButton(targetJoystick, 2);
	decreasePitch->WhileHeld(new DecreasePitchCommand(-0.5));
	
	increasePitch = new JoystickButton(targetJoystick, 3);
	increasePitch->WhileHeld(new IncreasePitchCommand(0.5));
	
	shootPiston = new JoystickButton(targetJoystick, 1);
	shootPiston->WhenPressed(new ShootPistonCommand());
	
	decreaseShootSpeed = new JoystickButton(targetJoystick, 8);
	decreaseShootSpeed->WhenPressed(new AdjustShootSpeedCommand(-0.025));
	
	increaseShootSpeed = new JoystickButton(targetJoystick, 9);
	increaseShootSpeed->WhenPressed(new AdjustShootSpeedCommand(0.025));
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Turn 90", new TurnDegreesCommand(90, 0.6));
	SmartDashboard::PutData("Turn -90", new TurnDegreesCommand(-90, 0.6));
	SmartDashboard::PutData("Drive With Encoder", new EncoderDriveToCommand(60));
	SmartDashboard::PutData("Drive To Line", new DriveToLineCommand(48, 0.6, 3));
	SmartDashboard::PutData("Drive To Point", new DriveToPointCommand(12, 0.4, 0));
	SmartDashboard::PutData("Horizontal Target", new HorizontalTargetCommand());
	SmartDashboard::PutData("Vertical Target", new VerticalTargetCommand());
}

Joystick* OI::getDriveJoystick() {
	return driveJoystick;
}
Joystick* OI::getTargetJoystick() {
	return targetJoystick;
}
float OI::GetX()
{
	return driveJoystick->GetX();
}
float OI::GetY()
{
	return driveJoystick->GetY();
}

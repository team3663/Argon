// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Shooter.h"
#include "../Robotmap.h"
Shooter::Shooter() : Subsystem("Shooter") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	shooterMotorControl = RobotMap::shooterShooterMotorControl;
	shooterEncoder = RobotMap::shooterShooterEncoder;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	_shootSpeed = 0.9;
	_isShooting = false;
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void Shooter::SetMotorSpeed(){
	shooterMotorControl->Set(-_shootSpeed);
	_isShooting = true;
}
float Shooter::GetMotorSpeed(){
	return _shootSpeed;
}
void Shooter::SetMotorSpeed(float speed){
	_shootSpeed = speed;
	if(_shootSpeed > 1){
		_shootSpeed = 1;
	}
	else if(_shootSpeed < -1){
		_shootSpeed = -1;
	}
	shooterMotorControl->Set(-_shootSpeed);
	_isShooting = true;
}
void Shooter::ChangeMotorSpeed(float changeAmount){
	SetMotorSpeed(_shootSpeed + changeAmount);
}
/*void Shooter::SpinUp(){
	RobotMap::shooterShooterMotorControl->Set(-1.0);
}*/
void Shooter::Stop(){
	RobotMap::shooterShooterMotorControl->Set(0.0);
	_isShooting = false;
}
bool Shooter::GetShooterState(){
	return _isShooting;
}
void Shooter::UpdateStatus(){
	SmartDashboard::PutNumber("Shoot Setting: ", _shootSpeed * 100);
	SmartDashboard::PutNumber("Shoot Rate: ", shooterEncoder->GetRate()/1440);
}

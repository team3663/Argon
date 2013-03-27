// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Photoelectric.h"
#include "../Robotmap.h"
Photoelectric::Photoelectric() : Subsystem("Photoelectric") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	lightSensor = RobotMap::photoelectricLightSensor;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}	
   
void Photoelectric::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
unsigned int Photoelectric::GetCurrentStatus(){
	return lightSensor->Get();
	
}
void Photoelectric::UpdateStatus(){
	SmartDashboard::PutNumber("Current voltage PE: ", Photoelectric::GetCurrentStatus());
	DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line3, "PhotoElectric: %f", Photoelectric::GetCurrentStatus());
	DriverStationLCD::GetInstance()->UpdateLCD();
}

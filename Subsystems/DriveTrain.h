// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../PIDDrive.h"
#include "../PIDUltrasonic.h"
#include "PIDController.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrain: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	bool highGear;
	float encodeRightPrevious;
	float encodeLeftPrevious;
	
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	SpeedController* speedControlLeft1;
	SpeedController* speedControlLeft2;
	SpeedController* speedControlRight1;
	SpeedController* speedControlRight2;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Gyro* gyro;
	RobotDrive* robotDrive3663;
	Solenoid* gearShift1;
	Solenoid* gearShift2;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	DriveTrain();
	void InitDefaultCommand();
	void Arcade();
	void GearShift(bool shift);
	void Drive(float speed, float curve);
	void Stop();
	float GetAngle();
	void ResetGyro();
	bool GetGearState();
	float GetLeftDistance();
	float GetRightDistance();
	void DriveEncoderReset();
	void UpdateStatus();
};
#endif
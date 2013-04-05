// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
SpeedController* RobotMap::driveTrainSpeedControlLeft1 = NULL;
SpeedController* RobotMap::driveTrainSpeedControlLeft2 = NULL;
SpeedController* RobotMap::driveTrainSpeedControlRight1 = NULL;
SpeedController* RobotMap::driveTrainSpeedControlRight2 = NULL;
Encoder* RobotMap::driveTrainLeftEncoder = NULL;
Encoder* RobotMap::driveTrainRightEncoder = NULL;
RobotDrive* RobotMap::driveTrainRobotDrive3663 = NULL;
Solenoid* RobotMap::driveTrainGearShift1 = NULL;
Solenoid* RobotMap::driveTrainGearShift2 = NULL;
SpeedController* RobotMap::shooterShooterMotorControl = NULL;
Encoder* RobotMap::shooterShooterEncoder = NULL;
Solenoid* RobotMap::diskManagementShootSolenoid1 = NULL;
Solenoid* RobotMap::diskManagementShootSolenoid2 = NULL;
Solenoid* RobotMap::diskManagementflipperSolenoid1 = NULL;
Solenoid* RobotMap::diskManagementFlipperSolenoid2 = NULL;
Gyro* RobotMap::driveTrainGyro = NULL;
SpeedController* RobotMap::pitchPitchMotor = NULL;
DigitalInput* RobotMap::pitchLimitSwitchMax = NULL;
DigitalInput* RobotMap::pitchLimitSwitchMin = NULL;
Relay* RobotMap::pneumaticsCompressorSwitch = NULL;
DigitalInput* RobotMap::pneumaticsCompressorLimitSwitch = NULL;
DigitalInput* RobotMap::photoelectricGroundSensor = NULL;
DigitalInput* RobotMap::photoelectricShooterSensor = NULL;
SpeedController* RobotMap::climberClimbMotorController = NULL;
DigitalInput* RobotMap::climberUpperLimitSwitch = NULL;
DigitalInput* RobotMap::climberLowerLimitSwitch = NULL;
Relay* RobotMap::lightsledRelay = NULL;
AnalogChannel* RobotMap::rangeFinderFrontUltrasonicSensor = NULL;
AnalogChannel* RobotMap::rangeFinderBackUltrasonicSensor = NULL;
AnalogChannel* RobotMap::rangeFinderLeftUltrasonicSensor = NULL;
AnalogChannel* RobotMap::rangeFinderRightUltrasonicSensor = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	driveTrainSpeedControlLeft1 = new Victor(1, 5);
	lw->AddActuator("DriveTrain", "SpeedControlLeft1", dynamic_cast<Victor*>(driveTrainSpeedControlLeft1));//(Victor*) driveTrainSpeedControlLeft1);
	
	driveTrainSpeedControlLeft2 = new Victor(1, 3);
	lw->AddActuator("DriveTrain", "SpeedControlLeft2", dynamic_cast<Victor*>(driveTrainSpeedControlLeft2));
	
	driveTrainSpeedControlRight1 = new Victor(1, 2);
	lw->AddActuator("DriveTrain", "SpeedControlRight1", dynamic_cast<Victor*>(driveTrainSpeedControlRight1));
	
	driveTrainSpeedControlRight2 = new Victor(1, 4);
	lw->AddActuator("DriveTrain", "SpeedControlRight2", dynamic_cast<Victor*>(driveTrainSpeedControlRight2));
	
	driveTrainRobotDrive3663 = new RobotDrive(driveTrainSpeedControlLeft2, driveTrainSpeedControlLeft1,
              driveTrainSpeedControlRight2, driveTrainSpeedControlRight1);
	
	driveTrainRobotDrive3663->SetSafetyEnabled(false);
        driveTrainRobotDrive3663->SetExpiration(0.1);
        driveTrainRobotDrive3663->SetSensitivity(0.5);
        driveTrainRobotDrive3663->SetMaxOutput(1.0);
        
    driveTrainLeftEncoder = new Encoder(1, 10, 1, 11, false, Encoder::k4X);
	lw->AddSensor("DriveTrain", "LeftEncoder", driveTrainLeftEncoder);
	driveTrainLeftEncoder->SetDistancePerPulse(1.0);
	
		driveTrainLeftEncoder->SetPIDSourceParameter(Encoder::kRate);
		driveTrainLeftEncoder->Start();
		
	driveTrainRightEncoder = new Encoder(1, 8, 1, 9, true, Encoder::k4X);
	lw->AddSensor("DriveTrain", "RightEncoder", driveTrainRightEncoder);
	driveTrainRightEncoder->SetDistancePerPulse(1.0);
	
		driveTrainRightEncoder->SetPIDSourceParameter(Encoder::kRate);
		driveTrainRightEncoder->Start();
		
	driveTrainGearShift1 = new Solenoid(1, 3);
	lw->AddActuator("DriveTrain", "GearShift1", driveTrainGearShift1);
	
	driveTrainGearShift2 = new Solenoid(1, 4);
	lw->AddActuator("DriveTrain", "GearShift2", driveTrainGearShift2);
	
	shooterShooterMotorControl = new Victor(1, 1);
	lw->AddActuator("Shooter", "ShooterMotorControl", (Victor*) shooterShooterMotorControl);
	
	shooterShooterEncoder = new Encoder(1, 12, 1, 13, true, Encoder::k4X);
	lw->AddSensor("Shooter", "ShooterEncoder", shooterShooterEncoder);
	shooterShooterEncoder->SetDistancePerPulse(1.0);
	
        shooterShooterEncoder->SetPIDSourceParameter(Encoder::kRate);
        shooterShooterEncoder->Start();
        
	diskManagementShootSolenoid1 = new Solenoid(1, 1);
	lw->AddActuator("DiskManagement", "ShootSolenoid1", diskManagementShootSolenoid1);
	
	diskManagementShootSolenoid2 = new Solenoid(1, 2);
	lw->AddActuator("DiskManagement", "ShootSolenoid2", diskManagementShootSolenoid2);
	
	diskManagementflipperSolenoid1 = new Solenoid(1, 5);
	lw->AddActuator("DiskManagement", "flipperSolenoid1", diskManagementflipperSolenoid1);
	
	diskManagementFlipperSolenoid2 = new Solenoid(1, 6);
	lw->AddActuator("DiskManagement", "FlipperSolenoid2", diskManagementFlipperSolenoid2);
	
	pitchPitchMotor = new Talon(1, 7);
	lw->AddActuator("Pitch", "PitchMotor", (Talon*) pitchPitchMotor);
	
	pitchLimitSwitchMax = new DigitalInput(1, 7);
	lw->AddSensor("Pitch", "LimitSwitchMax ", pitchLimitSwitchMax);
	
	pitchLimitSwitchMin = new DigitalInput(1, 6);
	lw->AddSensor("Pitch", "LimitSwitchMin", pitchLimitSwitchMin);
	
	pneumaticsCompressorSwitch = new Relay(1, 1);
	lw->AddActuator("Pneumatics", "CompressorSwitch", pneumaticsCompressorSwitch);
	
	pneumaticsCompressorLimitSwitch = new DigitalInput(1, 5);
	lw->AddSensor("Pneumatics", "CompressorLimitSwitch", pneumaticsCompressorLimitSwitch);
	
	photoelectricGroundSensor = new DigitalInput(1, 14);
	lw->AddSensor("Photoelectric", "GroundSensor", photoelectricGroundSensor);
	
	photoelectricShooterSensor = new DigitalInput(1, 1);
	lw->AddSensor("DiskManagement", "ShooterLightSensor", photoelectricShooterSensor);
	
	climberClimbMotorController = new Victor(1, 8);
	lw->AddActuator("Climber", "ClimbMotorController", (Victor*) climberClimbMotorController);
	
	climberUpperLimitSwitch = new DigitalInput(1, 3);
	lw->AddSensor("Climber", "UpperLimitSwitch", climberUpperLimitSwitch);
	
	climberLowerLimitSwitch = new DigitalInput(1, 4);
	lw->AddSensor("Climber", "LowerLimitSwitch", climberLowerLimitSwitch);
	
	lightsledRelay = new Relay(1, 2);
	lw->AddActuator("Lights", "ledRelay", lightsledRelay);
	
	rangeFinderFrontUltrasonicSensor = new AnalogChannel(1, 5);
	lw->AddSensor("RangeFinder", "FrontUltrasonicSensor", rangeFinderFrontUltrasonicSensor);
	
	rangeFinderBackUltrasonicSensor = new AnalogChannel(1, 7);
	lw->AddSensor("RangeFinder", "BackUltrasonicSensor", rangeFinderBackUltrasonicSensor);
	
	rangeFinderLeftUltrasonicSensor = new AnalogChannel(1, 4);
	lw->AddSensor("RangeFinder", "LeftUltrasonicSensor", rangeFinderLeftUltrasonicSensor);
	
	rangeFinderRightUltrasonicSensor = new AnalogChannel(1, 6);
	lw->AddSensor("RangeFinder", "RightUltrasonicSensor", rangeFinderRightUltrasonicSensor);

	driveTrainGyro = new Gyro(1, 1);
	lw->AddSensor("DriveTrain", "Gyro", driveTrainGyro);

		driveTrainGyro->SetSensitivity(Gyro::kDefaultVoltsPerDegreePerSecond);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

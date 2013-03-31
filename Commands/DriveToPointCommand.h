// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef DRIVETOPOINTCOMMAND_H
#define DRIVETOPOINTCOMMAND_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @JWIEDERSPAN Jon Wiederspan
 */
class DriveToPointCommand: public Command {
private:
	float targetDistance;
	float maxSpeed;
	int   frontSonic;
	double currDistance; // array of ultrasonic values [front,back,left,right]
	float driveSpeed;
	float distanceToDrive;
	float curve;
	float driveProgress;
	float decayFactor;
	bool  reachedEndpoint;
	//double currDistance[4];
public:
	DriveToPointCommand(float targetDistance, float maxSpeed, int frontSonic);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

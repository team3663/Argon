/*
#ifndef ENCODERDRIVECOMMAND_H
#define ENCODERDRIVECOMMAND_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class EncoderDriveCommand: public Command {
private:
	float distanceToDrive;
	float maxSpeed;
	float decayFactor;
	float driveSpeed;
	float curve;
	float driveProgress;
	bool reachedEndpoint;
	int driveDirection;
public:
	EncoderDriveCommand(float distanceToDrive, float maxSpeed, float decayFactor);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
*/

#ifndef ENCODERDRIVECOMMAND_H
#define ENCODERDRIVECOMMAND_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class EncoderDriveCommand: public Command {
private:
	float destination;
	float driveSpeed;
	float curve;
	float driveProgress;
	int driveDirection;
	bool finished;
public:
	EncoderDriveCommand(float finishPoint);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

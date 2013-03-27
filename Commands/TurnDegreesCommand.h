#ifndef TURNDEGREESCOMMAND_H
#define TURNDEGREESCOMMAND_H

#include "../Robot.h"
#include "WPIlib.h"
#include "../Subsystems/DriveTrain.h"

class TurnDegreesCommand: public Command
{
private:
	float _degreesToTurn;
	float turnProgress;
	float driveSpeed;
	float _maxSpeed;
	float decayFactor;
	int   turnDirection;
public:
	TurnDegreesCommand(float degreesToTurn, float maxSpeed, float decay);
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

#ifndef TURNDEGREESCOMMAND_H
#define TURNDEGREESCOMMAND_H

#include "../Robot.h"
#include "WPIlib.h"
#include "../Subsystems/DriveTrain.h"

class TurnDegreesCommand: public Command
{
private:
	float _degreesToTurn;
	float _turnSpeed;
public:
	TurnDegreesCommand(float degreesToTurn, float turnSpeed = 0.5);
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

#ifndef TURNDEGREESCOMMAND_H
#define TURNDEGREESCOMMAND_H

#include "../Robot.h"
#include "WPIlib.h"
#include "../Subsystems/DriveTrain.h"

class TurnDegreesCommand: public Command
{
private:
	float _currAngle;
	float _distanceToNewAngle;
	float _newAngle;
public:
	TurnDegreesCommand();
protected:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

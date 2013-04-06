
#ifndef CHANGEPITCHCOMMAND_H
#define CHANGEPITCHCOMMAND_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class ChangePitchCommand: public Command {
private:
	const float _timeout;
	float _changeRate;
public:
	ChangePitchCommand(float changeRate, float timeout = -1.0);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

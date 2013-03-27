#ifndef FAR_AUTONOMOUS_COMMAND_H
#define FAR_AUTONOMOUS_COMMAND_H


#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "TurnDegreesCommand.h"
#include "EncoderDriveToCommand.h"
#include "DriveToPointCommand.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class FarAutonomousCommand: public CommandGroup {
public:
	FarAutonomousCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

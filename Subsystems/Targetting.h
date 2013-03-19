#ifndef TARGETTING_H
#define TARGETTING_H

#include "Commands/Subsystem.h"
#include "Relay.h"
#include "Vision/AxisCamera.h"

class Targetting: public Subsystem
{
private:
	AxisCamera& _camera;
public:
	Targetting();
	~Targetting();
	void Target();
};

#endif

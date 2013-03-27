#ifndef TARGETTING_H
#define TARGETTING_H

#include "Commands/Subsystem.h"
#include "Relay.h"
#include "Vision/AxisCamera.h"

class Targetting: public Subsystem
{
private:
	AxisCamera& _camera;
	vector<ParticleAnalysisReport> *newestData;
public:
	ParticleAnalysisReport* GetNewestRect();
	Targetting();
	~Targetting();
	bool Target();
	
};

#endif

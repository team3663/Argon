#ifndef TARGETTING_H
#define TARGETTING_H

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "Relay.h"
#include "Vision/AxisCamera.h"

class Targetting: public Subsystem
{
private:
	AxisCamera& _camera;
	vector<ParticleAnalysisReport> *newestData;
	ParticleAnalysisReport* FindRectWithRatio(float targetRatio, float tolerance);
public:
	ParticleAnalysisReport* GetTargetRect();
	ParticleAnalysisReport* GetThreePointRect();
	ParticleAnalysisReport* GetTwoPointRect();
	float CalcDistance(ParticleAnalysisReport* rect);
	void WriteCurrentData();
	Targetting();
	~Targetting();
	bool Target();
	
};

#endif

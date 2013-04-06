#include "Targetting.h"
#include "Vision/RGBImage.h"
#include "DriverStationLCD.h"
#include <fstream>

#define DISTANCE_RATIO 2.2
#define CONSTANT 20

Targetting::Targetting(): Subsystem("Targetting"), _camera(AxisCamera::GetInstance("10.36.63.11"))
{
	newestData = NULL;
}

Targetting::~Targetting()
{
	newestData->clear();
	delete (newestData);
}

void Targetting::WriteCurrentData()
{
	ofstream file("/processingData.txt", ios::out | ios::app);
	if (!file.is_open())
		return;
	
	file << "Shot Number: " << Robot::diskManagement->GetShotNum() << "\n";
	
	Target();
	ParticleAnalysisReport* currRect = GetTargetRect();
	file << "Num of Rects: " << newestData->size() << "\n";
	if (currRect == NULL)
	{
		file << "Target Not Found \n";
	}
	else
	{
		file << "Rect X center: " << currRect->center_mass_x << "\n";
		file << "Rect Y center: " << currRect->center_mass_y << "\n";
		file << "Rect width: " << currRect->boundingRect.width << "\n";
		file << "Rect height: " << currRect->boundingRect.height << "\n";
	}
	file << "Time Since Last Shot: " << Robot::diskManagement->GetTimeSinceLastShot() << "\n";
	file << "Battery Voltage: " << DriverStation::GetInstance()->GetBatteryVoltage() << "\n";
	file << "Shoot Speed: " << Robot::shooter->GetMotorSpeed() << "\n \n";
	
	file.close();
}

ParticleAnalysisReport* Targetting::FindRectWithRatio(float targetRatio, float tolerance)
{
	for (unsigned int i = 0; i < newestData->size(); i++)
	{
		ParticleAnalysisReport* currRect = &newestData->at(i);
		float ratio = currRect->boundingRect.width / currRect->boundingRect.height;
		if (ratio < (targetRatio + tolerance) && ratio > (targetRatio - tolerance))
		{
			return currRect;
		}
	}
	return NULL;
}

ParticleAnalysisReport* Targetting::GetTargetRect()
{
	switch(*(static_cast<int*>(Robot::targetChooser->GetSelected())))
	{
	case 1:
		return &newestData->at(0);
	case 2:
		return GetTwoPointRect();
	case 3:
		return GetThreePointRect();
	default:
		return &newestData->at(0);
	}
}

ParticleAnalysisReport* Targetting::GetThreePointRect()
{
	return FindRectWithRatio(3.0, 0.2);
}

ParticleAnalysisReport* Targetting::GetTwoPointRect()
{
	return FindRectWithRatio(2.1, 0.3);
}

float Targetting::CalcDistance(ParticleAnalysisReport* rect)
{
	return DISTANCE_RATIO * rect->boundingRect.width + CONSTANT;
	// FAR_FEET - (width - FARDIST_WIDTH) * (STEP_FEET / STEP_WIDTH)
}

bool Targetting::Target()
{
	static int i = 0;
	Threshold threshold(0, 150, 200, 255, 200, 255);
	//Threshold threshold(151, 255, 0, 199, 0, 199);
	ColorImage* image;
	image = _camera.GetImage();
	DriverStationLCD* screen = DriverStationLCD::GetInstance();
	//image = new RGBImage("/testImage.jpg");
	if (image == NULL)
	{
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Can't get image");
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
		screen->UpdateLCD();
		return false;
	}
	else if (image->GetHeight() == 0 || image->GetWidth() == 0)
	{
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Height/width is zero");
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
		screen->UpdateLCD();
		return false;
	}
	BinaryImage *thresholdImage = image->ThresholdRGB(threshold);
	BinaryImage *convexHullImage = thresholdImage->ConvexHull(false);
	if (convexHullImage == NULL)
	{
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Can't process");
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
		screen->UpdateLCD();
		return false;
	}
	//convexHullImage->Write("/imageResult.jpg");
	//imaqWriteJPEGFile(convexHullImage->GetImaqImage(), "/TestImage.jpeg", 100, convexHullImage->);
	vector<ParticleAnalysisReport> *reports = convexHullImage->GetOrderedParticleAnalysisReports();
	int rectNum = reports->size();
	screen->PrintfLine(DriverStationLCD::kUser_Line4, "Num: %i, (%i, %i)", rectNum, rectNum ? reports->at(0).center_mass_x : 0, rectNum ? reports->at(0).center_mass_y : 0);
	screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
	if (reports->size() != 0)
	{
		/*
		screen->PrintfLine(DriverStationLCD::kUser_Line3, "Rect Center X: %f", reports->at(0).center_mass_x_normalized);
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Rect Center Y: %f", reports->at(0).center_mass_y_normalized);
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Rect Width: %i", reports->at(0).boundingRect.width);
		*/
		/*
		fstream outputFile("/processingData.txt");
		for (unsigned int num = 0; num < reports->size(); num++)
		{
			outputFile << "Report num " << (num + 1) << "\n";
			outputFile << "Rect Center X: " << reports->at(num).center_mass_x << "\n";
			outputFile << "Rect Relative Center X: " << reports->at(num).center_mass_x_normalized << "\n";
			outputFile << "Rect Center Y: " << reports->at(num).center_mass_y << "\n";
			outputFile << "Rect Relative Center Y: " << reports->at(num).center_mass_y_normalized << "\n";
			outputFile << "Rect Width: " << reports->at(num).boundingRect.width << "\n";
			outputFile << "Rect Height: " << reports->at(num).boundingRect.height << "\n \n";
		}
		outputFile.close();
		*/
	}
	screen->UpdateLCD();
	
	delete(newestData);
	newestData = reports;
	
	delete(thresholdImage);
	delete(convexHullImage);
	return true;
}



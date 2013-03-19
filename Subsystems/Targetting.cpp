#include "Targetting.h"
#include "Vision/RGBImage.h"
#include "DriverStationLCD.h"
#include <fstream>

Targetting::Targetting(): Subsystem("Targetting"), _camera(AxisCamera::GetInstance("10.36.63.11"))
{
	//ledRelay = new Relay(1, 2);
	//ledRelay->Set(Relay::kOn);
}

Targetting::~Targetting()
{
	//delete(ledRelay);
}

void Targetting::Target()
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
		screen->Clear();
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Can't get image");
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
		screen->UpdateLCD();
		return;
	}
	else if (image->GetHeight() == 0 || image->GetWidth() == 0)
	{
		screen->Clear();
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Height/width is zero");
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
		screen->UpdateLCD();
		return;
	}
	BinaryImage *thresholdImage = image->ThresholdRGB(threshold);
	BinaryImage *convexHullImage = thresholdImage->ConvexHull(false);
	if (convexHullImage == NULL)
	{
		screen->Clear();
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Can't process");
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
		screen->UpdateLCD();
		return;
	}
	convexHullImage->Write("/imageResult.jpg");
	//imaqWriteJPEGFile(convexHullImage->GetImaqImage(), "/TestImage.jpeg", 100, convexHullImage->);
	vector<ParticleAnalysisReport> *reports = convexHullImage->GetOrderedParticleAnalysisReports();
	
	screen->PrintfLine(DriverStationLCD::kUser_Line4, "Num. of rectangles: %i", reports->size());
	screen->PrintfLine(DriverStationLCD::kUser_Line5, "Time: %i", i++);
	if (reports->size() != 0)
	{
		/*
		screen->PrintfLine(DriverStationLCD::kUser_Line3, "Rect Center X: %f", reports->at(0).center_mass_x_normalized);
		screen->PrintfLine(DriverStationLCD::kUser_Line4, "Rect Center Y: %f", reports->at(0).center_mass_y_normalized);
		screen->PrintfLine(DriverStationLCD::kUser_Line5, "Rect Width: %i", reports->at(0).boundingRect.width);
		*/
		fstream outputFile("/processingData.txt");
		for (unsigned int num = 0; num < reports->size(); num++)
		{
			outputFile << "Report num " << (num + 1) << "\n";
			outputFile << "Rect Center X: " << reports->at(num).center_mass_x << "\n";
			outputFile << "Rect Center Y: " << reports->at(num).center_mass_y << "\n";
			outputFile << "Rect Width: " << reports->at(num).boundingRect.width << "\n";
			outputFile << "Rect Height: " << reports->at(num).boundingRect.height << "\n \n";
		}
		outputFile.close();
	}
	screen->UpdateLCD();
	
	delete(thresholdImage);
	delete(convexHullImage);
	delete(reports);
}

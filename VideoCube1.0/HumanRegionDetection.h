#pragma once
#include "cv.h"
#include <highgui.h> 
#include "HistogramOfOrientedGradients.h"
//#include "svm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Region
{
	int x;
	int y;
	int Width;
	int Height;
};
typedef struct Region VideoRegion;
class HumanRegionDetection
{
private:

	int _height;
	int _width;
	int _numberOfFrame;
	int _AviForamt;
	char _videoFileName[150];
	double** _hOGFeature;
	int** Label;
	IplImage** _frames;
	IplImage** _subFrames;
	int _FPS;
public:
	HumanRegionDetection(void);
	~HumanRegionDetection(void);
	void SaveImage(char* OutputPath,char* FileName,char* InputPath,int Frame,double scaling,char* tempAction);
	void ComputeHumanRegion(char *videoFileName);
	VideoRegion RoiRegion;
	void AddNoise(char* FileName);
	void ReSize(double scale,char* FileName);
	void RotationVideo(int RotationAngle,char* FileName);
	void SaveVideo(char *Path,char* FileName);
};

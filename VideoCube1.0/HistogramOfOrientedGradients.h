#pragma once
#define PI 3.14159
#include "cv.h"
#include <highgui.h> 
#include "math.h"
class HistogramOfOrientedGradients
{
private:
	double _piToAngle;
    double _pi90ToAngle;
    double** _gradientMaginitudeData;
    double** _gradientOrientationData;
    int _height;
    int _width;
    double* _histogram;
	int FeatureNumber;
	void HOGFeature(int blockSize);
public:
	HistogramOfOrientedGradients(int height,int width);
	~HistogramOfOrientedGradients(void);
	void ComputeBySobel(IplImage* inputImage, int blockSize);
	double* GetFeatureByOrientation(int index);
	double* GetFeatures();
	void ReleasGradientArray();
};

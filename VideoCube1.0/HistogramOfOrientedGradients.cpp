#include "StdAfx.h"
#include "HistogramOfOrientedGradients.h"

HistogramOfOrientedGradients::HistogramOfOrientedGradients(int height,int width)
{
	 _piToAngle = (180 / PI);
	 _pi90ToAngle = _piToAngle * PI / 2;
	 _height = height;
	 _width = width;
	_gradientOrientationData = new double*[_height];
	_gradientMaginitudeData = new double*[_height];
	for(int c = 0; c < _height; c++)
	{
		_gradientOrientationData[c] = new double[_width];
		_gradientMaginitudeData[c] = new double[_width];
		for(int r = 0 ; r < _width; r++)
		{
			_gradientOrientationData[c][r] = 0;
			_gradientMaginitudeData[c][r] = 0;
		}
	}
}

HistogramOfOrientedGradients::~HistogramOfOrientedGradients(void)
{
}

void HistogramOfOrientedGradients::HOGFeature(int blockSize)
{
	int CellSize = blockSize/3;

	int ModWidth = _width - _width % blockSize;
    int ModHeight = _height - _height % blockSize;

    int IndexOfHistogram = 0;
    
    int NumberOfCells = (ModWidth / blockSize) * (ModHeight / blockSize) * (blockSize/CellSize) * (blockSize/CellSize);

    FeatureNumber = NumberOfCells * 9;

    _histogram = new double[FeatureNumber];
	for(int i = 0 ; i < FeatureNumber; i++)
	{
		_histogram[i] = 0;
	}

   

    for (int c = 0; c < ModHeight; c += CellSize)
    {
        for (int r = 0; r < ModWidth; r += CellSize)
        {
            for (int y = c, LengthY = c + CellSize; y < LengthY; y++)
            {
                for (int x = r, LengthX = r + CellSize; x < LengthX; x++)
                {
                    int Index = -1;
                    int Gradient = (int)_gradientOrientationData[y][x];

                    if (Gradient >= 0 && Gradient <= 20) // 量化方向 0 : index = 0
                        Index = 0;
                    else if (Gradient >= 21 && Gradient <= 40) // 量化方向 45 : index = 1
                        Index = 1;
                    else if (Gradient >= 41 && Gradient <= 60) // 量化方向 90 : index = 2
                        Index = 2;
                    else if (Gradient >= 61 && Gradient <= 80) // 量化方向 135 : index = 3
                        Index = 3;
                    else if (Gradient >= 81 && Gradient <= 100) // 量化方向 135 : index = 4
                        Index = 4;
                    else if (Gradient >= 101 && Gradient <= 120) // 量化方向 135 : index = 5
                        Index = 5;
                    else if (Gradient >= 121 && Gradient <= 140) // 量化方向 135 : index = 6
                        Index = 6;
                    else if (Gradient >= 141 && Gradient <= 160) // 量化方向 135 : index = 7
                        Index = 7;
                    else if (Gradient >= 161 && Gradient <= 180) // 量化方向 135 : index = 8
                        Index = 8;

                    _histogram[IndexOfHistogram + Index] += _gradientMaginitudeData[c][r];
                }
            }
            IndexOfHistogram += 9;
        }
    }
}

void HistogramOfOrientedGradients::ComputeBySobel(IplImage* inputImage, int blockSize)
{

	IplImage* GrayImage = cvCreateImage(cvSize(_width, _height), inputImage->depth, 1);
	IplImage* XImage = cvCreateImage(cvSize(_width, _height), inputImage->depth, 1);
	IplImage* YImage = cvCreateImage(cvSize(_width, _height), inputImage->depth, 1);
	GrayImage->origin = 1;
	YImage->origin = 1;
	GrayImage->origin = 1;
	cvCvtColor(inputImage, GrayImage, CV_BGR2GRAY);
	cvSobel(GrayImage, XImage, 1, 0, 3);
	cvSobel(GrayImage, YImage, 0, 1, 3);
	


    for (int c = 0; c < _height; c++)
    {
		for (int r = 0; r < XImage->widthStep; r++)
        {
			int Loc = c * XImage->widthStep + r;
			double SobelXValue = XImage->imageData[Loc];
			double SobelYValue = YImage->imageData[Loc];
			double Gradient = -1;
			_gradientMaginitudeData[c][r]= sqrt(SobelXValue * SobelXValue + SobelYValue * SobelYValue);

			if (SobelXValue == 0)
                Gradient = _pi90ToAngle;
            else
                Gradient =atan(SobelYValue / SobelXValue) * _piToAngle;

			_gradientOrientationData[c][r] = Gradient + 90;
            /*double Gradient = -1;
            _gradientMaginitudeData[c][r]= sqrt(SobelYData[c][r] * SobelYData[c][r] + SobelXData[c][r] * SobelXData[c][r]);
            
            if (SobelXData[c][r] == 0)
                Gradient = _pi90ToAngle;
            else
                Gradient =atan(SobelYData[c][r] / SobelXData[c][r]) * _piToAngle;
            _gradientOrientationData[c][r] = Gradient + 90;*/
        }
    }
    /*for (int c = 0; c < _height; c++)
        for (int r = 0; r < _width; r++)
            _gradientMaginitudeData[c, r] = Math.Abs(_gradientMaginitudeData[c, r] - _gradientMaginitudeData[_height / 2, _width / 2]);*/
        
    HOGFeature(blockSize);
	cvReleaseImage(&GrayImage);
	cvReleaseImage(&XImage);
	cvReleaseImage(&YImage);
}

double* HistogramOfOrientedGradients::GetFeatureByOrientation(int index)
{
    /*int Length = _histogram.Length;
    double[] Features = new double[Length/9];
    int Next = 0;
    for (int i = 0; i < Length; i += 9)
    {
        Features[Next++] = _histogram[i + index];
    }
    return Features;*/

    int Length = FeatureNumber;
    double Features[300];
    int Next = 0;
    for (int i = index; i < index+300; i++)
    {
        Features[Next++] = _histogram[i];
    }
    return Features;
}

double* HistogramOfOrientedGradients::GetFeatures()
{
    return _histogram;
}

void HistogramOfOrientedGradients::ReleasGradientArray()
{
	for(int c = 0; c < _height; c++)
	{
			delete _gradientOrientationData[c];
			delete _gradientMaginitudeData[c];
	}
}
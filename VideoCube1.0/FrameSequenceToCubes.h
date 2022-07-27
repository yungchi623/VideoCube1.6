#pragma once
#include "cv.h"
#include "Cube.h"

struct FrameInfo // 用來暫存每張frame的資訊
{
	double* R;
	double* G;
	double* B;
	double* Gray;
};

struct CubeInfo
{
	double COSA;
	double COSB;
	double COSR;
	double L;
	double H1;
	double H2;
	int IndexHeight;
	int IndexWidth;
	int IndexTime;
	double M0;
	double MX;
	double MY;
	double MT;
	double AverageGrayValue;
	double CubeGradient;
};

class FrameSequenceToCubes
{
private:
	FrameInfo* _frameInfo;
	CubeInfo* _cubeInfo;
	Cube _cube; // 用來計算moment
	int _numberOfFrame; // 一次要處裡的frame數量
	int _height; // frame 高度
	int _width; // frame 寬度
	int _numberOfCube; // Cube的個數
public:
	FrameSequenceToCubes(int numberOfFrame, int height, int width);
	~FrameSequenceToCubes(void);
	void Transform(IplImage* frames[], int t); // 輸入對應於_numberOfFrame數目的影像及其時間位置
	void Decode();
	Cube decoding(double COSA, double COSB, double COSR, int h1, int h2, double L);
	IplImage* pixelsToImage(double* pixels, int iw, int ih);
	double* GetCubeGradient();
	IplImage* img[4];
	CubeInfo* GetCubeInfo();
	int GetNumberOfCubeInfo();
	void ReleaseBuffer();
};

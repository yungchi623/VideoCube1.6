#pragma once
#include "cv.h"
#include "Cube.h"

struct FrameInfo // �ΨӼȦs�C�iframe����T
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
	Cube _cube; // �Ψӭp��moment
	int _numberOfFrame; // �@���n�B�̪�frame�ƶq
	int _height; // frame ����
	int _width; // frame �e��
	int _numberOfCube; // Cube���Ӽ�
public:
	FrameSequenceToCubes(int numberOfFrame, int height, int width);
	~FrameSequenceToCubes(void);
	void Transform(IplImage* frames[], int t); // ��J������_numberOfFrame�ƥت��v���Ψ�ɶ���m
	void Decode();
	Cube decoding(double COSA, double COSB, double COSR, int h1, int h2, double L);
	IplImage* pixelsToImage(double* pixels, int iw, int ih);
	double* GetCubeGradient();
	IplImage* img[4];
	CubeInfo* GetCubeInfo();
	int GetNumberOfCubeInfo();
	void ReleaseBuffer();
};

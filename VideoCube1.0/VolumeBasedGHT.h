#pragma once
#include "cv.h"
#include <highgui.h> 
#include "FrameSequenceToCubes.h"

#define SIZE 25600
using namespace System;
struct RTableParameter
{
	double R;
	double XP[3];
	double N[3];
	double NR[3];
	struct RTableParameter* Next;
};
typedef struct RTableParameter ParameterNode;

struct Histogram
{
	int Bar[256];
};
typedef struct Histogram ImageHistogram;
struct RTable
{
	int NumberOfParam;
	ParameterNode* Head;
	ParameterNode* Ptr; // 增加建立 RTable的速度
};
typedef struct RTable RTableNode;

struct VotePoint
{
	double scaling;
	int x;
	int y;
	int t;
	int Arotation;
	int Brotation;
	int Vote;
	double Similar;
	char FileName[150];
};
typedef struct VotePoint ImagePoint;

class VolumeBasedGHT
{
	// ******************** R-Table ********************
private :
	char _fileName[100];
	char _TemplateFileName[300];
	RTableNode _rTable[SIZE];
	double _gradient[SIZE];
	int _countIndex;
	int _tNumberOfCube;
	int _vNumberOfCube;
	CubeInfo* CubeInformation;
	int _tHeight, _tWidth, _tTime;
	double** _templateCubeGradient; // 用來存每個cube的gradient  _rCubeGradient
	RTableParameter* ConstructRTableParameterNode(double r, double* xp, double* n, double* nr);
	double centerNormal[3];
public:
	ImagePoint *VoteCoordinate;
	ImagePoint *GetVoteCoordinate();
	int ComputeRTable(char* videoFileName);
	void ReleaseRTable();
	int ComputeCubeDataBase(char* videoFileName,char* outputFileName);
	int LoadCubeDataBase(char* videoFileName);
	void  Release();

	// ******************** R-Table ********************

	// ******************** Voting ********************
private :
	//int*** _votingTable;
	int*** _votingTable[3][2][2];//scaling rotation
	int _vHeight, _vWidth, _vTime;
	int _vMax, _vMin, _vLocX, _vLocY, _vLocZ;
public:
	//double *Similar;
	double Voting(char* videoFileName,char* CubeFileName,double scaling,int TopN,char* TempleteFileName);
	void ReleaseVoteTable();
	double ComputeSimilar(int CX, int CY, int CZ, double scaling,int Rotation,char *FileName);
	// ******************** Voting ********************
	VolumeBasedGHT(void);
	// ******************** TopN ********************
private:
	ImagePoint* TopNSort(int N);
	void DrawImage(char *FileName,ImagePoint *VotePoint,int N,char* TempleteFileName);
	int FindTopSimular(char *FileName,ImagePoint *VoteCoordinate,int N,int Feature);

private:
	double TempleteHistogram[256];
	double VideoRoiHistogram[256];
	void ComputeVideoGradientHistogram(double *Histogram,double* CubeGradient,bool* HasValue,int NumberOfCube);
	void ComputeTempleteGradientHistogram(double *Histogram,double* CubeGradient,int NumberOfCube);


};

#pragma once
#include <stdio.h>
#include <string.h>
#include "time.h"
#include "VolumeBasedGHT.h"
struct TopName
{
	char FileName[150];
	char Name[50];
};typedef struct TopName TopNAction;

ref class VBGHTSimular
{

private:
	double *totalSimularity;
	TopNAction *ActionName;
	int CountTopTen;
	int TopN;
	double percent;
	ImagePoint *SimularVoteCoordinate;
public:
	VBGHTSimular(int topN);
	void Simularity(double simular,char* databaseaction,char* databasename);
	void ResultSimular(char* templeteaction,char* templetefilename,time_t end);
	void Release();
	void VoteCoordinateSimularity(ImagePoint *VoteCoordinate,int RecordN);
	void SaveResultSimular(char* TempleteFileName,char* templeteaction,time_t end);
};

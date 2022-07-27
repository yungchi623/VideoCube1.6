#pragma once
#include <string.h>
#include <stdio.h>
class KthNearestNeighbor
{
private:
	double _totalTestData;
	double _correct;

	char _bufferOfName[6][30];
	
	
	int  _totalNameInBuffer;

	int _countType[25][6];

	double _correctPercent[25];
public:
	KthNearestNeighbor();
	~KthNearestNeighbor();
	void AddCompute(char* fileName, int kth);
	void FinalCompute(int kth);
	void SaveCorrect(char* fileName);
	void Initial();
	
};

#include "StdAfx.h"
#include "KthNearestNeighbor.h"

KthNearestNeighbor::KthNearestNeighbor()
{
	for(int i = 0; i < 25; i++)
		for(int j = 0; j < 6; j++)
			_countType[i][j] = 0;
	Initial();	
}

KthNearestNeighbor::~KthNearestNeighbor()
{
}

void KthNearestNeighbor :: AddCompute(char* fileName, int kth)
{
	FILE* FilePtr = fopen(fileName, "r");
	char TargetName[20] = {0};
	char ResultName[20] = {0};
	
	double Similar;
	double FName[20];
	
	double CountSimilat[6] = {0};
	int CountName[6] = {0};

	for(int i = 0; i < kth; i++)
	{
		fscanf(FilePtr, "%s : %s %lf %s\n",TargetName, ResultName, &Similar, FName);

		bool IsSame = false;
		for(int j = 0; j < _totalNameInBuffer; j++)
		{
			if(!strcmp(ResultName, _bufferOfName[j]))
			{
				CountName[j]++;
				CountSimilat[j] += Similar;
				IsSame = true;
				break;
			}
		}

		if(IsSame == false)
		{
			int S = 0;
			S = 1;
		}
	}

	int MaxIndex = -1;
	int MaxValue = -1;
	double MaxSimilar = -1;
	for(int j = 0; j < _totalNameInBuffer; j++)
	{
		if(MaxValue == CountName[j])
		{
			if(MaxSimilar > CountSimilat[j])
			{
				MaxValue = CountName[j];
				MaxIndex = j;
				MaxSimilar = CountSimilat[j];
			}
		}
		if(MaxValue < CountName[j])
		{
			MaxValue = CountName[j];
			MaxIndex = j;
			MaxSimilar = CountSimilat[j];
		}
	}

	_countType[kth - 1][MaxIndex]++;
	
	if(!strcmp(TargetName, _bufferOfName[MaxIndex]))
		_correct++;
	_totalTestData++;

	fclose(FilePtr);
}

void KthNearestNeighbor :: Initial()
{
	_totalTestData = 0;
	_correct = 0;

	_totalNameInBuffer = 6;

	//
	int Next = 0;
	
	strcpy(_bufferOfName[Next++], "walking");
	strcpy(_bufferOfName[Next++], "boxing");
	strcpy(_bufferOfName[Next++], "jogging");
	strcpy(_bufferOfName[Next++], "handclapping");
	strcpy(_bufferOfName[Next++], "running");
	strcpy(_bufferOfName[Next++], "handwaving");

}	

void KthNearestNeighbor :: SaveCorrect(char* fileName)
{
	FILE* FilePtr = fopen(fileName, "w");

	for(int i = 0; i < 25; i++)
	{
		fprintf(FilePtr, "kth : %d\t", i + 1);
		fprintf(FilePtr, "Correct Rate : %lf\t", _correctPercent[i]);

		for(int j = 0; j < 6; j++)
			fprintf(FilePtr, "%s : %d\t", _bufferOfName[j], _countType[i][j]);

		fprintf(FilePtr, "\n");
	}

	fclose(FilePtr);
}

void KthNearestNeighbor :: FinalCompute(int kth)
{
	_correctPercent[kth - 1] = _correct / _totalTestData;
}
#pragma once

ref class CountRank
{
public:
	CountRank(void);
	int *RecordRank;
	void ComputeRank(char* TempleteFileName,int TopN,int FileIndex);
	void SaveDetection(char* FileName);
};

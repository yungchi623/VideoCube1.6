#include "StdAfx.h"
#include "CountRank.h"
#include <stdio.h>
#include "string.h"
CountRank::CountRank(void)
{
	RecordRank = new int[31];
	for(int i = 0 ; i < 31; i++)
	{
		RecordRank[i] = 0;
	}
}

void CountRank::ComputeRank(char* TempleteFileName,int TopN,int FileIndex)
{
	char RankFileName[100];
	char TempFileName[500];
	char TargetFileName[100];
	int Rank = 0;

	char templeteaction[30];
	char VideoFileName[30];
	double Similar;


	char _bufferOfName[6][30];
	int Next = 0;

	strcpy(_bufferOfName[Next++], "walking");
	strcpy(_bufferOfName[Next++], "boxing");
	strcpy(_bufferOfName[Next++], "jogging");
	strcpy(_bufferOfName[Next++], "handclapping");
	strcpy(_bufferOfName[Next++], "running");
	strcpy(_bufferOfName[Next++], "handwaving");

	char * temptoken;
	char tempstr[] = ":\\_";
	bool isNAction = true;

	sprintf(TempFileName,"%s",TempleteFileName);
	temptoken = strtok( TempFileName, tempstr);

	while ( isNAction )
	{
		sprintf(TargetFileName,"%s",temptoken);
		temptoken = strtok( NULL, tempstr );
		for(int i = 0 ; i < 6; i++)
		{
			if(!strcmp(_bufferOfName[i],TargetFileName))
				isNAction = false;
		}
	} // while



	FILE *FilePtr= fopen(TempleteFileName,"r");
	for(int step = 1 ; step <= TopN;step++ )
	{
		fscanf(FilePtr, "%s : %s %lf %s\n", templeteaction, VideoFileName,&Similar,TempFileName);
		char * token;
		char str[] = ":\\_";
		//bool isNAction = true;

		/*token = strtok( TempFileName, str);

		while ( isNAction ) {

			sprintf(RankFileName,"%s",token);
			token = strtok( NULL, str );
			for(int i = 0 ; i < 6; i++)
			{
				if(!strcmp(_bufferOfName[i],RankFileName))
					isNAction = false;
			}
		} // while*/
		sprintf(RankFileName,"%s",VideoFileName);
		
		if(!strcmp(TargetFileName,RankFileName))
		{
			Rank = step;
			break;
		}
	}
	fclose(FilePtr);

	RecordRank[Rank]++;

}

void CountRank::SaveDetection(char* FileName)
{
	FILE *FilePtr= fopen(FileName,"w");

	int RecordCountRank = 0;

	for(int i = 0; i < 31; i++)
	{
		fprintf(FilePtr,"%d\t",i);
	}
	fprintf(FilePtr,"\n");

	for(int i = 0; i < 31; i++)
	{
		if( i > 0)
		{
			RecordCountRank += RecordRank[i];
			fprintf(FilePtr,"%d\t",RecordCountRank);
		}
		else
		{
			fprintf(FilePtr,"%d\t", RecordRank[i]);
		}
	}
	fclose(FilePtr);

}
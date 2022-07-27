#include "StdAfx.h"
#include "VBGHTSimular.h"


VBGHTSimular::VBGHTSimular(int topN)
{
	CountTopTen = 0;
	totalSimularity = new double[topN];
	ActionName = new TopNAction[topN];
	SimularVoteCoordinate = new ImagePoint[topN];
	TopN = topN;
}

void VBGHTSimular::VoteCoordinateSimularity(ImagePoint *VoteCoordinate,int RecordN)
{

	ImagePoint tempVoteCoordinate;

	for(int step = 0 ; step < RecordN; step++)
	{
		if(VoteCoordinate[step].Similar != -1)
		{
			if(CountTopTen < TopN) // 塞滿前十名
			{				
				SimularVoteCoordinate[CountTopTen].Similar = VoteCoordinate[step].Similar;
				SimularVoteCoordinate[CountTopTen].Arotation = VoteCoordinate[step].Arotation;
				SimularVoteCoordinate[CountTopTen].Brotation = VoteCoordinate[step].Brotation;
				SimularVoteCoordinate[CountTopTen].scaling = VoteCoordinate[step].scaling;
				SimularVoteCoordinate[CountTopTen].t = VoteCoordinate[step].t;
				SimularVoteCoordinate[CountTopTen].x = VoteCoordinate[step].x;
				SimularVoteCoordinate[CountTopTen].y = VoteCoordinate[step].y;
				SimularVoteCoordinate[CountTopTen].Vote = VoteCoordinate[step].Vote;
				sprintf(SimularVoteCoordinate[CountTopTen].FileName,"%s",VoteCoordinate[step].FileName);
				CountTopTen++;
			}
			else if(CountTopTen == TopN) // 排序一次
			{
				CountTopTen++;
				for(int i = 0; i < TopN; i++)
				{
					for(int j = i; j < TopN; j++)
					{
						if( SimularVoteCoordinate[i].Similar  > SimularVoteCoordinate[j].Similar)
						{
							tempVoteCoordinate.Similar = SimularVoteCoordinate[i].Similar;
							SimularVoteCoordinate[i].Similar = SimularVoteCoordinate[j].Similar;
							SimularVoteCoordinate[j].Similar = tempVoteCoordinate.Similar;

							tempVoteCoordinate.Arotation = SimularVoteCoordinate[i].Arotation;
							SimularVoteCoordinate[i].Arotation = SimularVoteCoordinate[j].Arotation;
							SimularVoteCoordinate[j].Arotation = tempVoteCoordinate.Arotation;

							tempVoteCoordinate.Brotation = SimularVoteCoordinate[i].Brotation;
							SimularVoteCoordinate[i].Brotation = SimularVoteCoordinate[j].Brotation;
							SimularVoteCoordinate[j].Brotation = tempVoteCoordinate.Brotation;

							tempVoteCoordinate.scaling = SimularVoteCoordinate[i].scaling;
							SimularVoteCoordinate[i].scaling = SimularVoteCoordinate[j].scaling;
							SimularVoteCoordinate[j].scaling = tempVoteCoordinate.scaling;

							tempVoteCoordinate.t = SimularVoteCoordinate[i].t;
							SimularVoteCoordinate[i].t = SimularVoteCoordinate[j].t;
							SimularVoteCoordinate[j].t = tempVoteCoordinate.t;		

							tempVoteCoordinate.x = SimularVoteCoordinate[i].x;
							SimularVoteCoordinate[i].x = SimularVoteCoordinate[j].x;
							SimularVoteCoordinate[j].x = tempVoteCoordinate.x;	

							tempVoteCoordinate.y = SimularVoteCoordinate[i].y;
							SimularVoteCoordinate[i].y = SimularVoteCoordinate[j].y;
							SimularVoteCoordinate[j].y = tempVoteCoordinate.y;

							tempVoteCoordinate.Vote = SimularVoteCoordinate[i].Vote;
							SimularVoteCoordinate[i].Vote = SimularVoteCoordinate[j].Vote;
							SimularVoteCoordinate[j].Vote = tempVoteCoordinate.Vote;

							sprintf(tempVoteCoordinate.FileName,"%s",SimularVoteCoordinate[i].FileName);
							sprintf(SimularVoteCoordinate[i].FileName,"%s",SimularVoteCoordinate[j].FileName);
							sprintf(SimularVoteCoordinate[j].FileName,"%s",tempVoteCoordinate.FileName);


						}
					}
				}
			}
			else // 一一比較是否屬於前十名
			{
				int i;
				for(i = TopN - 1; i >= 0; i--)
				{
					if(VoteCoordinate[step].Similar > SimularVoteCoordinate[i].Similar)
						break;
				}
				i++;
				if(i < TopN)
				{
					for(int j = TopN - 1; j > i; j--)
					{

						SimularVoteCoordinate[j].Similar = SimularVoteCoordinate[j-1].Similar;
						SimularVoteCoordinate[j].Arotation = SimularVoteCoordinate[j-1].Arotation;
						SimularVoteCoordinate[j].Brotation = SimularVoteCoordinate[j-1].Brotation;
						SimularVoteCoordinate[j].scaling = SimularVoteCoordinate[j-1].scaling;
						SimularVoteCoordinate[j].Vote = SimularVoteCoordinate[j-1].Vote;
						SimularVoteCoordinate[j].x = SimularVoteCoordinate[j-1].x;
						SimularVoteCoordinate[j].y = SimularVoteCoordinate[j-1].y;
						SimularVoteCoordinate[j].t = SimularVoteCoordinate[j-1].t;
						sprintf(SimularVoteCoordinate[j].FileName,"%s",SimularVoteCoordinate[j-1].FileName);

					}
					SimularVoteCoordinate[i].Similar  = VoteCoordinate[step].Similar;
					SimularVoteCoordinate[i].Arotation  = VoteCoordinate[step].Arotation;
					SimularVoteCoordinate[i].Brotation  = VoteCoordinate[step].Brotation;
					SimularVoteCoordinate[i].scaling  = VoteCoordinate[step].scaling;
					SimularVoteCoordinate[i].Vote  = VoteCoordinate[step].Vote;
					SimularVoteCoordinate[i].x  = VoteCoordinate[step].x;
					SimularVoteCoordinate[i].y  = VoteCoordinate[step].y;
					SimularVoteCoordinate[i].t  = VoteCoordinate[step].t;
					sprintf(SimularVoteCoordinate[i].FileName,"%s",VoteCoordinate[step].FileName);

				}
			}
		}
	}
}

void VBGHTSimular::SaveResultSimular(char* TempleteFileName,char* templeteaction,time_t end)
{	
	char VideoFileName[50];
	char FileName[150];
	char tempFileName[200];
	char _bufferOfName[6][30];
	double percent = 0;
	int Next = 0;
	strcpy(_bufferOfName[Next++], "walking");
	strcpy(_bufferOfName[Next++], "boxing");
	strcpy(_bufferOfName[Next++], "jogging");
	strcpy(_bufferOfName[Next++], "handclapping");
	strcpy(_bufferOfName[Next++], "running");
	strcpy(_bufferOfName[Next++], "handwaving");

	sprintf(FileName,"Test\\simular\\%s.txt",TempleteFileName);
	FILE *FilePtr= fopen(FileName,"w");

	for(int step = 0 ; step < TopN;step++ )
	{
		//CvCapture *Capture = cvCaptureFromAVI(SimularVoteCoordinate[step].FileName);
	
		//int Height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
		//int Width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
		//int Time = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	
		//CvScalar Color;
 		//int Thickness=2;
		//int Shift=0;
		sprintf(tempFileName,"%s",SimularVoteCoordinate[step].FileName);

		char * token;
		char str[] = ":\\_";
		bool isNAction = true;

		token = strtok( SimularVoteCoordinate[step].FileName, str);

		//while ( token != NULL ) {
		while ( isNAction )
		{
			sprintf(VideoFileName,"%s",token);
			token = strtok( NULL, str );
			for(int i = 0 ; i < 6; i++)
			{
				if(!strcmp(_bufferOfName[i],VideoFileName))
					isNAction = false;
			}

		} // while
	    
		/*for(int f = 0; f < Time; f++)
		{

			IplImage* Img = cvQueryFrame(Capture);

			double scaling = SimularVoteCoordinate[step].scaling;
			int Vote = SimularVoteCoordinate[step].Vote;

			if( SimularVoteCoordinate[step].t == f || SimularVoteCoordinate[step].t - 3 == f || SimularVoteCoordinate[step].t + 3 == f)
			{
				Color = CV_RGB(255,0,0);
				cvRectangle(Img, cvPoint(SimularVoteCoordinate[step].x - (Width*scaling/2), SimularVoteCoordinate[step].y - (Height*scaling/2)), cvPoint(SimularVoteCoordinate[step].x + (Width*scaling/2), SimularVoteCoordinate[step].y + (Height*scaling/2)), Color, Thickness, CV_AA, Shift);
				cvRectangle(Img, cvPoint(SimularVoteCoordinate[step].x - 3, SimularVoteCoordinate[step].y - 3), cvPoint(SimularVoteCoordinate[step].x + 3, SimularVoteCoordinate[step].y + 3), Color, Thickness, CV_AA, Shift);

				char OutputFileFolder[400];
				sprintf(OutputFileFolder, "Test\\%s_%s_%dG.jpg",TempleteFileName,VideoFileName,f);
				cvSaveImage(OutputFileFolder, Img);				
			}
			
		}
		cvReleaseCapture(&Capture);*/


		if(!strcmp(templeteaction,VideoFileName))
		{
				percent++;
		}
		fprintf(FilePtr, "%s : %s %lf %s\n", templeteaction, VideoFileName,SimularVoteCoordinate[step].Similar,tempFileName);
	}
	fprintf(FilePtr, "%s : %lf\n", templeteaction, percent /TopN * 100);
	fprintf(FilePtr,"Time: %lf\n",(double)(end/1000.0));

	fclose(FilePtr);

}


void VBGHTSimular::Simularity(double simular,char* databaseaction,char* databasename)
{
	double temp;
	char tempAction[50];
	char tempFileName[150];


	if(simular != -1)
	{
		if(CountTopTen < TopN) // 塞滿前十名
		{
			totalSimularity[CountTopTen] = simular;
			sprintf(ActionName[CountTopTen].Name,"%s",databaseaction);
			sprintf(ActionName[CountTopTen].FileName,"%s",databasename);
			CountTopTen++;
		}
		else if(CountTopTen == TopN) // 排序一次
		{
			CountTopTen++;
			for(int i = 0; i < TopN; i++)
			{
				for(int j = i; j < TopN; j++)
				{
					if(totalSimularity[i] > totalSimularity[j])
					{
						temp = totalSimularity[i];
						totalSimularity[i] = totalSimularity[j];
						totalSimularity[j] = temp;
						sprintf(tempAction,"%s",ActionName[i].Name);
						sprintf(ActionName[i].Name,"%s",ActionName[j].Name);
						sprintf(ActionName[j].Name,"%s",tempAction);
						sprintf(tempFileName,"%s",ActionName[i].FileName);
						sprintf(ActionName[i].FileName,"%s",ActionName[j].FileName);
						sprintf(ActionName[j].FileName,"%s",tempFileName);
					}
				}
			}
		}
		else // 一一比較是否屬於前十名
		{
			int i;
			for(i = TopN - 1; i >= 0; i--)
			{
				if(simular > totalSimularity[i])
					break;
			}
			i++;
			if(i < TopN)
			{
				for(int j = TopN - 1; j > i; j--)
				{
					totalSimularity[j] = totalSimularity[j-1];
					sprintf(ActionName[j].Name,"%s",ActionName[j-1].Name);
					sprintf(ActionName[j].FileName,"%s",ActionName[j-1].FileName);
				}
				totalSimularity[i] = simular;
				sprintf(ActionName[i].Name,"%s",databaseaction);
				sprintf(ActionName[i].FileName,"%s",databasename);
			}
		}
	}
}



void VBGHTSimular::ResultSimular(char* templeteaction,char* templetefilename,time_t end)
{	
	char FileName[150];
	sprintf(FileName,"Test\\simular\\%s.txt",templetefilename);
	FILE *FilePtr= fopen(FileName,"w");
	double percent = 0;
	for(int current = 0;current < TopN;current++)
	{
		if(!strcmp(templeteaction,ActionName[current].Name))
		{
			percent++;
		}
		fprintf(FilePtr, "%s : %s %lf %s\n", templeteaction, ActionName[current].Name,totalSimularity[current],ActionName[current].FileName);
	}
	fprintf(FilePtr, "%s : %lf\n", templeteaction, percent /TopN * 100);
	fprintf(FilePtr,"Time: %lf\n",(double)(end/1000.0));
	fclose(FilePtr);
}
void VBGHTSimular::SaveFile(char* FileName,int f)
{
	if((percent /TopN * 100) >= 30.0)
	{
		FILE *FilePtr2= fopen(FileName,"a");

		fprintf(FilePtr2, "%d, ",f);

		fclose(FilePtr2);
	}
}
void VBGHTSimular::Release()
{
	delete totalSimularity;
	totalSimularity = NULL;
	delete ActionName;
	ActionName = NULL;
	delete SimularVoteCoordinate;
	SimularVoteCoordinate = NULL;
}
#include "StdAfx.h"
#include "VolumeBasedGHT.h"
#include <stdio.h>

VolumeBasedGHT::VolumeBasedGHT(void)
{
	
}


int VolumeBasedGHT::ComputeRTable(char* videoFileName)//計算template的rtable
{
	CvCapture* Capture = cvCaptureFromAVI(videoFileName);
	double gradient;
	_countIndex = 0;
	_tHeight = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_tWidth = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_tTime = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);

	_tTime -= (_tTime % 4); // 因為一次取四張frame所以少計算一些frame使能被4整除
	
	
	if(_tHeight == 0 || _tWidth == 0 || _tTime == 0)
	{
		cvReleaseCapture(&Capture);
		return -1;
	}


	IplImage* Frames[4];
	IplImage* tempFrames[4];
	//IplImage* tempFrame;

	Frames[0] = cvCreateImage(cvSize(_tWidth, _tHeight), 8, 3);
	Frames[1] = cvCreateImage(cvSize(_tWidth, _tHeight), 8, 3);
	Frames[2] = cvCreateImage(cvSize(_tWidth, _tHeight), 8, 3);
	Frames[3] = cvCreateImage(cvSize(_tWidth, _tHeight), 8, 3);
	//Frames[0]->origin = 1;
	//Frames[1]->origin = 1;
	//Frames[2]->origin = 1;
	//Frames[3]->origin = 1;

	//tempFrame = cvCreateImage(cvSize(_tWidth, _tHeight), 8, 3);
	//tempFrame->origin = 1;
	int CountFrame = 0; // 用來紀錄取得之影像個數, 每四張計算一次

	FrameSequenceToCubes FrameSequenceToCubesObj(4, _tHeight, _tWidth);
	
	double XR[3] = {_tWidth / 2, _tHeight / 2, _tTime / 2}; 
	for(int i = 0; i < SIZE; i++)
		_rTable[i].NumberOfParam = 0;

	_templateCubeGradient = new double*[_tTime/4];//CubeSimular
	//double threshold;
	for(int f = 0; f < _tTime; f++)
	{

		try
		{
			cvCopy( cvQueryFrame(Capture), Frames[CountFrame]);
		}
		catch(cv::Exception e)
		{
			for(int i = 0; i < _tTime/4; i++)
				_templateCubeGradient[i] = new double[2];
			cvReleaseImage(&Frames[0]);
			cvReleaseImage(&Frames[1]);
			cvReleaseImage(&Frames[2]);
			cvReleaseImage(&Frames[3]);
			FrameSequenceToCubesObj.ReleaseBuffer();
			cvReleaseCapture(&Capture);
			ReleaseRTable();
			return -1;
		}
		

		CountFrame++;
		if(CountFrame == 4 && f != (_tTime / 2.0 + 4))
			CountFrame = 0;
		if(f == _tTime / 2.0 + 4)
		{
			CountFrame = 0;
			FrameSequenceToCubesObj.Transform(Frames, f - 3);
			CubeInfo* CubeInformation = FrameSequenceToCubesObj.GetCubeInfo();
			int NumberOfCube = FrameSequenceToCubesObj.GetNumberOfCubeInfo();
			int centerCube = NumberOfCube/2.0;//floor(Height/8.0)*Width+floor(Width/8.0);
			centerNormal[0] =CubeInformation[centerCube].COSA;
			centerNormal[1] =CubeInformation[centerCube].COSB;
			centerNormal[2] =CubeInformation[centerCube].COSR;
		}
	}


	cvReleaseCapture(&Capture);
	
	Capture = cvCaptureFromAVI(videoFileName);
	CountFrame = 0;
	int Next = 0;
	char OutputFileFolder[300];

	for(int f = 0; f < _tTime; f++)
	{
			
		try
		{
			sprintf(OutputFileFolder, "%s_%d.jpg",videoFileName,f+CountFrame);
			cvCopy(cvQueryFrame(Capture), Frames[CountFrame]);
			cvSaveImage(OutputFileFolder, Frames[CountFrame]);	
		}
		catch(cv::Exception e)
		{
			for(int i = 0; i < _tTime/4; i++)
				_templateCubeGradient[i] = new double[2];
			cvReleaseImage(&Frames[0]);
			cvReleaseImage(&Frames[1]);
			cvReleaseImage(&Frames[2]);
			cvReleaseImage(&Frames[3]);
			FrameSequenceToCubesObj.ReleaseBuffer();
			cvReleaseCapture(&Capture);
			ReleaseRTable();
			return -1;
		}


		CountFrame++;
		if(CountFrame == 4)
		{
		
			CountFrame = 0;
			FrameSequenceToCubesObj.Transform(Frames, f - 3);
			CubeInfo* CubeInformation = FrameSequenceToCubesObj.GetCubeInfo();
			
			_tNumberOfCube = FrameSequenceToCubesObj.GetNumberOfCubeInfo();
			_templateCubeGradient[Next++] = FrameSequenceToCubesObj.GetCubeGradient();
			for(int i = 0; i < _tNumberOfCube; i++)
			{
				double XPC[3] = {CubeInformation[i].IndexWidth + 2, CubeInformation[i].IndexHeight + 2, CubeInformation[i].IndexTime + 2}; // Cube中心位置
				double XP[3] = {0}; // 計算平面上座標
				double N[3] = {CubeInformation[i].COSA, CubeInformation[i].COSB, CubeInformation[i].COSR};

				XP[0] = XPC[0] + CubeInformation[i].L * N[0];
				XP[1] = XPC[1] + CubeInformation[i].L * N[1];
				XP[2] = XPC[2] + CubeInformation[i].L * N[2];
				double R = sqrt((XP[0]-XR[0])*(XP[0]-XR[0]) + (XP[1]-XR[1])*(XP[1]-XR[1]) + (XP[2]-XR[2])*(XP[2]-XR[2])); // 計算平面上的點到物件中心點的距離
				double NR[3] = {XR[0] - XP[0], XR[1] - XP[1], XR[2] - XP[2]};
				double tempR;
				tempR = R;
				if(R == 0)
					tempR = 1;
				NR[0] /= tempR;
				NR[1] /= tempR;
				NR[2] /= tempR;

				double AverageGray = 0;
				// 計算八個方向
				double CountDir = 0;
				int IH = CubeInformation[i].IndexHeight;
				int IW = CubeInformation[i].IndexWidth;

				for(int ih = IH - 4; ih <= IH + 4; ih += 4)
				{
					for(int iw = IW - 4; iw <= IW + 4; iw += 4)
					{
						if(ih == IH && iw == IW)
							continue;
						int CubeInformationIndex = ih + iw / 4;
						if(CubeInformationIndex >= 0 && CubeInformationIndex < _tNumberOfCube)
						{
							AverageGray += CubeInformation[CubeInformationIndex].AverageGrayValue;
							CountDir++;
						}
					}
				}
				if(CountDir == 0)
					CountDir = 1;
				AverageGray /= CountDir;

				// END 計算八個方向
				if(AverageGray == 0)
					AverageGray = 1;

                gradient = abs(CubeInformation[i].H2 - CubeInformation[i].H1) / AverageGray;

				bool IsFind = false;
				int IndexOfOfind = -1;

				for(int S = 0; S < _countIndex; S++)
				{
					if(abs(_gradient[S] - gradient) <= 0.01)
					{
						IsFind = true;
						IndexOfOfind = S;
						break;
					}
				}
				if(IsFind == true)
				{
					_gradient[IndexOfOfind] = (_gradient[IndexOfOfind] + gradient) / 2; //CubeSimular
					_rTable[IndexOfOfind].Ptr->Next = ConstructRTableParameterNode(R, XP, N, NR);				
					_rTable[IndexOfOfind].Ptr = _rTable[IndexOfOfind].Ptr->Next;
					_rTable[IndexOfOfind].NumberOfParam++;
				}
				else
				{
					_gradient[_countIndex] = gradient;
					_rTable[_countIndex].Head = ConstructRTableParameterNode(R, XP, N, NR);
					_rTable[_countIndex].Ptr = _rTable[_countIndex].Head;
					_rTable[_countIndex].NumberOfParam++;
					_countIndex++;
				}
			}
		}
	}
	//cvReleaseImage(&tempFrame);

	cvReleaseImage(&Frames[0]);
	cvReleaseImage(&Frames[1]);
	cvReleaseImage(&Frames[2]);
	cvReleaseImage(&Frames[3]);
	FrameSequenceToCubesObj.ReleaseBuffer();
	cvReleaseCapture(&Capture);
	return 1;
}


int VolumeBasedGHT::ComputeCubeDataBase(char* videoFileName,char* outputFileName)//建立database的cube資訊
{
	CvCapture* Capture = cvCaptureFromAVI(videoFileName);
	_countIndex = 0;
	_vHeight = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_vWidth = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_vTime = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	_vTime -= (_vTime % 4); // 因為一次取四張frame所以少計算一些frame使能被4整除

	if(_vHeight == 0 || _vWidth == 0 || _vTime == 0)
	{
		cvReleaseCapture(&Capture);
		return -1;
	}
	IplImage* Frames[4];
	Frames[0] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
	Frames[1] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
	Frames[2] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
	Frames[3] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
	Frames[0]->origin = 1;
	Frames[1]->origin = 1;
	Frames[2]->origin = 1;
	Frames[3]->origin = 1;
	//tempFrame = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
	//tempFrame->origin = 1;
	int CountFrame = 0; // 用來紀錄取得之影像個數, 每四張計算一次

	FrameSequenceToCubes FrameSequenceToCubesObj(4, _vHeight, _vWidth);
	
	sprintf(_fileName,"%s.txt",outputFileName);

	FILE* FilePtr = fopen(_fileName, "w"); 

	int _numberOfCube = (_vWidth/4)*(_vHeight/4)*(_vTime);
	fprintf(FilePtr,"%d, %d, %d, %d\n",_numberOfCube,_vWidth,_vHeight,_vTime);
	for(int f = 0; f < _vTime; f++)
	{

		try
		{
			cvCopy(cvQueryFrame(Capture), Frames[CountFrame]);
		}
		catch(cv::Exception e)
		{
			cvReleaseImage(&Frames[0]);
			cvReleaseImage(&Frames[1]);
			cvReleaseImage(&Frames[2]);
			cvReleaseImage(&Frames[3]);
			FrameSequenceToCubesObj.ReleaseBuffer();
			cvReleaseCapture(&Capture);
			return -1;
		}

		CountFrame++;
		if(CountFrame == 4)
		{
			CountFrame = 0;
			FrameSequenceToCubesObj.Transform(Frames, f - 3);
			CubeInformation = FrameSequenceToCubesObj.GetCubeInfo();
			int NumberOfCube = FrameSequenceToCubesObj.GetNumberOfCubeInfo();	
			for(int cube = 0 ; cube < NumberOfCube; cube++)
			{
				fprintf(FilePtr,"%lf, ",CubeInformation[cube].AverageGrayValue);
				fprintf(FilePtr,"%lf, %lf, %lf, ",CubeInformation[cube].COSA,CubeInformation[cube].COSB,CubeInformation[cube].COSR);
				fprintf(FilePtr,"%lf, ",CubeInformation[cube].CubeGradient);
				fprintf(FilePtr,"%lf, %lf, ",CubeInformation[cube].H1,CubeInformation[cube].H2);
				fprintf(FilePtr,"%d, %d, %d, ",CubeInformation[cube].IndexHeight, CubeInformation[cube].IndexTime,CubeInformation[cube].IndexWidth);
				fprintf(FilePtr,"%lf, %lf, %lf, %lf, %lf\n",CubeInformation[cube].L,CubeInformation[cube].M0,CubeInformation[cube].MT,CubeInformation[cube].MX,CubeInformation[cube].MY);
			}
		}
		
	}

	fclose(FilePtr);
	cvReleaseImage(&Frames[0]);
	cvReleaseImage(&Frames[1]);
	cvReleaseImage(&Frames[2]);
	cvReleaseImage(&Frames[3]);
	FrameSequenceToCubesObj.ReleaseBuffer();
	cvReleaseCapture(&Capture);
	return 1;
}

int VolumeBasedGHT::LoadCubeDataBase(char* videoFileName)//載入database的資料
{
	FILE* FilePtr;
	//sprintf(_fileName,"%s.txt",videoFileName);
	if(!(FilePtr = fopen(videoFileName, "r")))
	{
		return -1;
	}

	fscanf(FilePtr,"%d, %d, %d, %d\n",&_vNumberOfCube,&_vWidth,&_vHeight,&_vTime);

	CubeInformation = new CubeInfo[_vNumberOfCube];
	for(int cube = 0 ; cube < _vNumberOfCube; cube++)
	{
		fscanf(FilePtr,"%lf, ",&CubeInformation[cube].AverageGrayValue);
		fscanf(FilePtr,"%lf, %lf, %lf, ",&CubeInformation[cube].COSA,&CubeInformation[cube].COSB,&CubeInformation[cube].COSR);
		fscanf(FilePtr,"%lf, ",&CubeInformation[cube].CubeGradient);
		fscanf(FilePtr,"%lf, %lf, ",&CubeInformation[cube].H1,&CubeInformation[cube].H2);
		fscanf(FilePtr,"%d, %d, %d, ",&CubeInformation[cube].IndexHeight, &CubeInformation[cube].IndexTime,&CubeInformation[cube].IndexWidth);
		fscanf(FilePtr,"%lf, %lf, %lf, %lf, %lf\n",&CubeInformation[cube].L,&CubeInformation[cube].M0,&CubeInformation[cube].MT,&CubeInformation[cube].MX,&CubeInformation[cube].MY);
	}
	fclose(FilePtr);
	return 1;
}

RTableParameter* VolumeBasedGHT::ConstructRTableParameterNode(double r, double* xp, double* n, double* nr)
{
	ParameterNode* ReNode = new RTableParameter;
	ReNode->R = r;
	ReNode->XP[0] = xp[0];
	ReNode->XP[1] = xp[1];
	ReNode->XP[2] = xp[2];

	ReNode->N[0] = n[0];
	ReNode->N[1] = n[1];
	ReNode->N[2] = n[2];

	ReNode->NR[0] = nr[0];
	ReNode->NR[1] = nr[1];
	ReNode->NR[2] = nr[2];

	ReNode->Next = NULL;

	return ReNode;

}

void VolumeBasedGHT::ReleaseRTable()//relase
{
	for(int i = 0; i < SIZE; i++)
	{
		RTableParameter* Parameter = _rTable[i].Head; 
		RTableParameter* DeleteParameter = Parameter;
		for(int j = 0; j < _rTable[i].NumberOfParam; j++)
		{
			Parameter = Parameter->Next;
			delete DeleteParameter;
			DeleteParameter = Parameter;
		}
		_rTable[i].NumberOfParam = 0;
		_rTable[i].Head = NULL;
	}
	for(int i = 0; i < _tTime/4; i++)
		delete _templateCubeGradient[i];
	delete _templateCubeGradient;
	_templateCubeGradient = NULL;
}

void  VolumeBasedGHT::Release()//relase
{
		delete VoteCoordinate;
		VoteCoordinate = NULL;
		delete CubeInformation;
		CubeInformation = NULL;
}

double VolumeBasedGHT::Voting(char* videoFileName,char* CubeFileName,int TopN,char* TempleteFileName,bool Scaling,bool Rotation,bool MutiVote)//利用vbght投票
{


	// 建立票箱

	//FILE* FilePtr;
	//if(!(FilePtr = fopen(CubeFileName, "r")))
	//{
		//return -1;
	//}

//	fscanf(FilePtr,"%d, %d, %d, %d\n",&_vNumberOfCube,&_vWidth,&_vHeight,&_vTime);

	double gradient;
	double sqrtTwo =  sqrt(2.0);
	int Height = _vHeight;
	int Width = _vWidth;
	int NumberOfFrame = _vTime;
	double subGray;

	//SparseMatrix _sparseMatrix;

    int NumberOfCube = (_vWidth/4)*(_vHeight/4);
	//CubeInformation = new CubeInfo[NumberOfCube];
	//CubeInfo* FirstPatchCubeInformation = new CubeInfo[NumberOfCube];
	bool IsFirstPatch = true;

	int RotationAR[36];
	int RotationBR[36];
	for(int i = 0 ; i < 36; i++)
	{
		RotationAR[i] = 0;
		RotationBR[i] = 0;
	}


		// 建立票箱
		for(int S = 0 ; S < 3; S++)
		{
			for(int AR = 0 ; AR < 2 ; AR++)
			{
				for(int BR = 0 ; BR < 2 ; BR++)
				{
					_votingTable[S][AR][BR] = new int**[Height];
					for(int c = 0; c < Height; c++)
					{
						_votingTable[S][AR][BR][c] = new int*[Width];
						for(int r = 0; r < Width; r++)
						{
							_votingTable[S][AR][BR][c][r] = new int[NumberOfFrame];
							for(int t = 0; t < NumberOfFrame; t++)
								_votingTable[S][AR][BR][c][r][t] = 0;
						}
					}
				}
			}
		}



			for(int i = 0; i < NumberOfCube; i++)
			{
				subGray = abs(CubeInformation[i].H1 - CubeInformation[i].H2);
				if(((CubeInformation[i].L <= sqrtTwo) && (CubeInformation[i].L >= (-1 * sqrtTwo))) && (subGray > 80))
				{
					// 計算 R-Table Index
					double AverageGray = 0;
					// 計算八個方向
					double CountDir = 0;
					int IH = CubeInformation[i].IndexHeight;
					int IW = CubeInformation[i].IndexWidth;
					
					for(int ih = IH - 4; ih <= IH + 4; ih += 4)
					{
						for(int iw = IW - 4; iw <= IW + 4; iw += 4)
						{
							if(ih == IH && iw == IW)
								continue;
							int CubeInformationIndex = ih + iw / 4;
							if(CubeInformationIndex >= 0 && CubeInformationIndex < _vNumberOfCube)
							{
								AverageGray += CubeInformation[CubeInformationIndex].AverageGrayValue;
								CountDir++;
							}
						}
					}
					if(CountDir == 0)
						CountDir = 1;
					
					AverageGray /= CountDir;

					// END 計算八個方向
					//double Indexd = 100*(abs(CubeInformation[i].H2 - CubeInformation[i].H1) / AverageGray);

					// END 計算 R-Table Index
					if(AverageGray == 0)
						AverageGray = 1;
					gradient = abs(CubeInformation[i].H2 - CubeInformation[i].H1) / AverageGray;
					if(gradient >= _countIndex)
						continue;
					//int CBug = 0;
				
					for(int Index = 0 ; Index < _countIndex ; Index++)
					{
						RTableParameter* Parameter = _rTable[Index].Head; 

						if(abs(_gradient[Index] - gradient) <= 0.01)
						{
							//CBug++;
							for(int j = 0; j < _rTable[Index].NumberOfParam; j++)
							{
								double XPCV[3] = {CubeInformation[i].IndexWidth + 2, CubeInformation[i].IndexHeight + 2, CubeInformation[i].IndexTime + 2}; // Cube中心位置
								double NV[3] = {CubeInformation[i].COSA, CubeInformation[i].COSB, CubeInformation[i].COSR};
								double* NT = Parameter->N;
								double* NR = Parameter->NR;

								double dT = sqrt(NT[1] * NT[1] + NT[2] * NT[2]);
								double dV = sqrt(NV[1] * NV[1] + NV[2] * NV[2]);
								double AlphaV = 0;
								double BataV = 0;
								double AlphaT= 0;
								double BataT = 0;

								if(Rotation == true)
								{
									AlphaV = atan(NV[2]/NV[1]);
									BataV = atan(NV[0]/dV);
									AlphaT= atan(NT[2]/NT[1]);
									BataT = atan(NT[0]/dT);
								}

								double CosBTBV = cos(BataT-BataV);
								double SinAT = sin(AlphaT);
								double SinBTBV = sin(BataT-BataV);
								double CosAT = cos(AlphaT);
								double SinAV = sin(AlphaV);
								double CosAV = cos(AlphaV);
								double FinalMat[3];
 
								double AR =  (AlphaT * (180/3.14)) - (AlphaV * (180/3.14)) ;
								double BR =  (BataT * (180/3.14)) - (BataV * (180/3.14)) ;

								FinalMat[0] = NR[0] * CosBTBV + NR[1] * SinBTBV * SinAT + NR[2] * SinBTBV * CosAT;
								FinalMat[1] = NR[0] * SinAV * (-1*SinBTBV) + NR[1] * (CosAV * CosAT + SinAV * CosBTBV * SinAT) + NR[2] * (CosAV*(-1*SinAT) + SinAV *CosBTBV * CosAT);
								FinalMat[2] = NR[0] * CosAV * (-1*SinBTBV) + NR[1] * ((-1*SinAV) * CosAT + CosAV * CosBTBV * SinAT) + NR[2] * ((-1*SinAV) * (-1*SinAT) + CosAV * CosBTBV * CosAT);

								// 投票開始
								double XPV[3] = {0}; // 計算平面上座標
								XPV[0] = XPCV[0] + CubeInformation[i].L * NV[0];
								XPV[1] = XPCV[1] + CubeInformation[i].L * NV[1];
								XPV[2] = XPCV[2] + CubeInformation[i].L * NV[2];
								double rPT = Parameter->R;

								int countS;
								double Star;
								double E;

								if(Scaling == true)
								{
									countS = 0;
									Star = 0.5;
									E = 2;
								}
								else
								{
									countS = 1;
									Star = 1;
									E = 1;
								}

								for(double S = Star; S <= E; S+=0.5)
								{
									if(S == 1.5)
										continue;
									int Tar[3] = {0};
									Tar[0] =  XPV[0] + (int)( S *rPT *  FinalMat[0]);
									Tar[1] =  XPV[1] + (int)( S *rPT *  FinalMat[1]);
									Tar[2] =  XPV[2] + (int)( S *rPT *  FinalMat[2]);

									int Tar0 = Tar[0];
									int Tar1 = Tar[1];
									int Tar2 = Tar[2];

									if(AR < 0)
									{
									   AR+=360;
									}

									if(BR < 0)
									{
										BR+=360;
									}

									int IndexAR = (int)(AR/10+0.5)%36;
									int IndexBR = (int)(BR/10+0.5)%36;
									if(Tar[0] >= 0 && Tar[1] >= 0 && Tar[2] >= 0)
									{
										if((Tar[0] < Width-1 && Tar[1] < Height-1 && Tar[2] < NumberOfFrame-1) && (Tar[0] >=1  && Tar[1] >=1 && Tar[2] >=1) && (AR >= 0 && AR <= 10) && (BR >= 0 && BR <= 10))
										{
											if(MutiVote == true)
											{
												/*_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0-1,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0-1,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0-1,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0+1,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0+1,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1-1,Tar0+1,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0-1,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0-1,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0-1,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0+1,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0+1,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1,Tar0+1,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0-1,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0-1,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0-1,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0,Tar2+1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0+1,Tar2-1);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0+1,Tar2);
												_sparseMatrix.Add(countS,(int)(AR/10+0.5),(int)(BR/10+0.5),Tar1+1,Tar0+1,Tar2+1);*/

												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]-1][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]-1][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]-1][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]+1][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]+1][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]-1][Tar[0]+1][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]-1][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]-1][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]-1][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]+1][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]+1][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]+1][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]-1][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]-1][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]-1][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]][Tar[2]+1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]+1][Tar[2]-1]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]+1][Tar[2]]++;
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]+1][Tar[0]+1][Tar[2]+1]++;

											}
											else
											{
												//_sparseMatrix.Add(countS,IndexAR,IndexBR,Tar1,Tar0,Tar2);
												_votingTable[countS][(int)(AR/10+0.5)][(int)(BR/10+0.5)][Tar[1]][Tar[0]][Tar[2]]++;
											}

											RotationAR[IndexAR]++;
											RotationBR[IndexBR]++;

										}
									}

									if(Scaling == true)
									{
										countS++;
									}
								}
								Parameter = Parameter->Next;
							}// END for(int j = 0; j < _rTable[Index].NumberOfParam; j++)
						}
						//free(RTableParameter);
					}

				}//END if(CubeInformation[i].L) 
			}

	//VoteCoordinate = _sparseMatrix.GetTopN(TopN);
	VoteCoordinate = TopNSort(TopN);
	//DrawImage(videoFileName,VoteCoordinate,TopN,TempleteFileName);
	//Similar = new double[TopN];
	int isFairFile = FindTopSimular(videoFileName,VoteCoordinate,TopN,0); 
	DrawImage(videoFileName,VoteCoordinate,TopN,TempleteFileName);

	/*char FileName[300];
	sprintf(FileName,"Test\\simular\\%s.txt",TempleteFileName);
	FilePtr= fopen(FileName,"a");

	for(int current = 0;current < TopN;current++)
	{
		fprintf(FilePtr, "%s : %lf\n", videoFileName, Similar[current]);
	}

	fclose(FilePtr);*/

	/*FilePtr= fopen("Test\\simular\\ALLRotationAR.txt","w");

	for(int current = 0;current < 36;current++)
	{
		fprintf(FilePtr, "%d ", RotationAR[current]);
	}

	fclose(FilePtr);

	FilePtr= fopen("Test\\simular\\ALLRotationBR.txt","w");

	for(int current = 0;current < 36;current++)
	{
		fprintf(FilePtr, "%d ", RotationBR[current]);
	}

	fclose(FilePtr);

	_sparseMatrix.countSAB(_vHeight,_vWidth,_vTime,1.0,10);
	//==========================================
	_sparseMatrix.Release();*/

	if(isFairFile < TopN)
		return VoteCoordinate[isFairFile].Similar;
	else
		return -1;

}


ImagePoint *VolumeBasedGHT::GetVoteCoordinate()
{
	return VoteCoordinate;
}

int VolumeBasedGHT::FindTopSimular(char *FileName,ImagePoint *VoteCoordinate,int N,int Feature) //排序並找出最相似的前幾名的投票點
{
	//CvCapture *Capture;
       int isFairFile = 0;
	for(int i = 0 ; i <  N; i++)
	{
		//Capture = cvCaptureFromAVI(FileName);
		VoteCoordinate[i].Similar = ComputeSimilar(VoteCoordinate[i].x, VoteCoordinate[i].y, VoteCoordinate[i].t, VoteCoordinate[i].scaling,VoteCoordinate[i].Arotation,FileName);
		sprintf(VoteCoordinate[i].FileName,"%s",FileName);

		if(VoteCoordinate[i].Similar == -1)
			isFairFile++;
		//cvReleaseCapture(&Capture);
	}

	double tempSim,tempScaling,tempAR,tempBR;
	for(int i = 0 ; i < N; i++)
	{
		for(int j = i ; j < N ; j++)
		{
			if(VoteCoordinate[i].Similar > VoteCoordinate[j].Similar)
			{
				tempSim = VoteCoordinate[i].Similar;
				VoteCoordinate[i].Similar = VoteCoordinate[j].Similar;
				VoteCoordinate[j].Similar = tempSim;

				VoteCoordinate[i].x ^= VoteCoordinate[j].x;
				VoteCoordinate[j].x ^= VoteCoordinate[i].x;
				VoteCoordinate[i].x ^= VoteCoordinate[j].x;

				VoteCoordinate[i].y ^= VoteCoordinate[j].y;
				VoteCoordinate[j].y ^= VoteCoordinate[i].y;
				VoteCoordinate[i].y ^= VoteCoordinate[j].y;

				VoteCoordinate[i].t ^= VoteCoordinate[j].t;
				VoteCoordinate[j].t ^= VoteCoordinate[i].t;
				VoteCoordinate[i].t ^= VoteCoordinate[j].t;

				tempScaling = VoteCoordinate[i].scaling;
				VoteCoordinate[i].scaling = VoteCoordinate[j].scaling;
				VoteCoordinate[j].scaling = tempScaling;

				tempAR = VoteCoordinate[i].Arotation;
				VoteCoordinate[i].Arotation = VoteCoordinate[j].Arotation;
				VoteCoordinate[j].Arotation = tempAR;

				tempBR = VoteCoordinate[i].Brotation;
				VoteCoordinate[i].Brotation = VoteCoordinate[j].Brotation;
				VoteCoordinate[j].Brotation = tempBR;

			}
		}
	}

	return isFairFile;
}

void VolumeBasedGHT::DrawImage(char *FileName,ImagePoint *VotePoint,int N,char* TempleteFileName)  //輸出抓取的圖
{
	CvCapture *Capture = cvCaptureFromAVI(FileName);
	
	
	CvScalar Color;// = CV_RGB(255,0,0);
 	int Thickness=2;
    int Shift=0;

	int *countF = new int[_vTime];
	for(int f = 0; f < _vTime; f++)
	{
		countF[f] = 0;
	}
    
	for(int f = 0; f < _vTime; f++)
	{

		IplImage* Img = cvQueryFrame(Capture);
		for(int p = 0 ; p < N ; p++)
		{
			double scaling = VotePoint[p].scaling;
            int Vote =VotePoint[p].Vote;
			if( VotePoint[p].t == f)
			{
				Color = CV_RGB(255,0,0);
				cvRectangle(Img, cvPoint(VotePoint[p].x - (_tWidth*scaling/2), VotePoint[p].y - (_tHeight*scaling/2)), cvPoint(VotePoint[p].x + (_tWidth*scaling/2), VotePoint[p].y + (_tHeight*scaling/2)), Color, Thickness, CV_AA, Shift);
				cvRectangle(Img, cvPoint(VotePoint[p].x - 3, VotePoint[p].y - 3), cvPoint(VotePoint[p].x + 3, VotePoint[p].y + 3), Color, Thickness, CV_AA, Shift);

				char OutputFileFolder[300];
				sprintf(OutputFileFolder, "Test\\%s_%d_%dG_%d.jpg",TempleteFileName,p,f,countF[f]);


				try
				{
					cvSaveImage(OutputFileFolder, Img);	
				}
				catch(cv::Exception e)
				{
					delete countF;
					countF = NULL;
					cvReleaseCapture(&Capture);
					
				}			
			}
			else
			{
				char OutputFileFolder[300];
				sprintf(OutputFileFolder, "Test\\%s_%d_%dG_%d.jpg",TempleteFileName,p,f,countF[f]);
				try
				{
					cvSaveImage(OutputFileFolder, Img);	
				}
				catch(cv::Exception e)
				{
					delete countF;
					countF = NULL;
					cvReleaseCapture(&Capture);
					
				}	
			}
		}
		//cvReleaseImage(&Img);
		
	}
	delete countF;
	countF = NULL;
	cvReleaseCapture(&Capture);
}



ImagePoint* VolumeBasedGHT::TopNSort(int N) //已移到sqarseMatrix
{
	ImagePoint *VoteCoordinate = new ImagePoint[N];
	//ImagePoint tempCoordinate;
	int CountTopTen = 0;


	int countS = 0;
	for(double S = 0.5 ; S <= 2; S += 0.5)
	{
		if(S == 1.5)
			continue;
		for(int AR = 0; AR < 2; AR++)
		{
			for(int BR = 0; BR < 2; BR++)
			{
				for(int t = 0; t < _vTime; t++)
				{
					for(int c = 0; c < _vHeight; c++)
					{
						for(int r = 0; r < _vWidth; r++)
						{
							if(CountTopTen < N) // 塞滿前十名
							{
								VoteCoordinate[CountTopTen].Vote =  _votingTable[countS][AR][BR][c][r][t];
								VoteCoordinate[CountTopTen].x = r;
								VoteCoordinate[CountTopTen].y = c;
								VoteCoordinate[CountTopTen].t = t;
								VoteCoordinate[CountTopTen].scaling = S;
								VoteCoordinate[CountTopTen].Arotation = AR*10;
								VoteCoordinate[CountTopTen].Brotation = BR*10;
								CountTopTen++;
							}
							else if(CountTopTen == N) // 排序一次
							{
								CountTopTen++;
								double tempScaling,tempAR,tempBR;

								for(int i = 0; i < N; i++)
								{
									for(int j = i; j < N; j++)
									{
										if(VoteCoordinate[i].Vote < VoteCoordinate[j].Vote)
										{
											VoteCoordinate[i].Vote ^= VoteCoordinate[j].Vote;
											VoteCoordinate[j].Vote ^= VoteCoordinate[i].Vote;
											VoteCoordinate[i].Vote ^= VoteCoordinate[j].Vote;

											VoteCoordinate[i].x ^= VoteCoordinate[j].x;
											VoteCoordinate[j].x ^= VoteCoordinate[i].x;
											VoteCoordinate[i].x ^= VoteCoordinate[j].x;

											VoteCoordinate[i].y ^= VoteCoordinate[j].y;
											VoteCoordinate[j].y ^= VoteCoordinate[i].y;
											VoteCoordinate[i].y ^= VoteCoordinate[j].y;

											VoteCoordinate[i].t ^= VoteCoordinate[j].t;
											VoteCoordinate[j].t ^= VoteCoordinate[i].t;
											VoteCoordinate[i].t ^= VoteCoordinate[j].t;

											tempScaling = VoteCoordinate[i].scaling;
											VoteCoordinate[i].scaling = VoteCoordinate[j].scaling;
											VoteCoordinate[j].scaling = tempScaling;

											tempAR = VoteCoordinate[i].Arotation;
											VoteCoordinate[i].Arotation = VoteCoordinate[j].Arotation;
											VoteCoordinate[j].Arotation = tempAR;

											tempBR = VoteCoordinate[i].Brotation;
											VoteCoordinate[i].Brotation = VoteCoordinate[j].Brotation;
											VoteCoordinate[j].Brotation = tempBR;

										}
									}
								}

							}
							else // 一一比較是否屬於前十名
							{
								int i;
								double tempScaling,tempAR,tempBR;

								for(i = N-1; i >= 0; i--)
								{
									if(_votingTable[countS][AR][BR][c][r][t] > 1)
									{
										int a = _votingTable[countS][AR][BR][c][r][t];
										int b = 0;
									}

									if(_votingTable[countS][AR][BR][c][r][t] < VoteCoordinate[i].Vote)
										break;
								}
								i++;
								if(i < 10)
								{
									for(int j = N-1; j > i; j--)
									{
										VoteCoordinate[j].Vote = VoteCoordinate[j-1].Vote;
										VoteCoordinate[j].x = VoteCoordinate[j-1].x;
										VoteCoordinate[j].y = VoteCoordinate[j-1].y;
										VoteCoordinate[j].t = VoteCoordinate[j-1].t;

										VoteCoordinate[j].scaling = VoteCoordinate[j-1].scaling;
										VoteCoordinate[j].Arotation = VoteCoordinate[j-1].Arotation;
										VoteCoordinate[j].Brotation = VoteCoordinate[j-1].Brotation;

									}
									VoteCoordinate[i].Vote = _votingTable[countS][AR][BR][c][r][t];
									VoteCoordinate[i].x = r;
									VoteCoordinate[i].y = c;
									VoteCoordinate[i].t = t;
									VoteCoordinate[i].scaling = S;
									VoteCoordinate[i].Arotation = AR * 10;
									VoteCoordinate[i].Brotation = BR * 10;
								}
							}
						}
					}
				}
			}
		}
		countS++;
	} // for(double S = 0.5 ; S <= 2; S += 0.5)

	return VoteCoordinate;
}

void VolumeBasedGHT::ReleaseVoteTable() //無用
{

	for(int S = 0; S < 3 ; S++)
	{
		for(int AR = 0 ; AR < 2; AR++)
		{
			for(int BR = 0 ; BR < 2; BR++)
			{
				for(int c = 0; c < _vHeight; c++)
				{
					for(int r = 0; r < _vWidth; r++)
					{
						delete _votingTable[S][AR][BR][c][r];
					}
					delete _votingTable[S][AR][BR][c];
				}
				delete _votingTable[S][AR][BR];
			}
		}
	}
}

double VolumeBasedGHT::ComputeSimilar(int CX, int CY, int CZ , double scaling,int Rotation,char* FileName) //在找出視訊序列中最相似的位置並計算其相似度
{
	double SimilarValue = 0;
	
	double VideoNorm = 0, TempleteNorm = 0;
	double* VideoInfo;
	double* TempleteInfo;

	// 在template和資料庫中將ROI挖出
	int RoiX, RoiY, RoiZ, RoiW, RoiH, RoiT;

	if(CX > _vWidth || CY > _vHeight || CZ > _vTime)
	{
		return -1;
	}

	int RX = CX - (_tWidth * scaling / 2);
	int RY = CY - (_tHeight * scaling / 2);
	int RT = CZ - _tTime  / 2;

	if(RX < 0)
	{
		RoiX = 0;
		RoiW = (_tWidth* scaling) + RX;
	}
	else
	{
		RoiX = RX;
		RoiW = _tWidth* scaling;
	}

	if(RY < 0)
	{
		RoiY = 0;
		RoiH = (_tHeight* scaling) + RY;
	}
	else
	{
		RoiY = RY;
		RoiH = _tHeight* scaling;
	}
	if(RT < 0)
	{
		RoiZ = 0;
		RoiT = _tTime + RT;
	}
	else
	{
		RoiZ = RT;
		RoiT = _tTime;
	}

	if(RoiX + RoiW > _vWidth)
	{

		RoiW = RoiW - (RoiX + RoiW - _vWidth);
	}
	if(RoiY + RoiH > _vHeight)
	{

		RoiH = RoiH - (RoiY + RoiH - _vHeight);
	}

	if(RoiZ + RoiT > _vTime)
	{

		RoiT = RoiT - (RoiZ + RoiT - _vTime);
	}
	
	if(RoiX % 4 != 0)
		RoiX -= RoiX % 4;
	if(RoiY % 4 != 0)
		RoiY -= RoiY % 4;
	if(RoiZ % 4 != 0)
		RoiZ -= RoiZ % 4;

	if(RoiW % 4 != 0)
	{
		int tempW = RoiW - (4 - RoiW % 4);	
		//if(tempW <= _vWidth)
			//RoiW += 4 - RoiW % 4;
		//else
			RoiW =tempW;

	}

	if(RoiH % 4 != 0)
	{
		int tempH = RoiH - (4 - RoiH % 4);
		//if(tempH <= _vHeight )
			//RoiH += 4 - RoiH % 4;
		//else
			RoiH =tempH;
	}
	if(RoiT % 4 != 0)
	{
		int tempT = RoiT - (4 - RoiT % 4);
		//if(tempT <= _vTime)
			//RoiT += 4 - RoiT % 4;
		//else
			RoiT =tempT;
	}


	if(_tWidth == 0 || _tHeight == 0 || _tTime == 0 || RoiW <= 0 || RoiH <=0 || RoiT <= 0)
	{
		return -1;
	}

	int StartX;
	int StartY;
	int StartZ;

	int NumberOfCube = (int)(((RoiW/scaling)/4+1)*((RoiH/scaling)/4+1)*(RoiT/4+1));
	VideoInfo = new double[NumberOfCube];
	TempleteInfo = new double[NumberOfCube];


	for(int i = 0 ; i < NumberOfCube; i++ )
	{
		VideoInfo[i] = 0;
		TempleteInfo[i] = 0;
	}

	if(RX >= 0)
		StartX = 0;
	else
		StartX =CX - RX;
	if(RY >= 0)
		StartY = 0;
	else
		StartY = CY - RY;

	if(RT >= 0)
		StartZ = 0;
	else
		StartZ = CZ - RT;


//==================================================================開始計算相似度
	if(Rotation == 0 && scaling == 1)  //處理未旋轉未Scaling的狀態
	{
		/*for(int f = RoiZ; f < RoiZ + RoiT; f+=4)
		{
			if(f/4 >= _vTime/4)
				break;
			for(int y = RoiY; y < RoiY + RoiH; y += 4)
			{
				for(int x = RoiX; x < RoiX + RoiW; x += 4)
				{
					int FinalIndex = (int)(x / 4) + (int)(y / 4) * (int)(_vWidth / 4) + (int)(f / 4)*(int)(_vWidth / 4)*(int)(_vHeight / 4);

					if(FinalIndex >= _vNumberOfCube)
					{
						delete VideoInfo;
						VideoInfo = NULL;
						delete TempleteInfo;
						TempleteInfo = NULL;
						return -1;
					}
					VideoInfo[(int)VideoNorm] = CubeInformation[FinalIndex].CubeGradient;
					VideoNorm++;
				}
			}
		}*/
		FrameSequenceToCubes FrameSequenceToCubesObj(4, RoiH, RoiW);

		IplImage* Frames[4];
		Frames[0] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[1] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[2] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[3] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);

		int CountFrame = 0;

		CvCapture* Capture = cvCaptureFromAVI(FileName);

		for(int f = 0; f < RoiZ ; f++)
		{
			try
			{
				cvCopy( cvQueryFrame(Capture), Frames[CountFrame]);
			}
			catch(cv::Exception e)
			{
				cvReleaseImage(&Frames[0]);
				cvReleaseImage(&Frames[1]);
				cvReleaseImage(&Frames[2]);
				cvReleaseImage(&Frames[3]);
				FrameSequenceToCubesObj.ReleaseBuffer();
				cvReleaseCapture(&Capture);
				delete VideoInfo;
				VideoInfo = NULL;
				delete TempleteInfo;
				TempleteInfo = NULL;
				return -1;
			}
		}
	

		for(int f = RoiZ; f < RoiZ + RoiT; f++)
		{		
			try
			{
				cvCopy( cvQueryFrame(Capture), Frames[CountFrame]);
			}
			catch(cv::Exception e)
			{
				cvReleaseImage(&Frames[0]);
				cvReleaseImage(&Frames[1]);
				cvReleaseImage(&Frames[2]);
				cvReleaseImage(&Frames[3]);
				FrameSequenceToCubesObj.ReleaseBuffer();
				cvReleaseCapture(&Capture);
				delete VideoInfo;
				VideoInfo = NULL;
				delete TempleteInfo;
				TempleteInfo = NULL;
				return -1;
			}

			CountFrame++;
  
			if(CountFrame == 4)
			{
				CountFrame = 0;
				IplROI ROI;
				CvRect Rect;
				Rect = cvRect(RoiX, RoiY, RoiW, RoiH); //??
				ROI = cvRectToROI(Rect, 0);
				Frames[0]->roi = &ROI;
				Frames[1]->roi = &ROI;
				Frames[2]->roi = &ROI;
				Frames[3]->roi = &ROI;

				IplImage* RoiImage[4];
				RoiImage[0] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				RoiImage[1] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3); 
				RoiImage[2] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				RoiImage[3] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				/*RoiImage[0]->origin = 1;
				RoiImage[1]->origin = 1;
				RoiImage[2]->origin = 1;
				RoiImage[3]->origin = 1;*/
				cvCopy(Frames[0], RoiImage[0]);
				cvCopy(Frames[1], RoiImage[1]);
				cvCopy(Frames[2], RoiImage[2]);
				cvCopy(Frames[3], RoiImage[3]);
				
				/*for(int ROIF = 0 ; ROIF < 4; ROIF++)
				{
					cvNamedWindow ("src", 1);
					cvShowImage ("src", Frames[ROIF]);
					cvNamedWindow ("dst", 1);
					cvShowImage ("dst", RoiImage[ROIF]);
				}*/


				FrameSequenceToCubesObj.Transform(RoiImage, f-3);
				CubeInfo* cubeInfo = FrameSequenceToCubesObj.GetCubeInfo();

				int TNumberOfCube = FrameSequenceToCubesObj.GetNumberOfCubeInfo();

				for(int cube = 0 ; cube < TNumberOfCube; cube++)
				{
					VideoInfo[(int)VideoNorm] = cubeInfo[cube].CubeGradient;
					VideoNorm++;
				}

				Frames[0]->roi = NULL;
				Frames[1]->roi = NULL;
				Frames[2]->roi = NULL;
				Frames[3]->roi = NULL;

				cvReleaseImage(&RoiImage[0]);
				cvReleaseImage(&RoiImage[1]);
				cvReleaseImage(&RoiImage[2]);
				cvReleaseImage(&RoiImage[3]);
			}


		}
		cvReleaseImage(&Frames[0]);
		cvReleaseImage(&Frames[1]);
		cvReleaseImage(&Frames[2]);
		cvReleaseImage(&Frames[3]);
		cvReleaseCapture(&Capture);
		FrameSequenceToCubesObj.ReleaseBuffer();
	}
	else if(Rotation > 0 && scaling == 1)//處理有旋轉但未Scaling的狀態
	{
		FrameSequenceToCubes FrameSequenceToCubesObj(4, RoiH, RoiW);

		IplImage* Frames[4];
		IplImage* _subFrames[4];
		Frames[0] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[1] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[2] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[3] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		_subFrames[0] =  cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
		_subFrames[1] =  cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
		_subFrames[2] =  cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
		_subFrames[3] =  cvCreateImage(cvSize(RoiW, RoiH), 8, 3);


		/*Frames[0]->origin = 1;
		Frames[1]->origin = 1;
		Frames[2]->origin = 1;
		Frames[3]->origin = 1;
		_subFrames->origin = 1;*/
		int CountFrame = 0;
		//NumberOfCube = (int)((RoiW/4+1)*(RoiH/4+1)*(RoiT/4+1));

		CvCapture* Capture = cvCaptureFromAVI(FileName);

		for(int f = 0; f < RoiZ ; f++)
		{
			try
			{
				cvCopy( cvQueryFrame(Capture), Frames[CountFrame]);
			}
			catch(cv::Exception e)
			{
				cvReleaseImage(&Frames[0]);
				cvReleaseImage(&Frames[1]);
				cvReleaseImage(&Frames[2]);
				cvReleaseImage(&Frames[3]);
				cvReleaseImage(&_subFrames[0]);
				cvReleaseImage(&_subFrames[1]);
				cvReleaseImage(&_subFrames[2]);
				cvReleaseImage(&_subFrames[3]);
				FrameSequenceToCubesObj.ReleaseBuffer();
				cvReleaseCapture(&Capture);
				delete VideoInfo;
				VideoInfo = NULL;
				delete TempleteInfo;
				TempleteInfo = NULL;
				return -1;
			}
		}
	

		for(int f = RoiZ; f < RoiZ + RoiT; f++)
		{		
			try
			{
				cvCopy( cvQueryFrame(Capture), Frames[CountFrame]);
			}
			catch(cv::Exception e)
			{
				cvReleaseImage(&Frames[0]);
				cvReleaseImage(&Frames[1]);
				cvReleaseImage(&Frames[2]);
				cvReleaseImage(&Frames[3]);
				cvReleaseImage(&_subFrames[0]);
				cvReleaseImage(&_subFrames[1]);
				cvReleaseImage(&_subFrames[2]);
				cvReleaseImage(&_subFrames[3]);
				FrameSequenceToCubesObj.ReleaseBuffer();
				cvReleaseCapture(&Capture);
				delete VideoInfo;
				VideoInfo = NULL;
				delete TempleteInfo;
				TempleteInfo = NULL;
				return -1;
			}

			CountFrame++;
  
			if(CountFrame == 4)
			{
				CountFrame = 0;
				IplROI ROI;
				CvRect Rect;
				Rect = cvRect(RoiX, RoiY, RoiW, RoiH); //??
				ROI = cvRectToROI(Rect, 0);
				Frames[0]->roi = &ROI;
				Frames[1]->roi = &ROI;
				Frames[2]->roi = &ROI;
				Frames[3]->roi = &ROI;

				IplImage* RoiImage[4];
				RoiImage[0] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				RoiImage[1] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3); 
				RoiImage[2] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				RoiImage[3] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				/*RoiImage[0]->origin = 1;
				RoiImage[1]->origin = 1;
				RoiImage[2]->origin = 1;
				RoiImage[3]->origin = 1;*/
				cvCopy(Frames[0], RoiImage[0]);
				cvCopy(Frames[1], RoiImage[1]);
				cvCopy(Frames[2], RoiImage[2]);
				cvCopy(Frames[3], RoiImage[3]);



				 int delta = 1;
				 int angle = Rotation * -1;
				 int opt = 0;		// 1： 旋轉加縮放
				  // 0:  僅僅旋轉
				 double factor;
				
				 for(int ROIF = 0 ; ROIF < 4; ROIF++)
				 {
					  float m[6];
					  // Matrix m looks like:
					  //
					  // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
					  // [ m3  m4  m5 ]       [ A21  A22   b2 ]
					  //
					  CvMat M = cvMat (2, 3, CV_32F, m);
					  int w = RoiW;
					  int h = RoiH;
					  if (opt)		// 旋轉加縮放
						factor = (cos (angle * CV_PI / 180.) + 1.0) * 2;
					  else			//  僅僅旋轉
						factor = 1;
					  m[0] = (float) (factor * cos (-angle * 2 * CV_PI / 180.));
					  m[1] = (float) (factor * sin (-angle * 2 * CV_PI / 180.));
					  m[3] = -m[1];
					  m[4] = m[0];
					  // 將旋轉中心移至圖像中間
					  m[2] = w * 0.5f;
					  m[5] = h * 0.5f;
					  //  dst(x,y) = A * src(x,y) + b
					  cvZero (_subFrames[ROIF]);
					  cvGetQuadrangleSubPix (RoiImage[ROIF],_subFrames[ROIF], &M);
					 // cvNamedWindow ("src", 1);
					 // cvShowImage ("src", RoiImage[ROIF]);
					 // cvNamedWindow ("dst", 1);
					 // cvShowImage ("dst", _subFrames[ROIF]);
					 // cvWaitKey (50);
				 }



				FrameSequenceToCubesObj.Transform(_subFrames, f-3);
				CubeInfo* cubeInfo = FrameSequenceToCubesObj.GetCubeInfo();

				int TNumberOfCube = FrameSequenceToCubesObj.GetNumberOfCubeInfo();

				for(int cube = 0 ; cube < TNumberOfCube; cube++)
				{
					VideoInfo[(int)VideoNorm] = cubeInfo[cube].CubeGradient;
					VideoNorm++;
				}

				Frames[0]->roi = NULL;
				Frames[1]->roi = NULL;
				Frames[2]->roi = NULL;
				Frames[3]->roi = NULL;

				cvReleaseImage(&RoiImage[0]);
				cvReleaseImage(&RoiImage[1]);
				cvReleaseImage(&RoiImage[2]);
				cvReleaseImage(&RoiImage[3]);
			}


		}
		cvReleaseImage(&Frames[0]);
		cvReleaseImage(&Frames[1]);
		cvReleaseImage(&Frames[2]);
		cvReleaseImage(&Frames[3]);
		cvReleaseImage(&_subFrames[0]);
		cvReleaseImage(&_subFrames[1]);
		cvReleaseImage(&_subFrames[2]);
		cvReleaseImage(&_subFrames[3]);
		cvReleaseCapture(&Capture);
		FrameSequenceToCubesObj.ReleaseBuffer();
	}
	else if(scaling != 1 && Rotation == 0) //處理未旋轉但有Scaling的狀態
	{


		CvSize dst_cvsize;			//目標圖像尺寸
		dst_cvsize.width = RoiW/scaling;		//目標圖像的寬為源圖象寬的scale倍
		dst_cvsize.height = RoiH/scaling;	//目標圖像的高為源圖象高的scale倍

		FrameSequenceToCubes FrameSequenceToCubesObj(4, dst_cvsize.height, dst_cvsize.width);

		IplImage* Frames[4];
		IplImage* _subFrames[4];
		Frames[0] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[1] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[2] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);
		Frames[3] = cvCreateImage(cvSize(_vWidth, _vHeight), 8, 3);

		_subFrames[0] =  cvCreateImage(cvSize(dst_cvsize.width, dst_cvsize.height), 8, 3);
		_subFrames[1] =  cvCreateImage(cvSize(dst_cvsize.width, dst_cvsize.height), 8, 3);
		_subFrames[2] =  cvCreateImage(cvSize(dst_cvsize.width, dst_cvsize.height), 8, 3);
		_subFrames[3] =  cvCreateImage(cvSize(dst_cvsize.width, dst_cvsize.height), 8, 3);


		/*Frames[0]->origin = 1;
		Frames[1]->origin = 1;
		Frames[2]->origin = 1;
		Frames[3]->origin = 1;
		_subFrames->origin = 1;*/
		int CountFrame = 0;
		//NumberOfCube = (int)((dst_cvsize.width/4+1)*(dst_cvsize.height/4+1)*(RoiT/4+1));

		CvCapture* Capture = cvCaptureFromAVI(FileName);

		for(int f = 0; f < RoiZ ; f++)
		{
			try
			{
				cvCopy( cvQueryFrame(Capture), Frames[CountFrame]);
			}
			catch(cv::Exception e)
			{
				cvReleaseImage(&Frames[0]);
				cvReleaseImage(&Frames[1]);
				cvReleaseImage(&Frames[2]);
				cvReleaseImage(&Frames[3]);
				cvReleaseImage(&_subFrames[0]);
				cvReleaseImage(&_subFrames[1]);
				cvReleaseImage(&_subFrames[2]);
				cvReleaseImage(&_subFrames[3]);
				FrameSequenceToCubesObj.ReleaseBuffer();
				cvReleaseCapture(&Capture);
				delete VideoInfo;
				VideoInfo = NULL;
				delete TempleteInfo;
				TempleteInfo = NULL;
				return -1;
			}
		}
	

		for(int f = RoiZ; f < RoiZ + RoiT; f++)
		{		
			try
			{
				cvCopy( cvQueryFrame(Capture), Frames[CountFrame]);
			}
			catch(cv::Exception e)
			{
				cvReleaseImage(&Frames[0]);
				cvReleaseImage(&Frames[1]);
				cvReleaseImage(&Frames[2]);
				cvReleaseImage(&Frames[3]);
				cvReleaseImage(&_subFrames[0]);
				cvReleaseImage(&_subFrames[1]);
				cvReleaseImage(&_subFrames[2]);
				cvReleaseImage(&_subFrames[3]);
				FrameSequenceToCubesObj.ReleaseBuffer();
				cvReleaseCapture(&Capture);
				delete VideoInfo;
				VideoInfo = NULL;
				delete TempleteInfo;
				TempleteInfo = NULL;
				return -1;
			}

			CountFrame++;
  
			if(CountFrame == 4)
			{
				CountFrame = 0;
				IplROI ROI;
				CvRect Rect;
				Rect = cvRect(RoiX, RoiY, RoiW, RoiH); //??
				ROI = cvRectToROI(Rect, 0);
				Frames[0]->roi = &ROI;
				Frames[1]->roi = &ROI;
				Frames[2]->roi = &ROI;
				Frames[3]->roi = &ROI;

				IplImage* RoiImage[4];
				RoiImage[0] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				RoiImage[1] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3); 
				RoiImage[2] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				RoiImage[3] = cvCreateImage(cvSize(RoiW, RoiH), 8, 3);
				/*RoiImage[0]->origin = 1;
				RoiImage[1]->origin = 1;
				RoiImage[2]->origin = 1;
				RoiImage[3]->origin = 1;*/
				cvCopy(Frames[0], RoiImage[0]);
				cvCopy(Frames[1], RoiImage[1]);
				cvCopy(Frames[2], RoiImage[2]);
				cvCopy(Frames[3], RoiImage[3]);

				 for(int ROIF = 0 ; ROIF < 4; ROIF++)
				 {
						cvResize(RoiImage[ROIF], _subFrames[ROIF], CV_INTER_LINEAR);	//縮放源圖像到目標圖像
					 
						//cvNamedWindow( "src",   CV_WINDOW_AUTOSIZE );	//創建用於顯示源圖像的視窗
						//cvNamedWindow( "dst",   CV_WINDOW_AUTOSIZE );	//創建用於顯示目標圖像的視窗
					 
						//cvShowImage( "src", RoiImage[ROIF] );		//顯示源圖像
						//cvShowImage( "dst", _subFrames[ROIF]);		//顯示目標圖像
					 
						//cvWaitKey(27);		//等待用戶響應
				 }



				FrameSequenceToCubesObj.Transform(_subFrames, f-3);
				CubeInfo* cubeInfo = FrameSequenceToCubesObj.GetCubeInfo();

				int TNumberOfCube = FrameSequenceToCubesObj.GetNumberOfCubeInfo();

				for(int cube = 0 ; cube < TNumberOfCube; cube++)
				{
					VideoInfo[(int)VideoNorm] = cubeInfo[cube].CubeGradient;
					VideoNorm++;
				}

				Frames[0]->roi = NULL;
				Frames[1]->roi = NULL;
				Frames[2]->roi = NULL;
				Frames[3]->roi = NULL;

				cvReleaseImage(&RoiImage[0]);
				cvReleaseImage(&RoiImage[1]);
				cvReleaseImage(&RoiImage[2]);
				cvReleaseImage(&RoiImage[3]);
			}


		}
		cvReleaseImage(&Frames[0]);
		cvReleaseImage(&Frames[1]);
		cvReleaseImage(&Frames[2]);
		cvReleaseImage(&Frames[3]);
		cvReleaseImage(&_subFrames[0]);
		cvReleaseImage(&_subFrames[1]);
		cvReleaseImage(&_subFrames[2]);
		cvReleaseImage(&_subFrames[3]);
		cvReleaseCapture(&Capture);
		FrameSequenceToCubesObj.ReleaseBuffer();
	}


	CvSize dst_cvsize;			//目標圖像尺寸
	dst_cvsize.width = RoiW/scaling;		//目標圖像的寬為源圖象寬的scale倍
	dst_cvsize.height = RoiH/scaling;	//目標圖像的高為源圖象高的scale倍

	for(int f = StartZ; f < StartZ + RoiT; f+=4)
	{
		if(f/4 >= _tTime/4)
			break;
		for(int y = StartY; y < StartY + dst_cvsize.height; y += 4)
		{
			for(int x = StartX; x < StartX + dst_cvsize.width; x += 4)
			{
				int FinalIndex = (int)(x / 4) + (int)(y / 4) * (int)(_tWidth / 4);
				//int FinalIndex = (int)(y / 4) + (int)(x / 4) * (int)(_tHeight / 4);

				if(FinalIndex > _tNumberOfCube)
				{
					delete VideoInfo;
					VideoInfo = NULL;
					delete TempleteInfo;
					TempleteInfo = NULL;
					return -1;
				}
				TempleteInfo[(int)TempleteNorm] = _templateCubeGradient[(int)(f/4)][FinalIndex];
				TempleteNorm++;

			}
		}
	}
	

	for(int i = 0; i < TempleteNorm; i++)
	{

		if(SimilarValue < 0)
		{
			delete VideoInfo;
			VideoInfo = NULL;
			delete TempleteInfo;
			TempleteInfo = NULL;
			return -1;
		}
				
		SimilarValue += abs(VideoInfo[i] - TempleteInfo[i]);
	}



		
	if(TempleteNorm == 0)
		TempleteNorm = 1;
	SimilarValue /= TempleteNorm;
	delete VideoInfo;
	VideoInfo = NULL;
	delete TempleteInfo;
	TempleteInfo = NULL;
	return SimilarValue;

}








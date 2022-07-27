#include "StdAfx.h"
#include "SparseMatrix.h"
#include <stdio.h>

SparseDataNode* SparseMatrix::CreateNode(int index)
{
	SparseDataNode* NewNode = new SparseDataNode;
	NewNode->_Index = index;
	NewNode->_VoteValue = -1;

	NewNode->XLink = NULL;
	NewNode->YLink = NULL;
	NewNode->ZLink = NULL;

	return NewNode;
}

SparseMatrix::SparseMatrix(void)
{
	for(int s = 0; s < 3; s++)
		for(int ar = 0; ar < 36; ar++)
			for(int br = 0; br < 36; br++)
				Head[s][ar][br] = CreateNode(-1);

}

void SparseMatrix::Add(int s, int ar, int br, int y, int x, int z)
{
	SparseDataNode* Ptr = Head[s][ar][br];
	
	if(Ptr->XLink == NULL)
	{
		Ptr->XLink = CreateNode(x);
		Ptr = Ptr->XLink;

		Ptr->YLink = CreateNode(y);
		Ptr = Ptr->YLink;

		Ptr->ZLink = CreateNode(z);
		Ptr = Ptr->ZLink;
		Ptr->_VoteValue = 1;
	}
	else
	{
		SparseDataNode* FrontPtr = NULL;
		Ptr = Ptr->XLink;
		int SearchIndex = 0; // 0->X, 1->Y, 2->Z
		// Search X
		while(Ptr != NULL)
		{
			if(SearchIndex == 0)
			{
				if(Ptr->_Index == x)
				{
					SearchIndex = 1;
					Ptr = Ptr->YLink;
					continue;
				}
				FrontPtr = Ptr;
				Ptr = Ptr->XLink;
			}
			else if(SearchIndex == 1)
			{
				if(Ptr->_Index == y)
				{
					SearchIndex = 2;
					Ptr = Ptr->ZLink;
					continue;
				}
				FrontPtr = Ptr;
				Ptr = Ptr->YLink;
			}
			else if(SearchIndex == 2)
			{
				if(Ptr->_Index == z)
				{
					Ptr->_VoteValue++;
					break;
				}
				FrontPtr = Ptr;
				Ptr = Ptr->ZLink;
			}
		}
		
		if(Ptr == NULL)
		{
			if(SearchIndex == 0) // Add X
			{
				FrontPtr->XLink = CreateNode(x);
				FrontPtr = FrontPtr->XLink;

				FrontPtr->YLink = CreateNode(y);
				FrontPtr = FrontPtr->YLink;

				FrontPtr->ZLink = CreateNode(z);
				FrontPtr = FrontPtr->ZLink;
				FrontPtr->_VoteValue = 1;
			}
			else if(SearchIndex == 1) // Add Y
			{
				FrontPtr->YLink = CreateNode(y);
				FrontPtr = FrontPtr->YLink;

				FrontPtr->ZLink = CreateNode(z);
				FrontPtr = FrontPtr->ZLink;
				FrontPtr->_VoteValue = 1;
			}
			else if(SearchIndex == 2) // Add Z
			{
				FrontPtr->ZLink = CreateNode(z);
				FrontPtr = FrontPtr->ZLink;
				FrontPtr->_VoteValue = 1;
			}
		}
	}
}

struct ImagePoint* SparseMatrix::GetTopN(int N)
{

	VoteCoordinate = new ImagePoint[N];
	
	int CountTopTen = 0;
	
	int countS = 0;

	for(double s = 0.5; s <= 2; s += 0.5, countS++)
	{
		if(s == 1.5)
		{
			countS--;
			continue;
		}
		for(int ar = 0; ar < 36; ar++)
		{
			for(int br = 0; br < 36; br++)
			{
				SparseDataNode* PtrX = Head[countS][ar][br];
				SparseDataNode* PtrY;
				SparseDataNode* PtrZ;
				for(PtrX = PtrX->XLink; PtrX != NULL; PtrX = PtrX->XLink)
				{
					for(PtrY = PtrX->YLink; PtrY != NULL; PtrY = PtrY->YLink)
					{
						for(PtrZ = PtrY->ZLink; PtrZ != NULL; PtrZ = PtrZ->ZLink)
						{
							int VoteValue = PtrZ->_VoteValue;
							int r = PtrX->_Index;
							int c = PtrY->_Index;
							int t = PtrZ->_Index;

							if(CountTopTen < N) // 塞滿前十名
							{
								VoteCoordinate[CountTopTen].Vote =  VoteValue;
								VoteCoordinate[CountTopTen].x = r;
								VoteCoordinate[CountTopTen].y = c;
								VoteCoordinate[CountTopTen].t = t;
								VoteCoordinate[CountTopTen].scaling = s;
								VoteCoordinate[CountTopTen].Arotation = ar*10;
								VoteCoordinate[CountTopTen].Brotation = br*10;
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
									if(VoteValue > 1)
									{
										int a = VoteValue;
										int b = 0;
									}

									if(VoteValue < VoteCoordinate[i].Vote)
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
									VoteCoordinate[i].Vote = VoteValue;
									VoteCoordinate[i].x = r;
									VoteCoordinate[i].y = c;
									VoteCoordinate[i].t = t;
									VoteCoordinate[i].scaling = s;
									VoteCoordinate[i].Arotation = ar * 10;
									VoteCoordinate[i].Brotation = br * 10;
								}
							}
						}
					}
				}
			}
		}
	}
					
		
	return VoteCoordinate;
}

void SparseMatrix::countSAB(int Height,int Width, int NumberOfFrame,double DetectS,int N)
{

	voting = new int**[Height];
	for(int c = 0; c < Height; c++)
	{
		voting[c] = new int*[Width];
		for(int r = 0; r < Width; r++)
		{
			voting[c][r] = new int[NumberOfFrame];
			for(int t = 0; t < NumberOfFrame; t++)
				voting[c][r][t] = 0;
		}
	}

	int RotationAR[36];
	int RotationBR[36];
	for(int i = 0 ; i < 36; i++)
	{
		RotationAR[i] = 0;
		RotationBR[i] = 0;
	}


	/*int countS = 0;
	for(double s = 0.5; s <= 2; s += 0.5, countS++)
	{
		if(s == 1.5)
		{
			countS--;
			continue;
		}
		for(int ar = 0; ar < 36; ar++)
		{
			for(int br = 0; br < 36; br++)
			{
				SparseDataNode* PtrX = Head[countS][ar][br];
				SparseDataNode* PtrY;
				SparseDataNode* PtrZ;
				for(PtrX = PtrX->XLink; PtrX != NULL; PtrX = PtrX->XLink)
				{
					for(PtrY = PtrX->YLink; PtrY != NULL; PtrY = PtrY->YLink)
					{
						for(PtrZ = PtrY->ZLink; PtrZ != NULL; PtrZ = PtrZ->ZLink)
						{
							int VoteValue = PtrZ->_VoteValue;
							int r = PtrX->_Index;
							int c = PtrY->_Index;
							int t = PtrZ->_Index;
							
							if(s == DetectS)
							{
								voting[c][r][t]++;
							}
						}
					}
				}
			}
		}
	}*/

	for(int i = 0 ; i < N; i++)
	{
		int c = VoteCoordinate[i].y;
		int r = VoteCoordinate[i].x;
		int t = VoteCoordinate[i].t;
		int Vote = VoteCoordinate[i].Vote; 
		int AR = VoteCoordinate[i].Arotation;
		int BR = VoteCoordinate[i].Brotation;
		if(VoteCoordinate[i].scaling == DetectS)
		{
			voting[c][r][t] += Vote;
		}

		RotationAR[(int)(AR/10)]+=Vote;
		RotationBR[(int)(BR/10)]+=Vote;
		
	}
	

	int **sumProXY = new int*[Height];
	int **sumProXT = new int*[Height];
	int **sumProYT = new int*[Width];
	// **********
	for(int c = 0; c < Height; c++)
	{
		sumProXY[c] = new int[Width];
		for(int r = 0; r < Width; r++)
			sumProXY[c][r] = 0;
		
		sumProXT[c] = new int[NumberOfFrame];
		for(int n = 0; n < NumberOfFrame; n++)
			sumProXT[c][n] = 0;
	}
	for(int r = 0; r < Width; r++)
	{
		sumProYT[r] = new int[NumberOfFrame];
		for(int n = 0; n < NumberOfFrame; n++)		
			sumProYT[r][n] = 0;
	}
	// **********



	for(int t = 0 ; t < NumberOfFrame; t++)
	{
		for(int c = 0;c < Height;c++)
		{
				for(int r = 0; r < Width; r++)
				{
					sumProXY[c][r] = 0;
					sumProXT[c][t] = 0;
					sumProYT[r][t] = 0;
				}
		}
	}

	for(int t = 0 ; t < NumberOfFrame; t++)
	{
		for(int c = 0;c < Height;c++)
		{
				for(int r = 0; r < Width; r++)
				{
					sumProXY[c][r] += voting[c][r][t];
					sumProXT[c][t] += voting[c][r][t];
					sumProYT[r][t] += voting[c][r][t];
				}
		}
	}

	FILE* FilePtr= fopen("Test\\simular\\ScalingXY.txt","w");


	for(int c = 0;c < Height;c++)
	{
			for(int r = 0; r < Width; r++)
			{
				fprintf(FilePtr, "%d ", sumProXY[c][r]);
			}
			fprintf(FilePtr,";");
	}
	fclose(FilePtr);

	FilePtr= fopen("Test\\simular\\ScalingXT.txt","w");

	for(int c = 0;c < Height;c++)
	{
			for(int t = 0; t < NumberOfFrame; t++)
			{
				fprintf(FilePtr, "%d ", sumProXT[c][t]);
			}
			fprintf(FilePtr,";");
	}
	fclose(FilePtr);

	FilePtr= fopen("Test\\simular\\ScalingYT.txt","w");

	for(int r = 0; r < Width; r++)
	{
			for(int t = 0;t < NumberOfFrame;t++)
			{
				fprintf(FilePtr, "%d ", sumProYT[r][t]);
			}
			fprintf(FilePtr,";");
	}
	fclose(FilePtr);

	FilePtr= fopen("Test\\simular\\RotationAR.txt","w");

	for(int current = 0;current < 36;current++)
	{
		fprintf(FilePtr, "%d ", RotationAR[current]);
	}

	fclose(FilePtr);

	FilePtr= fopen("Test\\simular\\RotationBR.txt","w");

	for(int current = 0;current < 36;current++)
	{
		fprintf(FilePtr, "%d ", RotationBR[current]);
	}

	fclose(FilePtr);


	for(int c = 0; c < Height; c++)
	{
		for(int r = 0; r < Width; r++)
		{
			delete voting[c][r];
		}
		delete voting[c];
	}
	delete voting;
	voting = NULL;

	for(int c = 0; c < Height; c++)
	{
		delete sumProXY[c];		
		delete sumProXT[c];
	}
	delete sumProXT;
	sumProXT = NULL;
	delete sumProXY;
	sumProXY = NULL;

	for(int r = 0; r < Width; r++)
	{
		delete sumProYT[r];
	}
	delete sumProYT;
	sumProYT = NULL;
}

void SparseMatrix::Release()
{
	for(int s = 0; s < 3; s ++)
	{
		for(int ar = 0; ar < 36; ar++)
		{
			for(int br = 0; br < 36; br++)
			{
				SparseDataNode* PtrX = Head[s][ar][br];
				SparseDataNode* PtrY;
				SparseDataNode* PtrZ;
				SparseDataNode* Del;

				for(PtrX = PtrX->XLink; PtrX != NULL;)
				{
					for(PtrY = PtrX->YLink; PtrY != NULL;)
					{
						for(PtrZ = PtrY->ZLink; PtrZ != NULL; )
						{
							if(PtrZ->ZLink == NULL)
							{
								delete PtrZ;
								break;
							}
							else
							{
								Del = PtrZ;
								PtrZ = PtrZ->ZLink;
								delete Del;
							}
						} // END for(PtrZ = PtrY->ZLink; ; )
						if(PtrY->YLink == NULL)
						{
							delete PtrY;
							break;
						}
						else
						{
							Del = PtrY;
							PtrY = PtrY->YLink;
							delete Del;
						}
					} // END for(PtrY = PtrX->YLink; ;)
					if(PtrX->XLink == NULL)
					{
						delete PtrX;
						break;
					}
					else
					{
						Del = PtrX;
						PtrX = PtrX->XLink;
						delete Del;
					}
				} // END for(PtrX = PtrX->XLink; ;)
				Head[s][ar][br]->XLink = NULL;
			}
			
		}
	}
}

#include "StdAfx.h"
#include "SparseMatrix.h"


SparseDataNode* SparseMatrix::CreateNode(int index)
{
	SparseDataNode* NewNode = new SparseDataNode;
	NewNode->_Index = index;

	NewNode->XLink = NULL;
	NewNode->YLink = NULL;
	NewNode->ZLink = NULL;

	return NewNode;
}

SparseMatrix::SparseMatrix()
{
	for(int s = 0; s < 3; s++)
		for(int ar = 0; ar < 2; ar++)
			for(int br = 0; br < 2; br++)
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
		
		if(Ptr != NULL)
		{
			if(SearchIndex == 0) // Add X
			{
				FrontPtr->XLink = CreateNode(x);
				FrontPtr = Ptr->XLink;

				FrontPtr->YLink = CreateNode(y);
				FrontPtr = Ptr->YLink;

				FrontPtr->ZLink = CreateNode(z);
				FrontPtr->_VoteValue = 1;
			}
			else if(SearchIndex == 1) // Add Y
			{
				FrontPtr->YLink = CreateNode(y);
				FrontPtr = Ptr->YLink;

				FrontPtr->ZLink = CreateNode(z);
				FrontPtr->_VoteValue = 1;
			}
			else if(SearchIndex == 2) // Add Z
			{
				FrontPtr->ZLink = CreateNode(z);
				FrontPtr->_VoteValue = 1;
			}
		}
	}
}

struct ImagePoint* SparseMatrix::GetTopN()
{
	int N = 10;
	struct ImagePoint* VoteCoordinate = new ImagePoint[N];
	
	int CountTopTen = 0;
	
	int countS = 0;

	for(double s = 0.5; s <= 2; s += 0.5, countS++)
	{
		for(int ar = 0; ar < 2; ar++)
		{
			for(int br = 0; br < 2; br++)
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

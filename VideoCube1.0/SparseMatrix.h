#pragma once
#include "VolumeBasedGHT.h"
#include <stdio.h>
struct SParseData
{
	int _VoteValue;
	int _Index;
	struct SParseData* XLink;
	struct SParseData* YLink;
	struct SParseData* ZLink;
};

typedef struct SParseData SparseDataNode; 

class SparseMatrix
{

public:

	SparseMatrix* _SparseMatrix;
	struct ImagePoint* VoteCoordinate;
	struct ImagePoint* GetTopN(int N);

	SparseDataNode* CreateNode(int index);

	SparseDataNode* Head[3][36][36];

	SparseMatrix(void);

	int*** voting;

	void Add(int s, int ar, int br, int y, int x, int z);
	void countSAB(int Height,int Width, int NumberOfFrame,double DetectS,int N);
	void Release();	
};

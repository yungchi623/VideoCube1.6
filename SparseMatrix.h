#pragma once
#include <stdio.h>
#include "VolumeBasedGHT.h"

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
	struct ImagePoint* GetTopN();

	SparseDataNode* CreateNode(int index);

	SparseDataNode* Head[3][2][2];

	SparseMatrix();

	

	void Add(int s, int ar, int br, int y, int x, int z);

	

	
};

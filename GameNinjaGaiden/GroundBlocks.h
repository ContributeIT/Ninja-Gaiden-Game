#pragma once
#include "GroundBlock.h"
#include "GameObject.h"

class GroundBlocks
{
	GroundBlock * *groundBlocks;
	int numberOfBlocks;
	GroundBlock * currentBlock;
	float * currentHeight;
	float minHeight;
public:
	GroundBlocks(const char * filePath);
	~GroundBlocks();

	int getNumberOfBlocks();
	GroundBlock * getGroundBlock(int index);
	void Update(DWORD dt, GameObject &player);
};


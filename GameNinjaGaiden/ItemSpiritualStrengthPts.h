#pragma once
#include "Item.h"

enum ITEM_SPIRITUAL_STRENGTH_TYPE
{
	SPIRITUAL_STRENGTH_5_PTS,
	SPIRITUAL_STRENGTH_10_PTS,
};

class ItemSpiritualStrengthPts :
	public Item
{
	ITEM_SPIRITUAL_STRENGTH_TYPE type;
public:
	ItemSpiritualStrengthPts();
	~ItemSpiritualStrengthPts();
	
	void setType(ITEM_SPIRITUAL_STRENGTH_TYPE type);
	ITEM_SPIRITUAL_STRENGTH_TYPE getType();
	
	void Init(float x, float y);
	void CheckCollisionStatus(GameObject * player);
};


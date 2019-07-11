#pragma once
#include "GameObject.h"

enum USABLE_ITEM_TYPE
{
	UIT_THROWING_STAR,
	UIT_WINDMILL_THROWING_STAR,
};

class UsableItem :
	public GameObject
{
	USABLE_ITEM_TYPE type;
	int spiritualStrengthCost;
public:
	bool isUsed;
	UsableItem();
	~UsableItem();

	USABLE_ITEM_TYPE getType() { return type; }
	void setType(USABLE_ITEM_TYPE type) { this->type = type; }

	bool CollideEnemy(GameObject * enemy);

	virtual void Init(float x, float y) {}
	virtual void Update() {}
	void UseItem();
};


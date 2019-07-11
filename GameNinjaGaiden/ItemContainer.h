#pragma once
#include "GameObject.h"
#include "Item.h"

#define DEFAULT_ITEM_CONTAINER_WIDTH	16
#define DEFAULT_ITEM_CONTAINER_HEIGHT	16

class ItemContainer :
	public GameObject
{
	int itemTypeID;
	Item * item;
	float itemBase;
	bool isBroken;
public:
	ItemContainer();
	ItemContainer(float x, float y);
	~ItemContainer();

	int getItemTypeID();	void setItemTypeID(int id);
	float getItemBase();	void setItemBase(float base);

	void DropItem();

	void Init(GameObject * player);
	void CheckCollisionStatus(GameObject * player);
	void Update(DWORD dt, GameObject &player);
};


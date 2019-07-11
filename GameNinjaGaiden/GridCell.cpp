 #include "GridCell.h"
#include "Banshee.h"
#include "BirdBrown.h"
#include "MachineGunGuy.h"
#include "SwordMan.h"
#include "Cat.h"
#include "Cannoneer.h"
#include "Runner.h"
#include "ItemContainer.h"
#include "Player.h"
#include "Boss3.h"

#include<string>

GridCell::GridCell()
{
	columnIndex = rowIndex = 0;
	size = DEFAULT_CELL_SIZE;
	isEmpty = true;
}

GridCell::~GridCell()
{
}

int GridCell::getColumnIndex()
{
	return columnIndex;
}

void GridCell::setColumnIndex(int x)
{
	this->columnIndex = x;
}

int GridCell::getRowIndex()
{
	return rowIndex;
}

void GridCell::setRowIndex(int y)
{
	this->rowIndex = y;
}

int GridCell::getSize()
{
	return size;
}

void GridCell::setSize(int size)
{
	this->size = size;
}

int GridCell::getListSize()
{
	return listSize;
}

void GridCell::setListSize(int n)
{
	this->listSize = n;
}

void GridCell::addObjectInfo(float x, float y, int objTypeID, int itemTypeID, int itemBase)
{
	objectInfoList.push_back(new D3DXVECTOR3(x, y, objTypeID));
	itemInfoList.push_back(new D3DXVECTOR2(itemTypeID, itemBase));
}

void GridCell::InitObject(float x, float y, int objTypeID, int itemTypeID, int itemBase)
{
	GameObject * object = NULL;

	switch (objTypeID)
	{
	case 1:
		break;
	case 2:
		object = new Banshee(x, y);
		object->setObjectType(ENEMY_BANSHEE);
		break;
	case 3:
		// Bat (brown)
		break;
	case 4:
		break;
	case 5:
		object = new BirdBrown(x, y);
		object->directionX = itemTypeID;
		object->setObjectType(ENEMY_BIRD_BROWN);
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		object = new MachineGunGuy(x, y);
		object->setObjectType(ENEMY_MACHINE_GUN_GUY);
		break;
	case 11:
		break;
	case 12:
		object = new SwordMan(x, y);
		object->setObjectType(ENEMY_SWORD_MAN);
		break;
	case 13:
		object = new Cat(x, y);
		object->setObjectType(ENEMY_CAT);
		break;
	case 14:
		object = new Cannoneer(x, y);
		object->setObjectType(ENEMY_CANNONEER);
		break;
	case 15:
		object = new Runner(x, y);
		object->setObjectType(ENEMY_RUNNER);
		break;
	case 24:
		object = new ItemContainer(x, y);
		object->setObjectType(ITEM_ITEM_CONTAINER_4);
		object->setItemTypeID(itemTypeID);
		object->setItemBase(itemBase);
		break;
	case 25:
		object = new ItemContainer(x, y);
		object->setObjectType(ITEM_ITEM_CONTAINER_5);
		object->setItemTypeID(itemTypeID);
		object->setItemBase(itemBase);
		break;
	case 33:
		object = new Boss3(x, y);
		object->setObjectType(ENEMY_BOSS_3);
		break;
	default:
		break;
	}

	object->Init(Player::getInstance());
	object->isExist = false;
	object->isInCellsSet = false;

	objectList.push_back(object);
}
void GridCell::InitObject(D3DXVECTOR3 * objectInfo, D3DXVECTOR2 * itemInfo)
{
	InitObject(objectInfo->x, objectInfo->y, objectInfo->z, itemInfo->x, itemInfo->y);
}
void GridCell::InitAllObjects()
{
	if (!isEmpty)
	for (int i = 0; i < listSize; i++)
	{
		InitObject(objectInfoList[i], itemInfoList[i]);
	}
}

// getting
std::vector<D3DXVECTOR3*> GridCell::getObjectInfoList()
{
	return objectInfoList;
}
std::vector<D3DXVECTOR2*> GridCell::getItemInfoList()
{
	return itemInfoList;
}
std::vector<GameObject*> GridCell::getObjectList()
{
	return objectList;
}

//
void GridCell::enableUpdate(GameObject * player)
{
	if (!isEmpty)
	{
		for (int i = 0; i < listSize; i++)
		{
			objectList[i]->Init(player);
			objectList[i]->isExist = true;
			objectList[i]->isInCellsSet = true;
		}
	}
}
void GridCell::disableUpdate()
{
	if (!isEmpty)
	{
		for (int i = 0; i < listSize; i++)
		{
			if (objectList[i]->isInCellsSet) objectList[i]->isInCellsSet = false;
		}
	}
}

void GridCell::Release()
{
	std::vector<GameObject*> objectListClone;
	std::vector<D3DXVECTOR3*> objectInfoListClone;
	std::vector<D3DXVECTOR2*> itemInfoListClone;
	
	objectList.clear();
	objectInfoList.clear();
	itemInfoList.clear();

	objectList.swap(objectListClone);
	objectInfoList.swap(objectInfoListClone);
	itemInfoList.swap(itemInfoListClone);
}

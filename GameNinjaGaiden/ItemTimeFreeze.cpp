#include "ItemTimeFreeze.h"
#include "Stage.h"
#include <vector>


ItemTimeFreeze::ItemTimeFreeze()
{
}


ItemTimeFreeze::~ItemTimeFreeze()
{
}

void ItemTimeFreeze::setType(ITEM_TIME_FREEZE_TYPE type)
{
	this->type = type;
}

ITEM_TIME_FREEZE_TYPE ItemTimeFreeze::getType()
{
	return type;
}

void ItemTimeFreeze::Init(float x, float y)
{
	isExist = true;
	setX(x);
	setY(y);
	setSize(12, 15);
	setCollisionType(COLLISION_TYPE_ITEM);

	startAnimation = false;
	sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
	switch (getItemType())
	{
	case ITEM_TIME_FREEZE:
		type = TIME_FREEZE;
		sprite->LoadTexture("images/items/item_time_freeze.png", D3DCOLOR_XRGB(255, 255, 255));
		break;
	}
}

void ItemTimeFreeze::CheckCollisionStatus(GameObject * player)
{
	if (this->isExist)
	{
		if (collisionTime < 1.0f && !player->isAttacking)
		{
			if (type == TIME_FREEZE)
			{
				std::vector<GameObject*> objectList = Stage::getInstance()->GetAllObjects();
				
				for (int i = 0; i < objectList.size(); i++)
				{
					if (objectList[i]->getCollisionType() == COLLISION_TYPE_ENEMY)
						objectList[i]->Freeze(4000);
				}

				isExist = false;
			}
		}
	}
}

#include "ItemContainer.h"
#include "ItemSpiritualStrengthPts.h"
#include "ItemBonusPts.h"
#include "ItemFireWheelArt.h"
#include "ItemRestorePhysicalStrength.h"
#include "ItemThrowingStar.h"
#include "ItemTimeFreeze.h"
#include "ItemWindmillThrowingStar.h"

#include <string>

ItemContainer::ItemContainer()
{
}

ItemContainer::ItemContainer(float x, float y)
{
	setSize(DEFAULT_ITEM_CONTAINER_WIDTH, DEFAULT_ITEM_CONTAINER_HEIGHT);
	setX(x);
	setY(y + getHeight());
	isExist = true;
	setCollisionType(COLLISION_TYPE_NOTHING);
	isBroken = false;

	item = new Item();
}


ItemContainer::~ItemContainer()
{
}

int ItemContainer::getItemTypeID()
{
	return itemTypeID;
}

void ItemContainer::setItemTypeID(int id)
{
	itemTypeID = id;
}

float ItemContainer::getItemBase()
{
	return itemBase;
}

void ItemContainer::setItemBase(float base)
{
	itemBase = base;
}

void ItemContainer::Init(GameObject * player)
{
	startAnimation = true;

	//sprite->Release();
	switch (objType)
	{
	case ITEM_ITEM_CONTAINER_4:
		sprite->SetAnimation(getWidth(), getHeight(), 4, 2, 0, 1);
		break;
	case ITEM_ITEM_CONTAINER_5:
		sprite->SetAnimation(getWidth(), getHeight(), 4, 2, 2, 3);
		break;
	default:
		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
		break;
	}

	sprite->LoadTexture("images/items/ItemContainers.png", D3DCOLOR_XRGB(0, 128, 128));
}

void ItemContainer::CheckCollisionStatus(GameObject * player)
{
	if (!isBroken)
	if (player->isAttacking)
	{
		if (collisionTime < 1.0f)
		{
			// Player phá hộp
			// player tấn công khi đang đứng
			if (!player->isJumping)
			{
				if (player->directionX * (this->getLeft() >= player->getLeft() ? 1 : -1) > 0)
				{
					this->isBroken = true;
				}
			}
			// player tấn công khi đang nhảy (xoay vòng vòng nên khỏi xét hướng)
			else
			{
				this->isBroken = true;
			}

			// Rớt item
			DropItem();
		}
	}
}

void ItemContainer::DropItem()
{
	// Khởi tạo item
	switch (itemTypeID)
	{
	case 1:
		// Spiritual Strength 5 points
		item = new ItemSpiritualStrengthPts();
		item->setItemTypeID(itemTypeID);
		break;
	case 2:
		// Spiritual Strength 10 points
		item = new ItemSpiritualStrengthPts();
		item->setItemTypeID(itemTypeID);
		break;
	case 3:
		//ITEM_TIME_FREEZE
		item = new ItemTimeFreeze();
		item->setItemTypeID(itemTypeID);
		break;
	case 4:
		//ITEM_THROWING_STAR
		item = new ItemThrowingStar();
		item->setItemTypeID(itemTypeID);
		break;
	case 5:
		//ITEM_BONUS_500_PTS
		item = new ItemBonusPts();
		item->setItemTypeID(itemTypeID);
		break;
	case 6:
		//ITEM_BONUS_1000_PTS
		item = new ItemBonusPts();
		item->setItemTypeID(itemTypeID);
		break;
	case 7:
		//ITEM_FIRE_WHEEL_ART
		item = new ItemFireWheelArt();
		item->setItemTypeID(itemTypeID);
		break;
	case 8:
		//ITEM_HP_RECOVER
		item = new ItemRestorePhysicalStrength();
		item->setItemTypeID(itemTypeID);
		break;
	case 9:
		//ITEM_WINDMILL_THROWING_STAR
		item = new ItemWindmillThrowingStar();
		item->setItemTypeID(itemTypeID);
		break;
	default:
		break;
	}

	item->setItemBase(itemBase);
	item->Init(getX(), getY());
}

void ItemContainer::Update(DWORD dt, GameObject & player)
{
	timer.tickPerAnim = dt;

	if (!isBroken)
	{
		Draw();
	}
	else
	{
		if (item->isExist)
			item->Update(dt, player);
		else
			this->isExist = false;
	}
}

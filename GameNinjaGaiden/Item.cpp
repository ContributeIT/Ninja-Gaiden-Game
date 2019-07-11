#include "Item.h"
#include "Collision.h"


Item::Item()
{
}


Item::~Item()
{
}

int Item::getItemTypeID()
{
	return itemTypeID;
}

void Item::setItemTypeID(int id)
{
	itemTypeID = id;

	switch (id)
	{
	case 1:
		itemType = ITEM_SPIRITUAL_STR_5_PTS;
		break;
	case 2:
		itemType = ITEM_SPIRITUAL_STR_10_PTS;
		break;
	case 3:
		itemType = ITEM_TIME_FREEZE;
		break;
	case 4:
		itemType = ITEM_THROWING_STAR;
		break;
	case 5:
		itemType = ITEM_BONUS_500_PTS;
		break;
	case 6:
		itemType = ITEM_BONUS_1000_PTS;
		break;
	case 7:
		itemType = ITEM_FIRE_WHEEL_ART;
		break;
	case 8:
		itemType = ITEM_HP_RECOVER;
		break;
	case 9:
		itemType = ITEM_WINDMILL_THROWING_STAR;
		break;
	default: break;
	}
}

ITEM_TYPE Item::getItemType()
{
	return itemType;
}

void Item::setItemType(ITEM_TYPE itemType)
{
	this->itemType = itemType;

	switch (itemType)
	{
	case ITEM_SPIRITUAL_STR_5_PTS:
		itemTypeID = 1;
		break;
	case ITEM_SPIRITUAL_STR_10_PTS:
		itemTypeID = 2;
		break;
	case ITEM_TIME_FREEZE:
		itemTypeID = 3;
		break;
	case ITEM_THROWING_STAR:
		itemTypeID = 4;
		break;
	case ITEM_BONUS_500_PTS:
		itemTypeID = 5;
		break;
	case ITEM_BONUS_1000_PTS:
		itemTypeID = 6;
		break;
	case ITEM_FIRE_WHEEL_ART:
		itemTypeID = 7;
		break;
	case ITEM_HP_RECOVER:
		itemTypeID = 8;
		break;
	case ITEM_WINDMILL_THROWING_STAR:
		itemTypeID = 9;
		break;
	default: break;
	}
}

float Item::getItemBase()
{
	return base;
}

void Item::setItemBase(float base)
{
	this->base = base;
}

void Item::Update(DWORD dt, GameObject & player)
{
	// Rơi
	if (getBottom() > base)
	{
		if (getBottom() - base > 6)
		{
			moveY(-6);
		}
		else
		{
			moveY(-(getBottom() - base));
		}
	}

	Collision::CollisionHandle(player, *this);
	Draw();
}

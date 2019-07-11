#include "ItemSpiritualStrengthPts.h"
#include "Player.h"


ItemSpiritualStrengthPts::ItemSpiritualStrengthPts()
{
}


ItemSpiritualStrengthPts::~ItemSpiritualStrengthPts()
{
}

void ItemSpiritualStrengthPts::setType(ITEM_SPIRITUAL_STRENGTH_TYPE type)
{
	this->type = type;
}

ITEM_SPIRITUAL_STRENGTH_TYPE ItemSpiritualStrengthPts::getType()
{
	return type;
}

void ItemSpiritualStrengthPts::Init(float x, float y)
{
	isExist = true;
	setX(x);
	setY(y);
	setSize(15, 15);
	setCollisionType(COLLISION_TYPE_ITEM);

	startAnimation = false;
	sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
	switch (getItemType())
	{
	case ITEM_SPIRITUAL_STR_5_PTS:
		type = SPIRITUAL_STRENGTH_5_PTS;
		sprite->LoadTexture("images/items/item_spiritual_strength_5.png", D3DCOLOR_XRGB(255, 255, 255));
		break;
	case ITEM_SPIRITUAL_STR_10_PTS:
		type = SPIRITUAL_STRENGTH_10_PTS;
		sprite->LoadTexture("images/items/item_spiritual_strength_10.png", D3DCOLOR_XRGB(255, 255, 255));
		break;
	}
}

void ItemSpiritualStrengthPts::CheckCollisionStatus(GameObject * player)
{
	if (this->isExist)
	{
		if (collisionTime < 1.0f && !player->isAttacking)
		{
			// Xử lý khi player nhặt item
			// cái thứ này chỉ có 2 loại là +5 và +10
			if (type == SPIRITUAL_STRENGTH_5_PTS)
			{
				Player::getInstance()->increase_spiritualStrength(5);
				isExist = false;
			}
			else
			{
				Player::getInstance()->increase_spiritualStrength(10);
				isExist = false;
			}
		}
	}
}

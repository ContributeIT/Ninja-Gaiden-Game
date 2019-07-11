#include "ItemBonusPts.h"
#include "Player.h"


ItemBonusPts::ItemBonusPts()
{
}


ItemBonusPts::~ItemBonusPts()
{
}

void ItemBonusPts::setType(ITEM_BONUS_TYPE type)
{
	this->type = type;
}

ITEM_BONUS_TYPE ItemBonusPts::getType()
{
	return type;
}

void ItemBonusPts::Init(float x, float y)
{
	isExist = true;
	setX(x);
	setY(y);
	setSize(16, 15);
	setCollisionType(COLLISION_TYPE_ITEM);

	startAnimation = false;
	sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
	switch (getItemType())
	{
	case ITEM_BONUS_500_PTS:
		type = BONUS_500_PTS;
		sprite->LoadTexture("images/items/item_bonus_500.png", D3DCOLOR_XRGB(255, 255, 255));
		break;
	case ITEM_BONUS_1000_PTS:
		type = BONUS_1000_PTS;
		sprite->LoadTexture("images/items/item_bonus_1000.png", D3DCOLOR_XRGB(255, 255, 255));
		break;
	}
}

void ItemBonusPts::CheckCollisionStatus(GameObject * player)
{
	if (this->isExist)
	{
		if (collisionTime < 1.0f && !player->isAttacking)
		{
			// Xử lý khi player nhặt item
			if (type == BONUS_500_PTS)
			{
				Player::getInstance()->addScore(500);
				isExist = false;
			}
			else
			{
				Player::getInstance()->addScore(1000);
				isExist = false;
			}
		}
	}
}

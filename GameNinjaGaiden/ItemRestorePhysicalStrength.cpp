#include "ItemRestorePhysicalStrength.h"
#include "Player.h"

ItemRestorePhysicalStrength::ItemRestorePhysicalStrength()
{
}


ItemRestorePhysicalStrength::~ItemRestorePhysicalStrength()
{
}

void ItemRestorePhysicalStrength::setType(ITEM_RESTORE_PHYSICAL_STRENGTH_TYPE type)
{
	this->type = type;
}

ITEM_RESTORE_PHYSICAL_STRENGTH_TYPE ItemRestorePhysicalStrength::getType()
{
	return type;
}

void ItemRestorePhysicalStrength::Init(float x, float y)
{
	isExist = true;
	setX(x);
	setY(y);
	setSize(12, 16);
	setCollisionType(COLLISION_TYPE_ITEM);

	startAnimation = false;
	sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
	switch (getItemType())
	{
	case ITEM_HP_RECOVER:
		type = HP_RECOVER;
		sprite->LoadTexture("images/items/item_restore_physical_strength.png", D3DCOLOR_XRGB(255, 255, 255));
		break;
	}
}

void ItemRestorePhysicalStrength::CheckCollisionStatus(GameObject * player)
{
	if (this->isExist)
	{
		if (collisionTime < 1.0f && !player->isAttacking)
		{
			if (type == HP_RECOVER)
			{
				Player::getInstance()->setHP(MAX_HP);

				isExist = false;
			}
		}
	}
}

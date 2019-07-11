#include "ItemFireWheelArt.h"
#include "Collision.h"

ItemFireWheelArt::ItemFireWheelArt()
{
}


ItemFireWheelArt::~ItemFireWheelArt()
{
}

void ItemFireWheelArt::setType(ITEM_FIRE_WHEEL_TYPE type)
{
	this->type = type;
}

ITEM_FIRE_WHEEL_TYPE ItemFireWheelArt::getType()
{
	return type;
}

void ItemFireWheelArt::Init(float x, float y)
{
	isExist = true;
	setX(x);
	setY(y);
	setSize(16, 16);
	setCollisionType(COLLISION_TYPE_ITEM);

	startAnimation = false;
	sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
	switch (getItemType())
	{
	case ITEM_FIRE_WHEEL_ART:
		type = FIRE_WHEEL_ART;
		sprite->LoadTexture("images/items/item_fire_wheel_art.png", D3DCOLOR_XRGB(255, 255, 255));
		break;
	}
}

void ItemFireWheelArt::CheckCollisionStatus(GameObject * player)
{
	if (this->isExist)
	{
		if (collisionTime < 1.0f && !player->isAttacking)
		{
			if (type == FIRE_WHEEL_ART)
			{
				// cái này làm gì nhỉ

				isExist = false;
			}
			
		}
	}
}

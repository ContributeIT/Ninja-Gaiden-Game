#include "ItemThrowingStar.h"
#include "Player.h"
#include "Collision.h"

ItemThrowingStar::ItemThrowingStar()
{
	item = new ThrowingStar();
}


ItemThrowingStar::~ItemThrowingStar()
{
}

void ItemThrowingStar::Init(float x, float y)
{
	isExist = true;
	setX(x);
	setY(y);
	setSize(16, 16);
	setCollisionType(COLLISION_TYPE_ITEM);

	startAnimation = false;
	sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
	sprite->LoadTexture("images/items/item_throwing_star.png", D3DCOLOR_XRGB(255, 255, 255));
}

void ItemThrowingStar::CheckCollisionStatus(GameObject * player)
{
	if (this->isExist)
	{
		if (collisionTime < 1.0f && !player->isAttacking)
		{
			Player::getInstance()->setItem(item);
			isExist = false;
		}
	}
}

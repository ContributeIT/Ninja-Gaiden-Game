#include "UsableItem.h"
#include "Player.h"
#include "Collision.h"


UsableItem::UsableItem()
{
}


UsableItem::~UsableItem()
{
}

bool UsableItem::CollideEnemy(GameObject * enemy)
{
	if (isExist)
	{
		Collision::CollisionHandle(*enemy, *this);
		if (collisionTime < 1.0f)
		{
			if (type == UIT_THROWING_STAR)
			{
				isExist = false;
			}
			return true;
		}
	}
	
	return false;
}

void UsableItem::UseItem()
{
	switch (type)
	{
	case UIT_THROWING_STAR:
		spiritualStrengthCost = 3;
		break;
	case UIT_WINDMILL_THROWING_STAR:
		spiritualStrengthCost = 5;
		break;
	}

	Player * player = Player::getInstance();
	if (player->getSpiritualStrength() >= spiritualStrengthCost)
	{
		player->decrease_spiritualStrength(spiritualStrengthCost);
		player->SetStatus(PLAYER_ITEM_USE, player->directionX);

		isExist = true;
		isUsed = true;
	}
}

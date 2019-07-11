#include "Boss3Bullet.h"



Boss3Bullet::Boss3Bullet()
{
	setSize(DEFAULT_BOSS_3_BULLET_WIDTH, DEFAULT_BOSS_3_BULLET_HEIGHT);
	isExist = false;
	delayTime = 0;
}

Boss3Bullet::~Boss3Bullet()
{
}

void Boss3Bullet::Init(float x, float y)
{
	isAlive = true;
	setSize(DEFAULT_BOSS_3_BULLET_WIDTH, DEFAULT_BOSS_3_BULLET_HEIGHT);

	setX(x);
	setY(y);
	isExist = true;
	setObjectType(ENEMY_BOSS_3_BULLET);
	setCollisionType(COLLISION_TYPE_ENEMY);
	isMoving = false;
	startDelay = GetTickCount();
	//
	setVelX(DEFAULT_BOSS_3_BULLET_VELOCITY * directionX);
	sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
	sprite->LoadTexture("images/enemies/Boss3_bullet.png", D3DCOLOR_XRGB(255, 163, 177));
}

void Boss3Bullet::SetStatus(ENEMY_STATUS status)
{
	switch (status)
	{
	case ENEMY_STANDING:
		break;
	case ENEMY_MOVING:
		break;
	default:
		break;
	}
}

void Boss3Bullet::Update(DWORD dt, GameObject & player)
{
	if (isAlive)
	{
		SetStatus(ENEMY_MOVING);

		if (!isMoving)
		{
			if (GetTickCount() - startDelay >= delayTime)
			{
				isMoving = true;
			}
		}
		else
		{
			autoMove(0);
		}
	}
	else
	{
		timer.tickPerAnim = DIE_ANIMATION_TIME;

		if (sprite->getCurrentAnimation() == sprite->getLastAnimation())
		{
			isInvincible = false;
			isExist = false;
		}
	}

	Draw();
}

void Boss3Bullet::autoMove(float range)
{
	selfMovingX();
}

#include "CannonBullet.h"



CannonBullet::CannonBullet()
{
	setSize(DEFAULT_CANNON_BULLET_WIDTH, DEFAULT_CANNON_BULLET_HEIGHT);
	isExist = false;
	startFire = -1;
}

CannonBullet::~CannonBullet()
{
}

void CannonBullet::Init(float x, float y)
{
	isAlive = true;
	setSize(DEFAULT_CANNON_BULLET_WIDTH, DEFAULT_CANNON_BULLET_HEIGHT);

	setX(x);
	setY(y);

	isExist = true;

	startFire = GetTickCount();
	SetStatus(ENEMY_STANDING);
	setObjectType(ENEMY_CANNON_BULLET);
	setCollisionType(COLLISION_TYPE_ENEMY);
}

void CannonBullet::SetStatus(ENEMY_STATUS status)
{
	switch (status)
	{
	case ENEMY_STANDING:
		setVelX(0);
		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 0);
		if (directionX > 0)
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/Cannoneer_fire_right.png", D3DCOLOR_XRGB(255, 163, 177));
		}
		else
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/Cannoneer_fire_left.png", D3DCOLOR_XRGB(255, 163, 177));
		}
		break;
	case ENEMY_MOVING:
		setVelX(DEFAULT_CANNON_BULLET_VELOCITY * directionX);
		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 1, 1);
		if (directionX > 0)
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/Cannoneer_fire_right.png", D3DCOLOR_XRGB(255, 163, 177));
		}
		else
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/Cannoneer_fire_left.png", D3DCOLOR_XRGB(255, 163, 177));
		}
		break;
	default:
		break;
	}
}

void CannonBullet::Update(DWORD dt, GameObject & player)
{
	if (startFire != -1)
	if (GetTickCount() - startFire >= FIRE_TIME)
	{
		if (isAlive) SetStatus(ENEMY_MOVING);
		startFire = -1;
	}

	if (isAlive)
	{
		autoMove(0);
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

void CannonBullet::autoMove(float range)
{
	selfMovingX();
}

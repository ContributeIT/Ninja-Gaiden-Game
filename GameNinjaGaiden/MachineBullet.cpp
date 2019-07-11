#include "MachineBullet.h"



MachineBullet::MachineBullet()
{
	setObjectType(ENEMY_MACHINE_BULLET);
	setCollisionType(COLLISION_TYPE_ENEMY);
	setSize(DEFAULT_MACHINEGUN_BULLET_WIDTH, DEFAULT_MACHINEGUN_BULLET_HEIGHT);
	isExist = false;
	startFire = -1;
}

MachineBullet::~MachineBullet()
{
}

void MachineBullet::Init(float x, float y)
{
	isAlive = true;
	setSize(DEFAULT_MACHINEGUN_BULLET_WIDTH, DEFAULT_MACHINEGUN_BULLET_HEIGHT);

	setX(x);
	setY(y);

	startFire = GetTickCount();
	SetStatus(ENEMY_STANDING);
	isExist = true;
}

void MachineBullet::SetStatus(ENEMY_STATUS status)
{
	switch (status)
	{
	case ENEMY_STANDING:
		setVelX(0);
		sprite->SetAnimation(getWidth(), getHeight(), 3, 3, 0, 1);
		if (directionX > 0)
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/MachineGunFire_right.png", D3DCOLOR_XRGB(0, 128, 128));
		}
		else
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/MachineGunFire_left.png", D3DCOLOR_XRGB(0, 128, 128));
		}
		break;
	case ENEMY_ATTACKING:
		setVelX(DEFAULT_MACHINEGUN_BULLET_VELOCITY * directionX);
		sprite->SetAnimation(getWidth(), getHeight(), 3, 3, 2, 2);
		if (directionX > 0)
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/MachineGunFire_right.png", D3DCOLOR_XRGB(0, 128, 128));
		}
		else
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/MachineGunFire_left.png", D3DCOLOR_XRGB(0, 128, 128));
		}
		break;
	default:
		break;
	}
}

void MachineBullet::Update(DWORD dt, GameObject & player)
{
	if (startFire != -1)
	if (GetTickCount() - startFire >= FIRE_TIME)
	{
		if (isAlive)
			SetStatus(ENEMY_ATTACKING);
		startFire = -1;
	}

	if (isAlive) autoMove(32);

	if (!isAlive)
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

void MachineBullet::autoMove(float range)
{
	selfMovingX();
}

#include "Banshee.h"
Banshee::Banshee()
{
	setSize(DEFAULT_BANSHEE_WIDTH, DEFAULT_BANSHEE_HEIGHT);
}

Banshee::Banshee(float x, float y)
{
	moveType = MT_ON_ONE_GROUND;
	setCollisionType(COLLISION_TYPE_ENEMY);
	setSize(DEFAULT_BANSHEE_WIDTH, DEFAULT_BANSHEE_HEIGHT);
	spawnX = x;
	spawnY = y;
	isExist = false;
}

Banshee::~Banshee()
{
}

void Banshee::Init(GameObject * player)
{
	isExist = true;
	isAlive = true;
	setSize(DEFAULT_BANSHEE_WIDTH, DEFAULT_BANSHEE_HEIGHT);

	setX(spawnX);
	setY(spawnY + getHeight());
	directionX = player->getMidX() <= getMidX() ? -1 : 1;
	setVelX(DEFAULT_BANSHEE_VELOCITY * directionX);

	SetStatus(ENEMY_STANDING);
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	if (directionX > 0)
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Banshee_right.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Banshee_left.png", D3DCOLOR_XRGB(255, 255, 255));
	}
}

void Banshee::SetStatus(ENEMY_STATUS status)
{
	this->status = status;

	switch (status)
	{
	case ENEMY_STANDING:
		startAnimation = false;

		break;
	case ENEMY_MOVING:
		startAnimation = true;
		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
		if (getVelX() > 0)
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/Banshee_right.png", D3DCOLOR_XRGB(255, 255, 255));
		}
		else
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/Banshee_left.png", D3DCOLOR_XRGB(255, 255, 255));
		}
		break;
	default:
		break;
	}
}

void Banshee::Update(DWORD dt, GameObject &player)
{
	if (isAlive)
	{
		timer.tickPerAnim = dt;

		MindTheGroundBlocks();
		SetStatus(ENEMY_MOVING);

		if (!isFreezing)
			autoMove(80);
		else
		{
			startAnimation = false;

			if (GetTickCount() - startFreezeTime >= freezeTime)
			{
				isFreezing = false;
			}
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

void Banshee::autoMove(float range)
{
	setVelX(DEFAULT_BANSHEE_VELOCITY * directionX);
	selfMovingX();
}
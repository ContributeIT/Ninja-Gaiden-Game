#include "SwordMan.h"
#include "Collision.h"


SwordMan::SwordMan()
{
	setSize(DEFAULT_SWORD_MAN_WIDTH, DEFAULT_SWORD_MAN_HEIGHT);
}

SwordMan::SwordMan(float x, float y)
{
	moveType = MT_ON_ONE_GROUND;
	setCollisionType(COLLISION_TYPE_ENEMY);
	setSize(DEFAULT_SWORD_MAN_WIDTH, DEFAULT_SWORD_MAN_HEIGHT);
	spawnX = x;
	spawnY = y;
	isExist = false;
	currentBlock = new GameObject();
}

SwordMan::~SwordMan()
{
}

void SwordMan::Init(GameObject * player)
{
	isExist = true;
	isAlive = true;
	isInvincible = false;
	setSize(DEFAULT_SWORD_MAN_WIDTH, DEFAULT_SWORD_MAN_HEIGHT);

	setX(spawnX);
	setY(spawnY + getHeight());
	directionX = player->getMidX() <= getMidX() ? -1 : 1;

	setVelX(DEFAULT_SWORD_MAN_VELOCITY * directionX);
	
	SetStatus(ENEMY_STANDING);
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	if (directionX > 0)
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/SwordMan_right.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/SwordMan_left.png", D3DCOLOR_XRGB(255, 255, 255));
	}
}

void SwordMan::SetStatus(ENEMY_STATUS status)
{
	this->status = status;

	switch (status)
	{
	case ENEMY_STANDING:
		startAnimation = false;

		break;
	case ENEMY_MOVING:
		startAnimation = true;
		if (directionX > 0)
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/SwordMan_right.png", D3DCOLOR_XRGB(255, 255, 255));
		}
		else
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/SwordMan_left.png", D3DCOLOR_XRGB(255, 255, 255));
		}
		break;
	case ENEMY_DIE:
		
		break;
	default:
		break;
	}
}

void SwordMan::Update(DWORD dt, GameObject &player)
{
	if (isAlive)
	{
		timer.tickPerAnim = dt;

		MindTheGroundBlocks();
		SetStatus(ENEMY_MOVING);

		if (!isFreezing)
		{
			autoMove(0);
		}
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

void SwordMan::autoMove(float range)
{
	setVelX(DEFAULT_SWORD_MAN_VELOCITY * directionX);
	selfMovingX();
}
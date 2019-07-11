#include "BirdBrown.h"
#include <string>


BirdBrown::BirdBrown()
{
	setSize(DEFAULT_BIRD_BROWN_WIDTH, DEFAULT_BIRD_BROWN_HEIGHT);
}

BirdBrown::BirdBrown(float x, float y)
{
	setCollisionType(COLLISION_TYPE_ENEMY);
	setSize(DEFAULT_BIRD_BROWN_WIDTH, DEFAULT_BIRD_BROWN_HEIGHT);
	spawnX = x;
	spawnY = y;
	isExist = false;

	seekRange = 36;
	playerRange = 40;
}

BirdBrown::~BirdBrown()
{
}

void BirdBrown::Init(GameObject * player)
{
	isExist = true;
	isAlive = true;
	setSize(DEFAULT_BIRD_BROWN_WIDTH, DEFAULT_BIRD_BROWN_HEIGHT);

	setX(spawnX);
	setY(spawnY + getHeight());
	maxY = getY();
	minY = maxY - 32;
	playerIsInSeekRange = false;

	if (directionX) {
		if (!spawnDirectionX)
		{
			spawnDirectionX = directionX;
		}
	}
	if (spawnDirectionX)
	{
		directionX = spawnDirectionX;
	}
	else
	{
		directionX = player->getMidX() > getMidX() ? 1 : -1;
	}

	directionY = -1;

	setVelX(DEFAULT_BIRD_BROWN_VELOCITY_X * directionX);
	setVelY(DEFAULT_BIRD_BROWN_VELOCITY_Y / 2 * directionY);

	SetStatus(ENEMY_STANDING);
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	if (directionX > 0)
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/BirdBrown_right.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/BirdBrown_left.png", D3DCOLOR_XRGB(255, 255, 255));
	}
}

void BirdBrown::SetStatus(ENEMY_STATUS status)
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
			sprite->LoadTexture("images/enemies/BirdBrown_right.png", D3DCOLOR_XRGB(255, 255, 255));
		}
		else
		{
			sprite->Release();
			sprite->LoadTexture("images/enemies/BirdBrown_left.png", D3DCOLOR_XRGB(255, 255, 255));
		}
		break;
	default:
		break;
	}
}

void BirdBrown::Update(DWORD dt, GameObject &player)
{
	if (isAlive)
	{
		timer.tickPerAnim = dt;

		SetStatus(ENEMY_MOVING);

		if (!isFreezing)
			autoMove(100, &player);
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

void BirdBrown::autoMove(float range, GameObject * player)
{
	if (!playerIsInSeekRange)
	{
		// bay qua lại ở điểm ban đầu phạm vi range  |<---range---spawnX---range--->|
		if (getMidX() <= spawnX - range || getMidX() >= spawnX + range)
		{
			setVelX(-getVelX());
		}

		// bay lên bay xuống một cách bình thường
		if (getY() <= minY || getY() > maxY)
		{
			setVelY(-getVelY());
		}

		if (player->getRight() >= getMidX() - seekRange && player->getLeft() <= getMidX() + seekRange)
		{
			playerIsInSeekRange = true;
			playerMidX = player->getMidX();
		}
	}
	else
	{
		minY = player->getY();
		maxY = minY + getHeight();

		// bay qua lại quanh player
		if (getMidX() >= playerMidX - playerRange && getMidX() <= playerMidX + playerRange)
		{
			if (getMidX() < playerMidX - playerRange || getMidX() > playerMidX + playerRange)
			{
				setVelX(-getVelX());
			}
		}
		else if (getMidX() < playerMidX - playerRange)
		{
			setVelX(DEFAULT_BIRD_BROWN_VELOCITY_X);
		}
		else
		{
			setVelX(-DEFAULT_BIRD_BROWN_VELOCITY_X);
		}

		// xét tâm chuyển động mới
		if ((player->directionX == -1 && (getMidX() <= playerMidX - playerRange ||
			getMidX() >= player->getMidX() + playerRange)) ||
			(player->directionX == 1 && (getMidX() >= playerMidX + playerRange ||
				getMidX() <= player->getMidX() - playerRange)))
		{
			playerMidX = player->getMidX();
		}

		// bay lên bay xuống
		if (getMidY() >= minY && getMidY() <= maxY)
		{
			if (getMidY() == minY || getMidY() == maxY)
			{
				setVelY(-getVelY());
			}
		}
		else if (getMidY() < minY)
		{
			setVelY(DEFAULT_BIRD_BROWN_VELOCITY_Y);
		}
		else
		{
			setVelY(-DEFAULT_BIRD_BROWN_VELOCITY_Y);
		}
	}
	selfMovingX();
	selfMovingY();
}
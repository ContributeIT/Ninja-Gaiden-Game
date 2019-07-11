#include "Cat.h"
Cat::Cat()
{
	setSize(DEFAULT_CAT_WIDTH, DEFAULT_CAT_HEIGHT);
}

Cat::Cat(float x, float y)
{
	moveType = MT_FROM_HIGHER_TO_LOWER_GROUND;
	setCollisionType(COLLISION_TYPE_ENEMY);
	isOnGround = true;
	setSize(DEFAULT_CAT_WIDTH, DEFAULT_CAT_HEIGHT);
	spawnX = x;
	spawnY = y;
	isExist = false;
}

Cat::~Cat()
{
}

void Cat::Init(GameObject * player)
{
	isExist = true;
	isAlive = true;
	setSize(DEFAULT_CAT_WIDTH, DEFAULT_CAT_HEIGHT);

	setX(spawnX);
	setY(spawnY + getHeight());
	currentGroundY = getY();
	minY = getY();
	maxY = minY + 6;
	directionX = player->getMidX() <= getMidX() ? -1 : 1;
	directionY = 1;
	setVelX(DEFAULT_CAT_VELOCITY * directionX);
	setVelY(DEFAULT_CAT_VELOCITY/2 * directionY);

	SetStatus(ENEMY_STANDING);
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	if (directionX > 0)
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Cat_right.png", D3DCOLOR_XRGB(255, 163, 177));
	}
	else
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Cat_left.png", D3DCOLOR_XRGB(255, 163, 177));
	}
}

void Cat::SetStatus(ENEMY_STATUS status)
{
	//if (this->status != status || directionChanged)
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
				sprite->LoadTexture("images/enemies/Cat_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Cat_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			break;
		default:
			break;
		}
	}
}

void Cat::Update(DWORD dt, GameObject &player)
{
	if (isAlive)
	{
		timer.tickPerAnim = dt;

		MindTheGroundBlocks();
		SetStatus(ENEMY_MOVING);

		if (!isFreezing)
			autoMove(120);
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

void Cat::autoMove(float range)
{
	setVelX(DEFAULT_CAT_VELOCITY * directionX);
	selfMovingX();

	// Nhảy tưng tưng
	if (getY() < minY || getY() >= maxY)
	{
		setVelY(-getVelY());
	}
	selfMovingY();
}
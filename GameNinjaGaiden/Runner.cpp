#include "Runner.h"



Runner::Runner()
{
	setSize(DEFAULT_RUNNER_WIDTH, DEFAULT_RUNNER_HEIGHT);
}

Runner::Runner(float x, float y)
{
	moveType = MT_FROM_HIGHER_TO_LOWER_GROUND;
	setCollisionType(COLLISION_TYPE_ENEMY);
	isOnGround = true;
	setSize(DEFAULT_RUNNER_WIDTH, DEFAULT_RUNNER_HEIGHT);
	spawnX = x;
	spawnY = y;
	isExist = false;
}

Runner::~Runner()
{
}

void Runner::Init(GameObject * player)
{
	isExist = true;
	isAlive = true;
	setSize(DEFAULT_RUNNER_WIDTH, DEFAULT_RUNNER_HEIGHT);

	setX(spawnX);
	setY(spawnY + getHeight());
	currentGroundY = getY();
	directionX = player->getMidX() <= getMidX() ? -1 : 1;
	setVelX(DEFAULT_RUNNER_VELOCITY * directionX);

	SetStatus(ENEMY_STANDING);
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	if (directionX > 0)
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Runner_right.png", D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		sprite->Release();
		sprite->LoadTexture("images/enemies/Runner_left.png", D3DCOLOR_XRGB(255, 255, 255));
	}
}

void Runner::SetStatus(ENEMY_STATUS status)
{
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
				sprite->LoadTexture("images/enemies/Runner_right.png", D3DCOLOR_XRGB(255, 255, 255));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Runner_left.png", D3DCOLOR_XRGB(255, 255, 255));
			}
			break;
		default:
			break;
		}
	}
}

void Runner::Update(DWORD dt, GameObject & player)
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

void Runner::autoMove(float range)
{
	setVelX(DEFAULT_RUNNER_VELOCITY * directionX);
	selfMovingX();
}

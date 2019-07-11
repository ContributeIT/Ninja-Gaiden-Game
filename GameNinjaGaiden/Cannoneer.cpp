#include "Cannoneer.h"
#include "Player.h"
#include "Collision.h"

#include <string>

Cannoneer::Cannoneer()
{
	setSize(DEFAULT_CANNONEER_WIDTH, DEFAULT_CANNONEER_HEIGHT);
}

Cannoneer::Cannoneer(float x, float y)
{
	setCollisionType(COLLISION_TYPE_ENEMY);
	setSize(DEFAULT_CANNONEER_WIDTH, DEFAULT_CANNONEER_HEIGHT);
	spawnX = x;
	spawnY = y;
	isExist = false;

	bullet = new CannonBullet();
}

Cannoneer::~Cannoneer()
{
}

void Cannoneer::Init(GameObject * player)
{
	isExist = true;
	isAlive = true;
	setSize(DEFAULT_CANNONEER_WIDTH, DEFAULT_CANNONEER_HEIGHT);

	directionChanged = false;
	setX(spawnX);
	setY(spawnY + getHeight());
	directionX = player->getMidX() <= getMidX() ? -1 : 1;
	
	isAttacking = true;
	startCooldown = GetTickCount() + 800;

	status = ENEMY_STANDING;
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 0);
	if (directionX > 0)
	{
		sprite->LoadTexture("images/enemies/Cannoneer_right.png", D3DCOLOR_XRGB(255, 163, 177));
	}
	else
	{
		sprite->LoadTexture("images/enemies/Cannoneer_left.png", D3DCOLOR_XRGB(255, 163, 177));
	}
}

void Cannoneer::SetStatus(ENEMY_STATUS status)
{
	switch (status)
	{
	case ENEMY_STANDING:
		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 0);
		if (directionChanged)
		{
			if (directionX > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Cannoneer_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Cannoneer_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			directionChanged = false;
		}
		break;
	case ENEMY_MOVING:
		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 1, 1);
		if (directionChanged)
		{
			if (directionX > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Cannoneer_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Cannoneer_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			directionChanged = false;
		}
		break;
	default:
		break;
	}
}

void Cannoneer::Update(DWORD dt, GameObject & player)
{
	if (isAlive)
	{
		timer.tickPerAnim = dt;

		if (bullet->startFire != -1)
		{
			SetStatus(ENEMY_MOVING);
		}
		else
		{
			SetStatus(ENEMY_STANDING);
		}

		if (!isFreezing)
		{
			autoMove(0);
			periodAttack(2000);
		}
		else
		{
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

void Cannoneer::autoMove(float range)
{
	// làm màu
	int temp = directionX;
	directionX = Player::getInstance()->getMidX() > getMidX() ? 1 : -1;
	if (temp * directionX < 0) directionChanged = true;
}

void Cannoneer::periodAttack(DWORD cooldown)
{	
	// isAttacking = false <=> sẵn sàng tấn công => thực hiện tấn công
	if (!isAttacking)
	{
		isAttacking = true;
		startCooldown = GetTickCount();

		// Xử lý tấn công
		bullet->directionX = directionX;
		if (directionX > 0)
		{
			bullet->Init(getRight(), getY() -1);
		}
		else
		{
			bullet->Init(getLeft() - bullet->getRealWidth(), getY() -1);
		}
	}
	// đã attack thì bắt đầu chờ cd
	else
	{
		if (GetTickCount() - startCooldown >= cooldown)
		{
			isAttacking = false;
			bullet->isExist = false;
		}

		// update viên đạn bay
		if (bullet->isExist)
		{
			Collision::CollisionHandle(*Player::getInstance(), *bullet);
			bullet->Update(0, *Player::getInstance());
		}
	}
}


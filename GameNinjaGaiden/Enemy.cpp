#include "Enemy.h"
#include "Game.h"
#include "Player.h"

#include "Collision.h"

Enemy::Enemy()
{
	isExist = false;
}


Enemy::~Enemy()
{
}

void Enemy::getHitByPlayer()
{
	if (isBoss())
	{
		decrease_HP();
	}
	else
	{
		Die();
	}
}

void Enemy::CheckCollisionStatus(GameObject * playerFake)	// nhập chơi thôi chứ chả xài
{
	Player * player = Player::getInstance();

	// bị player tấn công
	if (player->isAttacking && isAlive)
	{
		if (collisionTime < 1.0f)
		{
			// player tấn công khi đang đứng
			if (!player->isJumping)
			{
				if (player->directionX * (this->getLeft() >= player->getLeft() ? 1 : -1) > 0)
				{
					getHitByPlayer();
				}
			}
			// player tấn công khi đang nhảy (xoay vòng vòng nên khỏi xét hướng)
			else
			{
				getHitByPlayer();
			}
		}
	}

	// va chạm với item của player
	if (player->getItem()->CollideEnemy(this))
	{
		getHitByPlayer();
	}

	// đập player (khi hắn không bất tử)
	if (this->isAlive && !player->isInvincible && (!player->isAttacking)
		&& Game::getInstance()->allowHurtingPlayer)
	{
		if (collisionTime < 1.0f)
		{
			// hướng player = quái bên phải ? bên phải : bên trái
			player->directionX = this->getLeft() >= player->getLeft() ? 1 : -1;
			player->SetStatus(PLAYER_KNOCKBACK, player->directionX);

			player->decrease_HP();

			if (getObjectType() == ENEMY_MACHINE_BULLET ||
				getObjectType() == ENEMY_CANNON_BULLET ||
				getObjectType() == ENEMY_BOSS_3_BULLET)
			{
				// giảm thêm 1 máu nữa là 2
				player->decrease_HP();
			}
		}
	}
}

void Enemy::Die()
{
	SetStatus(ENEMY_DIE);	// <- đáng lẽ phải xử lý trong đây, mà con nào cũng chết giống nhau nên lười sửa code từng con

	#pragma region Show code
	float realWidth, realHeight;
	realWidth = getWidth();
	realHeight = getHeight();

	setSize(48, 48);
	startAnimation = true;

	setX(getX() - (getWidth() - realWidth) / 2);
	setY(getY() + (getHeight() - realHeight) / 2);

	sprite->SetAnimation(48, 48, 3, 3, 0, 2);
	sprite->Release();
	sprite->LoadTexture("images/enemies/die.png", D3DCOLOR_XRGB(0, 128, 128));

	timer.startTime = GetTickCount();
	sprite->setCurrentAnimation(0);

	isInvincible = true;
	isAlive = false;
#pragma endregion
}

void Enemy::setSpawned(bool isSpawned)
{
	isExist = isSpawned;
}

void Enemy::SetStatus(ENEMY_STATUS status)
{
	this->status = status;
}

void Enemy::Update(DWORD dt, GameObject & player)
{
	timer.tickPerAnim = dt;

	SetStatus(ENEMY_MOVING);
	autoMove(10);
	Draw();
}

void Enemy::MindTheGroundBlocks()
{
	switch (moveType)
	{
	case MT_ON_ONE_GROUND:
		if (getLeft() < currentBlock->getLeft())
		{
			setX(currentBlock->getLeft());
			directionX = 1;
		}
		if (getRight() > currentBlock->getRight())
		{
			setX(currentBlock->getRight() - getWidth());
			directionX = -1;
		}
		break;
	case MT_FROM_HIGHER_TO_LOWER_GROUND:	// [incompleted]
		if (getLeft() < currentBlock->getLeft())
		{
			if (getLeft() < 0)
			{ 
				setX(0);
				directionX = 1;
			}
			else
			{
				if (getRight() < currentBlock->getLeft())
					isOnGround = false;
			}
		}
		if (getRight() > currentBlock->getRight())
		{
			if (getLeft() > currentBlock->getRight())
				isOnGround = false;
		}

		if (!isOnGround)
		{
			moveY(-8);
			if (getY() <= currentGroundY - 32)
			{
				isOnGround = true;
				currentGroundY -= 32;
				setY(currentGroundY);
			}
		}

		break;
	default: break;
	}
}

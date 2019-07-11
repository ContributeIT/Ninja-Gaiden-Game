#include "Boss3.h"
#include "Collision.h"
#include "math.h"

#define PI 3.14159265

Boss3::Boss3()
{
	setCollisionType(COLLISION_TYPE_ENEMY);
	setSize(DEFAULT_BOSS_3_WIDTH, DEFAULT_BOSS_3_HEIGHT);
	HP = MAX_HP;

	for (int i = 0; i < 3; i++)
	{
		bullet[i] = new Boss3Bullet();
	}
}

Boss3::Boss3(float x, float y)
{
	setCollisionType(COLLISION_TYPE_ENEMY);
	setSize(DEFAULT_BOSS_3_WIDTH, DEFAULT_BOSS_3_HEIGHT);
	spawnX = x;
	spawnY = y;
	isExist = false;
	HP = MAX_HP;

	for (int i = 0; i < 3; i++)
	{
		bullet[i] = new Boss3Bullet();
	}
}

Boss3::~Boss3()
{
}

void Boss3::Init(GameObject * player)
{
	isExist = true;
	isAlive = true;
	setSize(DEFAULT_BOSS_3_WIDTH, DEFAULT_BOSS_3_HEIGHT);

	directionChanged = false;
	isJumping = false;
	setX(spawnX);
	setY(spawnY + getHeight());
	setVelX(DEFAULT_BOSS_3_VELOCITY);
	setVelY(DEFAULT_BOSS_3_VELOCITY);
	directionX = -1;

	isAttacking = true;
	startCooldown = GetTickCount();
	jumpCount = 0;

	status = ENEMY_STANDING;
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 1, 1);
	if (directionX > 0)
	{
		sprite->LoadTexture("images/enemies/Boss3_right.png", D3DCOLOR_XRGB(0, 0, 128));
	}
	else
	{
		sprite->LoadTexture("images/enemies/Boss3_left.png", D3DCOLOR_XRGB(0, 0, 128));
	}
}

void Boss3::SetStatus(ENEMY_STATUS status)
{
	switch (status)
	{
	case ENEMY_STANDING:
		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 1, 1);
		if (directionChanged)
		{
			if (directionX > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Boss3_right.png", D3DCOLOR_XRGB(0, 0, 128));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Boss3_left.png", D3DCOLOR_XRGB(0, 0, 128));
			}
			directionChanged = false;
		}
		break;
	case ENEMY_MOVING:
		setVelX(DEFAULT_BOSS_3_VELOCITY * directionX);

		sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 0);
		if (directionChanged)
		{
			if (directionX > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Boss3_right.png", D3DCOLOR_XRGB(0, 0, 128));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/enemies/Boss3_left.png", D3DCOLOR_XRGB(0, 0, 128));
			}
			directionChanged = false;
		}
		break;
	default:
		break;
	}
}

void Boss3::Update(DWORD dt, GameObject & player)
{
	if (isAlive)
	{
		timer.tickPerAnim = dt;

		autoMove(0);
		periodAttack(BOSS_3_COOLDOWN_JUMP);
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

	if (HP <= 0) Die();
}

void Boss3::autoMove(float range)
{
	if (!isAttacking && getBottom() == spawnY)
	{
		directionX = getMidX() < 640 ? 1 : -1;	// có thể thay 640 bằng (mapStart + mapEnd) / 2
		directionChanged = true;
	}

	// Xử lý nhảy
	if (isJumping)
	{
		SetStatus(ENEMY_MOVING);

		if (getLeft() >= 528 && getRight() <= 744)
		{
			selfMovingX();
		}

		if (getY() >= 160)
		{
			directionY = -1;
		}
		
		moveY(DEFAULT_BOSS_3_VELOCITY * directionY);

		if (getBottom() < spawnY)
		{
			setY(spawnY + getHeight());
			isJumping = false;
			SetStatus(ENEMY_STANDING);
		}
	}

	// Giới hạn
	if (getLeft() < 528)
		setX(528);
	if (getRight() > 744)
		setX(704);
}

void Boss3::periodAttack(DWORD cooldown)
{
	// isAttacking = false <=> sẵn sàng tấn công => thực hiện tấn công
	if (!isAttacking)
	{
		isAttacking = true;
		isJumping = true;
		directionY = 1;
		startCooldown = GetTickCount();

		// Xử lý tấn công
		jumpCount++;

		if (jumpCount == 3)
		{
			float prevY = 62;
			DWORD delayTime = 250;
			for (int i = 0; i < 3; i++)
			{
				bullet[i]->directionX = directionX;
				bullet[i]->Init(getMidX(), prevY);
				bullet[i]->setDelay(delayTime);
				prevY -= 16;
				delayTime += 150;
			}

			jumpCount = 0;
		}
	}
	// đã attack thì bắt đầu chờ cd
	else
	{
		if (GetTickCount() - startCooldown >= cooldown)
		{
			isAttacking = false;
			bullet[0]->isExist = false;
			bullet[1]->isExist = false;
			bullet[2]->isExist = false;
		}

		// update viên đạn bay
		for (int i = 0; i < 3; i++)
		if (bullet[i]->isExist)
		{
			Collision::CollisionHandle(*Player::getInstance(), *bullet[i]);
			bullet[i]->Update(0, *Player::getInstance());
		}
		else
		{
			bullet[i]->Release();
		}
	}
}

void Boss3::decrease_HP(int HP)
{
	if (!isInvincible)
	{
		this->HP -= HP * 5;

		isInvincible = true;
		startInvincible = GetTickCount();

		if (this->HP <= 0)
		{
			//Die();
		}
	}
	else
	{
		if (GetTickCount() - startInvincible >= invincibleTime)
		{
			isInvincible = false;
		}
	}
}

void Boss3::Die()
{
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
}

void Boss3::resetAllStats()
{
	HP = BOSS_3_MAX_HP;
}

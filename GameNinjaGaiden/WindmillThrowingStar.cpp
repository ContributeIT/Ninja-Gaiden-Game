#include "WindmillThrowingStar.h"
#include "Player.h"


WindmillThrowingStar::WindmillThrowingStar()
{
	setSize(DEFAULT_WINDMILL_THROWING_STAR_WIDTH, DEFAULT_WINDMILL_THROWING_STAR_HEIGHT);
	isExist = false;
	setType(UIT_WINDMILL_THROWING_STAR);

	startAnimation = true;
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	sprite->LoadTexture("images/items/windmill_throwing_star.png", D3DCOLOR_XRGB(0, 128, 128));
}


WindmillThrowingStar::~WindmillThrowingStar()
{
}

void WindmillThrowingStar::Init(float x, float y)
{
	setX(x);
	setY(y);
	spawnX = x;
	isExist = true;
	isUsed = false;
	startExist = GetTickCount();
	directionY = 1;
	//setObjectType(ENEMY_BOSS_3_BULLET);
	//setCollisionType(COLLISION_TYPE_ENEMY);
	setVelX(DEFAULT_WINDMILL_THROWING_STAR_VELOCITY * directionX);

}

void WindmillThrowingStar::Update()
{
	timer.tickPerAnim = 100;
	autoMove();
	Draw();

	if (GetTickCount() - startExist >= EXIST_TIME)
	{
		isExist = false;
	}
}

void WindmillThrowingStar::autoMove()	//	[incompleted]
{
	Player * player = Player::getInstance();

	selfMovingX();

	// xét tâm chuyển động mới
	if ((player->directionX == -1 && (getMidX() <= spawnX - range || 
										getMidX() >= player->getMidX() + range)) ||
		(player->directionX == 1 && (getMidX() >= spawnX + range ||
										getMidX() <= player->getMidX() - range)))
	{
		spawnX = player->getMidX();
	}

	// bay qua bay lại
	if (!(getMidX() >= spawnX - range && getMidX() <= spawnX + range))
	{
		if (getMidX() < spawnX - range)
		{
			directionX = 1;
			setX(spawnX - range - getWidth() / 2);
		}
		else if (getMidX() > spawnX + range)
		{
			directionX = -1;
			setX(spawnX + range - getWidth() / 2);
		}
		setVelX(DEFAULT_WINDMILL_THROWING_STAR_VELOCITY * directionX);
	}

	// bay lên bay xuống theo nhân vật
	float Y = player->getMidY() + getHeight() / 2;
	float velY = DEFAULT_WINDMILL_THROWING_STAR_VELOCITY / 2;
	if ((directionX == 1 && getMidX() <= player->getMidX()) ||
		(directionX == -1 && getMidX() >= player->getMidX()))
	{
		if (getMidY() > Y)
		{
			if (getMidY() - Y < velY)
			{
				moveY(-(getMidY() - Y));
			}
			else
				moveY(-velY);
		}
		else if (getMidY() < Y)
		{
			if (Y - getMidY() < velY)	// ^_^
			{
				moveY(Y - getMidY());
			}
			else
				moveY(velY);
		}
	}
}
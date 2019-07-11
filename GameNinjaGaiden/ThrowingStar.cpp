#include "ThrowingStar.h"


ThrowingStar::ThrowingStar()
{
	setSize(DEFAULT_THROWING_STAR_WIDTH, DEFAULT_THROWING_STAR_HEIGHT);
	isExist = false;
	setType(UIT_THROWING_STAR);

	startAnimation = true;
	sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
	sprite->LoadTexture("images/items/throwing_star.png", D3DCOLOR_XRGB(0, 128, 128));
}


ThrowingStar::~ThrowingStar()
{
}

void ThrowingStar::Init(float x, float y)
{
	setX(x);
	setY(y);
	spawnX = getMidX();
	isExist = true;
	isUsed = false;
	setVelX(DEFAULT_THROWING_STAR_VELOCITY * directionX);
}

void ThrowingStar::Update()
{
	timer.tickPerAnim = 100;
	autoMove();
	Draw();
}

void ThrowingStar::autoMove()
{
	selfMovingX();

	if (!(getMidX() >= spawnX - range && getMidX() <= spawnX + range))
	{
		isExist = false;
	}
}

#pragma once
#include "Enemy.h"

#define DEFAULT_BOSS_3_BULLET_WIDTH		7
#define DEFAULT_BOSS_3_BULLET_HEIGHT	7
#define DEFAULT_BOSS_3_BULLET_VELOCITY	8

class Boss3Bullet :
	public Enemy
{
	DWORD startDelay, delayTime;
public:
	Boss3Bullet();
	~Boss3Bullet();
	void setDelay(DWORD delayTime) { this->delayTime = delayTime; }

	void Init(float x, float y);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


#pragma once
#include "Enemy.h"

#define DEFAULT_CANNON_BULLET_WIDTH 8
#define DEFAULT_CANNON_BULLET_HEIGHT 16
#define DEFAULT_CANNON_BULLET_VELOCITY 8
// thời gian tóe lửa 0.2s
#define FIRE_TIME 200

class CannonBullet :
	public Enemy
{
public:
	// để làm hiệu ứng tóe lửa ^_^
	DWORD startFire;

	CannonBullet();
	~CannonBullet();

	float getRealWidth() { return DEFAULT_CANNON_BULLET_WIDTH; }

	void Init(float x, float y);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


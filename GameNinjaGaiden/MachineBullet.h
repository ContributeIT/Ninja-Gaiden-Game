#pragma once
#include "Enemy.h"

#define DEFAULT_MACHINEGUN_BULLET_WIDTH 8
#define DEFAULT_MACHINEGUN_BULLET_HEIGHT 16
#define DEFAULT_MACHINEGUN_BULLET_VELOCITY 8
// thời gian tóe lửa 0.2s
#define FIRE_TIME 200

class MachineBullet :
	public Enemy
{
public:
	// để làm hiệu ứng tóe lửa ^_^
	DWORD startFire;

	MachineBullet();
	~MachineBullet();

	float getRealWidth() { return DEFAULT_MACHINEGUN_BULLET_WIDTH; }

	void Init(float x, float y);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


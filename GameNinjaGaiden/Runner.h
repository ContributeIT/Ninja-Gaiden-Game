#pragma once
#include "Enemy.h"

#define	DEFAULT_RUNNER_WIDTH	16
#define DEFAULT_RUNNER_HEIGHT	32
#define DEFAULT_RUNNER_VELOCITY	4

class Runner :
	public Enemy
{
public:
	Runner();
	Runner(float x, float y);
	~Runner();

	void Init(GameObject * player);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


#pragma once
#include "Enemy.h"

#define DEFAULT_BANSHEE_WIDTH	24
#define DEFAULT_BANSHEE_HEIGHT	32
#define DEFAULT_BANSHEE_VELOCITY	2

class Banshee :
	public Enemy
{


public:
	Banshee();
	Banshee(float x, float y);
	~Banshee();

	void Init(GameObject * player);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


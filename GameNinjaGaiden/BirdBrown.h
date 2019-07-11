#pragma once
#include "Enemy.h"

#define DEFAULT_BIRD_BROWN_WIDTH	18
#define DEFAULT_BIRD_BROWN_HEIGHT	30
#define DEFAULT_BIRD_BROWN_VELOCITY_X	5
#define DEFAULT_BIRD_BROWN_VELOCITY_Y	4

class BirdBrown :
	public Enemy
{
	float seekRange;
	float playerMidX;
	float playerRange;
	bool playerIsInSeekRange;

	int spawnDirectionX;
public:
	BirdBrown();
	BirdBrown(float x, float y);
	~BirdBrown();

	void Init(GameObject * player);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range, GameObject * player);
};


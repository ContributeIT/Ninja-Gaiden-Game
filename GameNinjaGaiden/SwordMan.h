#pragma once
#include "Enemy.h"

#define DEFAULT_SWORD_MAN_WIDTH		24
#define DEFAULT_SWORD_MAN_HEIGHT	40
#define DEFAULT_SWORD_MAN_VELOCITY	2

class SwordMan :
	public Enemy
{
public:
	SwordMan();
	SwordMan(float x, float y);
	~SwordMan();

	void Init(GameObject * player);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


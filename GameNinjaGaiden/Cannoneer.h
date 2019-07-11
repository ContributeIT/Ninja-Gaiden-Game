#pragma once
#include "Enemy.h"
#include "CannonBullet.h"

#define	DEFAULT_CANNONEER_WIDTH		28
#define DEFAULT_CANNONEER_HEIGHT	32

class Cannoneer :
	public Enemy
{
	CannonBullet * bullet;

public:
	Cannoneer();
	Cannoneer(float x, float y);
	~Cannoneer();

	void Init(GameObject * player);
	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
	void periodAttack(DWORD cooldown);
};


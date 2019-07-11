#include "Enemy.h"
#include "MachineBullet.h"

#define DEFAULT_MACHINE_GUN_GUY_WIDTH	16
#define DEFAULT_MACHINE_GUN_GUY_HEIGHT	32
#define DEFAULT_MACHINE_GUN_GUY_VELOCITY	2

class MachineGunGuy :
	public Enemy
{
	MachineBullet * bullet;

public:
	
	MachineGunGuy();
	MachineGunGuy(float x, float y);
	~MachineGunGuy();

	void Init(GameObject * player);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);
	void autoMove(float range);
	void periodAttack(DWORD cooldown);
};


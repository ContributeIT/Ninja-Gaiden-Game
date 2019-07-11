#include "Enemy.h"
#include "GameObject.h"

#define DEFAULT_BAT_WIDTH	48
#define DEFAULT_BAT_HEIGHT	32

class Bat :
	public Enemy
{


public:
	Bat();
	Bat(float x, float y);
	~Bat();

	void Init(GameObject * player);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


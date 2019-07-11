#include "Enemy.h"

#define DEFAULT_CAT_WIDTH	31
#define DEFAULT_CAT_HEIGHT	15
#define DEFAULT_CAT_VELOCITY	5

class Cat :
	public Enemy
{


public:
	Cat();
	Cat(float x, float y);
	~Cat();

	void Init(GameObject * player);

	void SetStatus(ENEMY_STATUS status);
	void Update(DWORD dt, GameObject &player);

	void autoMove(float range);
};


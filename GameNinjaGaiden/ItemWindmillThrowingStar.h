#include "Item.h"
#include "WindmillThrowingStar.h"

class ItemWindmillThrowingStar :
	public Item
{
	WindmillThrowingStar * item;
public:
	ItemWindmillThrowingStar();
	~ItemWindmillThrowingStar();

	void Init(float x, float y);
	void CheckCollisionStatus(GameObject * player);
};




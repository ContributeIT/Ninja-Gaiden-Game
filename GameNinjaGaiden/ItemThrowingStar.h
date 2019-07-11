#include "Item.h"
#include "ThrowingStar.h"

class ItemThrowingStar :
	public Item
{
	ThrowingStar * item;
public:
	ItemThrowingStar();
	~ItemThrowingStar();

	void Init(float x, float y);
	void CheckCollisionStatus(GameObject * player);
};




#include "Item.h"

enum ITEM_FIRE_WHEEL_TYPE
{
	FIRE_WHEEL_ART,
};

class ItemFireWheelArt :
	public Item
{
	ITEM_FIRE_WHEEL_TYPE type;
public:
	ItemFireWheelArt();
	~ItemFireWheelArt();

	void setType(ITEM_FIRE_WHEEL_TYPE type);
	ITEM_FIRE_WHEEL_TYPE getType();

	void Init(float x, float y);
	void CheckCollisionStatus(GameObject * player);
};




#include "Item.h"

enum ITEM_TIME_FREEZE_TYPE
{
	TIME_FREEZE,
};

class ItemTimeFreeze :
	public Item
{
	ITEM_TIME_FREEZE_TYPE type;
public:
	ItemTimeFreeze();
	~ItemTimeFreeze();

	void setType(ITEM_TIME_FREEZE_TYPE type);
	ITEM_TIME_FREEZE_TYPE getType();

	void Init(float x, float y);
	void CheckCollisionStatus(GameObject * player);
};




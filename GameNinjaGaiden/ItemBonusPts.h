#include "Item.h"

enum ITEM_BONUS_TYPE
{
	BONUS_500_PTS,
	BONUS_1000_PTS,
};

class ItemBonusPts :
	public Item
{
	ITEM_BONUS_TYPE type;
public:
	ItemBonusPts();
	~ItemBonusPts();

	void setType(ITEM_BONUS_TYPE type);
	ITEM_BONUS_TYPE getType();

	void Init(float x, float y);
	void CheckCollisionStatus(GameObject * player);
};



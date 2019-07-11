#include "Item.h"

enum ITEM_RESTORE_PHYSICAL_STRENGTH_TYPE
{
	HP_RECOVER,
};

class ItemRestorePhysicalStrength :
	public Item
{
	ITEM_RESTORE_PHYSICAL_STRENGTH_TYPE type;
public:
	ItemRestorePhysicalStrength();
	~ItemRestorePhysicalStrength();

	void setType(ITEM_RESTORE_PHYSICAL_STRENGTH_TYPE type);
	ITEM_RESTORE_PHYSICAL_STRENGTH_TYPE getType();

	void Init(float x, float y);
	void CheckCollisionStatus(GameObject * player);
};




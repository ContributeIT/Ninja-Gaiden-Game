#pragma once
#include "MovableRect.h"
#include "Sprite.h"

typedef struct SpriteTimer
{
	DWORD startTime = 0;
	DWORD tickPerAnim = 0;

	bool isAtTime()
	{
		if (GetTickCount() - startTime >= tickPerAnim)
		{
			startTime = GetTickCount();
			return true;
		}
		return false;
	}
} ObjTimer;

// loại đối tượng (bao gồm enemy và item)
enum GAME_OBJECT_TYPE
{
	ENEMY_ARMOR_SWORD_MAN = 1,
	ENEMY_BANSHEE = 2,				//
	ENEMY_BAT_BROWN = 3,			//
	ENEMY_BAT_MAN = 4,
	ENEMY_BIRD_BROWN = 5,			//
	ENEMY_BIRD_GREY = 6,
	ENEMY_BOXER = 7,
	ENEMY_DOG = 8,
	ENEMY_KNIFE_THROWER = 9,
	ENEMY_MACHINE_GUN_GUY = 10,		//
	ENEMY_GUNNER = 11,
	ENEMY_SWORD_MAN = 12,			//
	ENEMY_CAT = 13,					//
	ENEMY_CANNONEER = 14,			//
	ENEMY_RUNNER = 15,				//
	ITEM_ITEM_CONTAINER_1 = 21,
	ITEM_ITEM_CONTAINER_2 = 22,
	ITEM_ITEM_CONTAINER_3 = 23,
	ITEM_ITEM_CONTAINER_4 = 24,		//
	ITEM_ITEM_CONTAINER_5 = 25,		// and so on...
	ENEMY_BOSS_3 = 33,					//
	ENEMY_MACHINE_BULLET = 40,		//
	ENEMY_CANNON_BULLET = 41,		//
	ENEMY_BOSS_3_BULLET = 42,		//
	OBJECT_GROUND = 50,
};

// loại va chạm
enum COLLISION_TYPE
{
	COLLISION_TYPE_GROUND,
	COLLISION_TYPE_ENEMY,
	COLLISION_TYPE_ITEM,
	COLLISION_TYPE_NOTHING,
};
// Loại item
enum ITEM_TYPE
{
	ITEM_SPIRITUAL_STR_5_PTS = 1,
	ITEM_SPIRITUAL_STR_10_PTS = 2,
	ITEM_TIME_FREEZE = 3,
	ITEM_THROWING_STAR = 4,
	ITEM_BONUS_500_PTS = 5,
	ITEM_BONUS_1000_PTS = 6,
	ITEM_FIRE_WHEEL_ART = 7,
	ITEM_HP_RECOVER = 8,
	ITEM_WINDMILL_THROWING_STAR = 9,
};

// trạng thái của player
enum PLAYER_STATUS
{
	PLAYER_NULL,
	PLAYER_STANDING,
	PLAYER_MOVING,
	PLAYER_JUMPING,
	PLAYER_END_JUMPING,
	PLAYER_KNOCKBACK,
	PLAYER_INVINCIBLE,
	PLAYER_ATTACK,
	PLAYER_JUMP_ATTACK,
	PLAYER_CLINGING,
	PLAYER_CLIMBING,
	PLAYER_ITEM_USE,
	PLAYER_DIE,
};

class GameObject :
	public MovableRect
{
protected:
	Sprite * sprite;
	ObjTimer timer;

	GAME_OBJECT_TYPE objType;
	COLLISION_TYPE clsType;

	float realWidth;

	DWORD startFreezeTime, freezeTime;
	bool isFreezing = false;
public:
	float nx = 0.0f, ny = 0.0f;
	float collisionTime = 1.0f;

	float e_nx = 0.0f, e_ny = 0.0f, e_collisionTime = 1.0f;

	GameObject * currentBlock = NULL;

	bool startAnimation;
	int directionX, directionY;
	bool isExist;
	bool isInCellsSet;

	// player only
	bool isMoving;
	bool isJumping;
	bool isClimbing;
	bool isInvincible;
	bool isKnockback;
	bool isOnGround;
	bool isAttacking;
	bool isDead;

	GameObject();
	~GameObject();

	// Player only
	virtual void setMinJumpHeight(float) {}
	virtual float getMinJumpHeight() { return 0.0f; }
	virtual void resetMaxJumpHeight() {}
	virtual void setMaxJumpHeight(float) {}
	virtual float getMaxJumpHeight() { return 0.0f; }
	virtual float getDefaultPlayerWidth() { return 0.0f; }
	virtual float getDefaultPlayerHeight() { return 0.0f; }
	virtual void SetStatus(PLAYER_STATUS, int = 1) {}
	virtual float getRealWidth() { return 0.0f; }
	virtual void setMinClimbHeight(float) {}
	virtual float getMinClimbHeight() { return 0.0f; }
	virtual void setMaxClimbHeight(float) {}
	virtual float getMaxClimbHeight() { return 0.0f; }
   
	// Dùng trong Collision.cpp để lấy thông tin va chạm
	// lưu thông tin va chạm vào những thứ sẽ va chạm với nhân vật
	void UpdateCollisionStatus(int nx, int ny, float collisionTime);
	virtual void CheckCollisionStatus(GameObject * player);

	// Enemies, items, ground
	void setObjectType(GAME_OBJECT_TYPE objectType);
	GAME_OBJECT_TYPE getObjectType();
	void setCollisionType(COLLISION_TYPE collisionType);
	COLLISION_TYPE getCollisionType();
	// Bosses
	virtual bool isBoss() { return false; }
	virtual int getMaxHP() { return 0; }
	virtual int getHP() { return 0; }
	virtual void decrease_HP(int i = 1) {}
	virtual void resetAllStats() {}

	// ItemContainer
	virtual void setItemTypeID(int id) {}
	virtual void setItemBase(float base) {}

	// General
	virtual void Init();
	virtual void Init(GameObject * player) {}
	virtual void setSpawned(bool isSpawned) {}	// dành cho enemy	
	virtual void Update(DWORD dt, GameObject &player);

	void Freeze(DWORD time);
	void Draw();
	void Release();
};
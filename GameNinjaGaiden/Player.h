#pragma once
#include "GameObject.h"
#include "UsableItem.h"

#define DEFAULT_VELOCITY_X	4
#define DEFAULT_VELOCITY_Y	8
#define DEFAULT_CLIMB_VELOCITY 4
#define DEFAULT_WIDTH 20
#define DEFAULT_HEIGHT	32
#define DEFAULT_JUMP_HEIGHT 56

#define MAX_HP 20
#define MAX_SPIRITUAL_STRENGTH_PTS 99

// Mỗi lần nhảy cách nhau 1 tí xíu
#define COOLDOWN_JUMP 300
// bị đẩy lùi delay 0.3s
#define KNOCKBACK_TIME 500
// mỗi lần bất tử sẽ kéo dài 1.5s từ lúc bắt đầu bị knockback do va chạm enemy
#define INVINCIBLE_TIME 1500
// delay mỗi cái chớp chớp
#define BLINK_DELAY 100
// mỗi đòn tấn công kéo dài 0.5s
#define ATTACK_TIME 500
#define THROWING_TIME 250

class Player :
	public GameObject
{
	static Player * instance;

	PLAYER_STATUS status;
	
	DWORD startCooldownJump;
	DWORD startKnockback;
	DWORD startInvincible;
	DWORD stopDrawing;	bool isStopDrawing;
	DWORD startAttack;
	DWORD startThrowing;

	float minHeight, maxHeight;
	float minClimbHeight, maxClimbHeight;

	/********** Này kia các thứ: **********/
	int score;
	int HP;
	int life;
	int spiritualStr;
	UsableItem * item;	// nhớ là chỉ dùng cho các item có hiển thị trên UI nhé

	// Người hãy quên em đi, vì em sử dụng singleton pattern
	Player();
	~Player();
public:
	bool isMovable;
	bool isJumpable;
	bool directionChanged;
	bool isThrowing;
	bool hasItem;

	bool started = false;
	// attack animation trick
	bool X_moved;

	static Player * getInstance();
	
	void setMinJumpHeight(float minHeight);		// set min dưới chân
	float getMinJumpHeight() { return minHeight; }
	void resetMaxJumpHeight() { maxHeight = minHeight + DEFAULT_JUMP_HEIGHT; }
	void setMaxJumpHeight(float maxHeight);		// set max trên đầu
	float getMaxJumpHeight() { return maxHeight; }

	float getDefaultPlayerWidth() { return DEFAULT_WIDTH; }
	float getDefaultPlayerHeight() { return DEFAULT_HEIGHT; }
	float getRealWidth() { return realWidth; }

	void setMinClimbHeight(float minClimbHeight);
	float getMinClimbHeight() { return minClimbHeight; }
	void setMaxClimbHeight(float maxClimbHeight);
	float getMaxClimbHeight() { return maxClimbHeight; }

	// Nhập x, y là điểm dưới trái của nhân vật
	void InitPlayer(float x, float y);
	void SetStatus(PLAYER_STATUS status, int direction = 1);
	void Update(DWORD dt);

	/********** Này kia các thứ **********/
	void setScore(int score);	int getScore() { return score; }
	void setHP(int HP);			int getHP() { return HP; }
	void setLife(int life);		int getLife() { return life; }
	int getMaxHP() { return MAX_HP; }
	void setSpiritualStrength(int spiritualStr);
	int getSpiritualStrength() { return spiritualStr; }
	void setItem(UsableItem * item);
	UsableItem * getItem() { return item; }
	/********** Advanced **********/
	void addScore(int score);
	void increase_HP(int HP = 1);
	void decrease_HP(int HP = 1);
	void increase_life(int life = 1);
	void decrease_life(int life = 1);
	void increase_spiritualStrength(int ss);
	void decrease_spiritualStrength(int ss);
	
	void resetAllStats();
};


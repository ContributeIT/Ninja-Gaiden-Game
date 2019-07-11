#pragma once
#include "GameTexture.h"
#include <string>
#include "Player.h"

class Scorebar
{
	static Scorebar * instance;

	int Hpbar;

	int playChance;
	int bossHealth;
	int playerHealth;
	int maxHealth;
	int spiritualStr;
	int score;
	int time;
	int act;

	ID3DXFont *FONT;
	Rect *rect;
	std::string m;

	Player * player = Player::getInstance();

	GameTexture *gameTexture;

	Scorebar();
	~Scorebar();
public:

	static Scorebar * getInstance();

	bool Init();
	void Draw(int x, int y);
	void Update();
};
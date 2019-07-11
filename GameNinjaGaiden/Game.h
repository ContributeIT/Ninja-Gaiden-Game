#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameWindow.h"
#include "Sprite.h"
#include "Camera.h"
#include "Player.h"
#include "Stage.h"

#include "Collision.h"

typedef struct GameTimer
{
	DWORD startTime = 0;
	DWORD tickPerFrame = 0;

	bool isAtTime()
	{
		if (GetTickCount() - startTime >= tickPerFrame)
		{
			startTime = GetTickCount();
			return true;
		}
		return false;
	}
} Timer;

class Game
{
	static Game * instance;

	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddev = NULL;
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DSURFACE9 backbuffer = NULL;

	LPD3DXSPRITE spriteHandler;

	// con trỏ player
	Player * Ryu = Player::getInstance();
	// con trỏ camera
	Camera * camera = Camera::getInstance();

	// con trỏ stage
	Stage * stage = Stage::getInstance();

	// Stage
	int stageIndex = 0;
	const int NUMBER_OF_STAGES = 3; // làm có 3 stage thôi

	Timer timer;

	DWORD startCooldown_R = GetTickCount();
	bool canJump = true;
public:
	bool allowHurtingPlayer = true;

	static Game * getInstance();

	Game();
	~Game();

	void InitDirectX();
	void InitGame();

	int getStageIndex() { return stageIndex; }
	LPDIRECT3DDEVICE9 get3DDevice();
	LPD3DXSPRITE getSpriteHandler();

	void init();
	void run();
	void update();
	void end();

	void KeysControl();
};


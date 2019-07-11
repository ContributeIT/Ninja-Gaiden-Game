#include "Game.h"
#include <time.h>
#include "DXInput.h"
#include "Scorebar.h"

#include <string>

#define BACKBUFFER_WIDTH 256
#define BACKBUFFER_HEIGHT 216
#define FPS 60

#define WINDOW_CLASS "GameWindow"
#define WINDOW_TITLE "Game"

Game * Game::instance = NULL;
Game * Game::getInstance()
{
	if (instance == NULL)
	{
		instance = new Game();
	}
	return instance;
}

Game::Game()
{
	this->hWnd = GameWindow::getInstance()->getHandleWindow();
}


Game::~Game()
{
}

LPDIRECT3DDEVICE9 Game::get3DDevice()
{
	return this->d3ddev;
}

LPD3DXSPRITE Game::getSpriteHandler()
{
	return this->spriteHandler;
}

void Game::init()
{
	// DirectX init
	InitDirectX();

	// Game init
	InitGame();

	// Scorebar init
	Scorebar::getInstance()->Init();

	// Keyboard init
	if (!Init_Keyboard(hWnd))
	{
		//MessageBox(hWnd, "Error initializing the keyboard", "Error", MB_OK);
			return;
	}
}

void Game::InitDirectX()
{
	HRESULT result;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// d3d present parameters
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = BACKBUFFER_WIDTH;
	d3dpp.BackBufferHeight = BACKBUFFER_HEIGHT;
	d3dpp.hDeviceWindow = hWnd;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hWnd, "Error initializing Direct3D", "Error",
			MB_OK);
		return;
	}
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		NULL,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);

	// backbuffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	D3DXCreateSprite(d3ddev, &spriteHandler);
}

void Game::InitGame()
{
	//srand(time(NULL));

	// Game Timer
	timer.startTime = GetTickCount();
	timer.tickPerFrame = 1000 / FPS;

	// Load stage
	float groundLine;
	switch (stageIndex)
	{
	case 0:
		#pragma region Stage 3-1
		// Map
		stage->LoadTilemap("images/Stage31/3_1_tilesheet.png", "images/Stage31/3_1_matrix.txt");
		stage->LoadGroundBlocks("images/Stage31/ground_blocks.txt");
		stage->setPlayerStart(16);
		groundLine = 38;
		// Camera
		camera->setX(stage->getMapStart());
		// Enemy
		stage->InitGrid("images/Stage31/grid_info.txt", "images/Stage31/cells_info.txt");
		break;
#pragma endregion
	case 1:
		#pragma region Stage 3-2
		// Map
		stage->LoadTilemap("images/Stage32/3_2_tilesheet.png", "images/Stage32/3_2_matrix.txt");
		stage->LoadGroundBlocks("images/Stage32/ground_blocks.txt");
		stage->setPlayerEnd(stage->getMapEnd() - 16);
		groundLine = 38;
		// Camera
		camera->setX(stage->getMapStart());
		// Enemy
		stage->InitGrid("images/Stage32/grid_info.txt", "images/Stage32/cells_info.txt");
		break;
#pragma endregion
	case 2:
		#pragma region Stage 3-3
		// Map
		stage->LoadTilemap("images/Stage33/3_3_tilesheet.png", "images/Stage33/3_3_matrix.txt");
		stage->LoadGroundBlocks("images/Stage33/ground_blocks.txt");
		stage->setMapStart(512);
		stage->setPlayerStart(544);
		groundLine = 22;
		// Camera
		camera->setX(stage->getMapStart());
		// Enemy
		stage->InitGrid("images/Stage33/grid_info.txt", "images/Stage33/cells_info.txt");
		break;
#pragma endregion
	}

	// Player Ryu
	Ryu->InitPlayer(stage->getPlayerStart() - 16, groundLine);
}

void Game::run()
{
	// Kiểm tra device
	if (d3ddev == NULL)
		return;

	// update keyboard
	Poll_Keyboard();

	// Bắt đầu vẽ 1 frame
	if (timer.isAtTime())
	{
		if (d3ddev->BeginScene())
		{
			// Nếu không vẽ gì thì màn hình sẽ đen thui
			d3ddev->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

			// Xử lý phím
			KeysControl();

			// Update các thông số game;
			update();

			// Kết thúc 1 frame
			d3ddev->EndScene();
		}

		// Flip backbuffer lên frontbuffer
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}

void Game::update()
{
	// Vẽ Scorebar
	Scorebar::getInstance()->Update();
	// Vẽ tilemap
	stage->Draw(camera);

	// Update enemy trong stage
	stage->Update(300, Ryu);

	// Vẽ Ryu
	#pragma region Start Stage Animation
	if (!Ryu->started)
	{
		Ryu->SetStatus(PLAYER_MOVING);
		Ryu->moveX(2);

		if (Ryu->getX() >= stage->getPlayerStart())
		{
			Ryu->started = true;
		}
	}
#pragma endregion
	Ryu->Update(60);


	// Đến cuối map -> chuyển stage
	if (Ryu->getRight() >= stage->getPlayerEnd()
		&& !Ryu->isJumping)
	{
		if (stageIndex < NUMBER_OF_STAGES)	// Vượt qua tất cả stage
		{
			stageIndex++;
			if (!(stageIndex < NUMBER_OF_STAGES))	 // ^_^
				stageIndex = 0;

			stage->Release();
			InitGame();
		}
	}
}

void Game::end()
{
	if (backbuffer != NULL) backbuffer->Release();
	//if (spriteHandler != NULL) spriteHandler->Release();
	if (d3ddev != NULL) d3ddev->Release();
	if (d3d != NULL) d3d->Release();
}

void Game::KeysControl()
{
	// ***** Will be deleted ********************************

	if (Key_Down(DIK_LSHIFT) || Key_Down(DIK_RSHIFT))
	{
		Ryu->setVelX(16 * Ryu->directionX);
	}
	else
	{
		Ryu->setVelX(4 * Ryu->directionX);
	}
	// [R] restart stage
	if (Key_Down(DIK_R))
	{
		if (GetTickCount() - startCooldown_R > 500)
		{
			startCooldown_R = GetTickCount();
			stage->Release();
			InitGame();
		}
	}
	// [Q] to turn on invincibility
	if (Key_Down(DIK_Q))
	{
		allowHurtingPlayer = false;
	}
	// [W] to turn off invincibility
	if (Key_Down(DIK_W))
	{
		allowHurtingPlayer = true;
	}
	// [B] test keys menu
	if (Key_Down(DIK_B))
	{
		std::string k1 = "[Q] to turn on invincibility";
		std::string k2 = "[W] to turn off invincibility";
		std::string k3 = "[R] restart stage";
		std::string k4 = "Numpad [1] [2] [3] to switch between stages";
		std::string k5 = "Numpad [4] to jump to the end of stage 3-2 while in stage 3-2";
		std::string k6 = "Hold [SHIFT] to x4 move speed";
		std::string msg = k1 + '\n' + k2 + '\n' + k3 + '\n' + k4 + '\n' + k5 + '\n' + k6;
		MessageBox(0, msg.c_str(), "Keys use for testing", 0);
	}
	// [1] [2] [3] to switch between stages
	if (Key_Down(DIK_NUMPAD1))
	{
		if (stageIndex != 0)
		{
			stageIndex = 0;
			stage->Release();
			InitGame();
		}
	}
	if (Key_Down(DIK_NUMPAD2))
	{
		if (stageIndex != 1)
		{
			stageIndex = 1;
			stage->Release();
			InitGame();
		}
	}
	if (Key_Down(DIK_NUMPAD3))
	{
		if (stageIndex != 2)
		{
			stageIndex = 2;
			stage->Release();
			InitGame();
		}
	}
	if (Key_Down(DIK_NUMPAD4))
	{
		if (stageIndex == 1)
		{
			Ryu->setX(stage->getPlayerEnd() - 320);
			Ryu->setY(134);
			camera->trackPlayer(Ryu);
		}
	}
	// ******************************************************
	if (Ryu->started){

		#pragma region [LEFT] [RIGHT]
		if (Key_Down(DIK_RIGHTARROW) || Key_Down(DIK_LEFTARROW))
		{
			if (!Ryu->isKnockback && !Ryu->isClimbing)
			{
				Ryu->directionX = Key_Down(DIK_RIGHTARROW) ? 1 : -1;

				if (Ryu->getVelX() * Ryu->directionX < 0)
				{
					Ryu->setVelX(-Ryu->getVelX());
					Ryu->directionChanged = true;
				}

				Ryu->isMoving = true;
				if (!Ryu->isJumping && !Ryu->isAttacking)
				{
					Ryu->SetStatus(PLAYER_MOVING, Ryu->directionX);
				}
			}
		}
		// Không di chuyển
		else
		{
			if (!Ryu->isClimbing)
			{
				Ryu->isMoving = false;
				if (!Ryu->isJumping && !Ryu->isKnockback && !Ryu->isAttacking)
				{
					Ryu->SetStatus(PLAYER_STANDING, Ryu->directionX);
				}
			}
		}
	#pragma endregion di chuyển trái phải

		#pragma region [UP] [DOWN]
		if (Key_Down(DIK_UPARROW) || Key_Down(DIK_DOWNARROW))
		{
			if (Ryu->isClimbing)
			{
				Ryu->isMoving = true;
				Ryu->directionY = Key_Down(DIK_UPARROW) ? 1 : -1;

				if (Ryu->getVelY() * Ryu->directionY < 0)
				{
					Ryu->setVelY(-Ryu->getVelY());
					Ryu->directionChanged = true;
				}

				Ryu->SetStatus(PLAYER_CLIMBING, Ryu->directionX);
			}
		}
		else
		{
			if (Ryu->isClimbing)
			{
				Ryu->isMoving = false;
				Ryu->SetStatus(PLAYER_CLINGING, Ryu->directionX);
			}
		}
	#pragma endregion lên xuống khi leo trèo

		#pragma region [Z]
		if (Key_Down(DIK_Z))
		{
			// Không được tấn công lúc đang leo trèo
			if (!Ryu->isClimbing && !Ryu->isKnockback)
			//if (!Ryu->isAttacking)
			{
				if (Ryu->isOnGround && !Ryu->isJumping)
				{
					Ryu->SetStatus(PLAYER_ATTACK, Ryu->directionX);
				}
				else
				{
					Ryu->SetStatus(PLAYER_JUMP_ATTACK, Ryu->directionX);
				}
			}
		}
	#pragma endregion tấn công

		#pragma region [Space] [X]
		if ((Key_Down(DIK_SPACE) || Key_Down(DIK_X)) && !Ryu->isAttacking)
		{
			if (canJump)
			{
				if (Ryu->isClimbing)
				{
					// thiết lập sau khi thoát climbing
					Ryu->isClimbing = false;
					Ryu->setMinJumpHeight(Ryu->getBottom());
					Ryu->setMaxJumpHeight(Ryu->getMinJumpHeight() + 48);
				}

				if (Ryu->isJumpable)
				{
					if (!Ryu->isAttacking && !Ryu->isKnockback)
					{
						if (!Ryu->isJumping && Ryu->isOnGround)
						{
							Ryu->directionY = 1;
							Ryu->SetStatus(PLAYER_JUMPING, Ryu->directionX);
						}
					}
				}
			}
			canJump = false;
		}
		else
		{
			canJump = true;
		}
	#pragma endregion nhảy
		
		#pragma region [C]
		if (Key_Down(DIK_C))
		{
			// ^_^
			if (!Ryu->isClimbing)
			if (!Ryu->isKnockback)
			if (!Ryu->isAttacking)
			if (!Ryu->isThrowing)
			if (Ryu->hasItem)
			if (!Ryu->getItem()->isExist)
			{
				Ryu->getItem()->UseItem();
			}
		}
	#pragma endregion dùng item
	}

	#pragma region [ESC]
	if (Key_Down(DIK_ESCAPE))
	{
		// giải phóng bàn phím
		Kill_Keyboard();
		if (dinput != NULL) dinput->Release();

		end();
		PostMessage(hWnd, WM_DESTROY, 0, 0);
	}
#pragma endregion thoát game
}
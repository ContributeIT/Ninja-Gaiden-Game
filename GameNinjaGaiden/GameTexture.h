#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class GameTexture
{
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE spriteHandler;

public:
	float width, height;

	GameTexture();
	~GameTexture();

	void LoadTexture(const char* imagePath, D3DCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(int x, int y, RECT *r = 0);
	void Release();
};


#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "MovableRect.h"
#include "GameTexture.h"


typedef struct {
	float X, Y;
} myPoint;

class Sprite
{
	myPoint * animation;
	bool startAnimation;
	int currentAnimation, firstAnimation, lastAnimation;

	GameTexture spriteTexture;

	float width, height;
	D3DXVECTOR3 position;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE spriteHandle;
public:
	bool lapDone = false;

	Sprite();
	Sprite(float x, float y);
	~Sprite();

	int getCurrentAnimation();	void setCurrentAnimation(int currentAnimation);
	int getFirstAnimation();	void setFirstAnimation(int firstAnimation);
	int getLastAnimation();		void setLastAnimation(int lastAnimation);

	void LoadTexture(const char * imagePath, D3DCOLOR transColor);
	void SetAnimation(float animationWidth, float animationHeight, int animationCount, int animationsPerRow, int firstAnimation, int lastAnimation);

	void Draw(float x, float y, Rect * rect);
	void Release();

	//chổ thêm
	D3DXVECTOR3 getPosition() { return position; }
	LPDIRECT3DTEXTURE9 LoadTexture(LPDIRECT3DDEVICE9 device, const char *file);
	void Draw(D3DXVECTOR3 pos, RECT *rect);
};


#pragma once
#include "GameObject.h"
class GroundBlock :
	public GameObject
{
	/*	3 loại groundblock:
			1. Có va chạm ngang,
			2. Không va chạm ngang,
			3. Va chạm đúng hướng thì bám luôn (cụ thể stage 3-2 là cầu thang)
	*/
	int groundType;
public:
	GroundBlock(float x, float y, float width, float height, int groundType);
	~GroundBlock();

	bool blockMovingX();

	void CheckCollisionStatus(GameObject * player);

	void Update(DWORD dt, GameObject &player);
};


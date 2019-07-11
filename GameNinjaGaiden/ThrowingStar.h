#pragma once
#include "UsableItem.h"

#define DEFAULT_THROWING_STAR_WIDTH		8
#define DEFAULT_THROWING_STAR_HEIGHT	8
#define DEFAULT_THROWING_STAR_VELOCITY	12


class ThrowingStar :
	public UsableItem
{
	float range = 96;
	float spawnX;
public:

	ThrowingStar();
	~ThrowingStar();

	void Init(float x, float y);

	void Update();

	void autoMove();
};


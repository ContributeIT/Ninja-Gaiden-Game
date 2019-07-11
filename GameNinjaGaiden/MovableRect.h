#pragma once
#include "Rect.h"

class MovableRect :
	public Rect
{
	float velX, velY;

public:
	MovableRect();
	virtual ~MovableRect();

	float getVelX();	void setVelX(float velX);
	float getVelY();	void setVelY(float velY);
	
	// Tự di chuyển theo vận tốc
	void selfMovingX();
	void selfMovingY();

};


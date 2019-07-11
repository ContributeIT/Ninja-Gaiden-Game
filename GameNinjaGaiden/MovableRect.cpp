#include "MovableRect.h"



MovableRect::MovableRect()
{
}


MovableRect::~MovableRect()
{
}

float MovableRect::getVelX()
{
	return velX;
}

void MovableRect::setVelX(float velX)
{
	this->velX = velX;
}

float MovableRect::getVelY()
{
	return velY;
}

void MovableRect::setVelY(float velY)
{
	this->velY = velY;
}

void MovableRect::selfMovingX()
{
	Rect::moveX(velX);
}

void MovableRect::selfMovingY()
{
	Rect::moveY(velY);
}

#include "Rect.h"



Rect::Rect()
{
	posX = posY = width = height = 0;
}


Rect::~Rect()
{
}

float Rect::getX()
{
	return posX;
}

void Rect::setX(float x)
{
	posX = x;
}

float Rect::getY()
{
	return posY;
}

void Rect::setY(float y)
{
	posY = y;
}

float Rect::getWidth()
{
	return width;
}

void Rect::setWidth(float width)
{
	this->width = width;
}

float Rect::getHeight()
{
	return height;
}

void Rect::setHeight(float height)
{
	this->height = height;
}

void Rect::setSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Rect::moveX(float dx)
{
	posX += dx;
}

void Rect::moveY(float dy)
{
	posY += dy;
}

void Rect::move(float dx, float dy)
{
	posX += dx;
	posY += dy;
}

void Rect::moveTo(float x, float y)
{
	posX = x;
	posY = y;
}

float Rect::getLeft()
{
	return posX;
}

float Rect::getRight()
{
	return posX + width;
}

float Rect::getTop()
{
	return posY;
}

float Rect::getBottom()
{
	return posY - height;
}

float Rect::getMidX()
{
	return posX + width / 2;
}

float Rect::getMidY()
{
	return posY - height / 2;
}

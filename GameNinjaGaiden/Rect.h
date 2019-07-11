#pragma once

class Rect
{
	float posX, posY;
	float width, height;

public:
	Rect();
	virtual ~Rect();

	float getX();		void setX(float x);
	float getY();		void setY(float y);
	float getWidth();	void setWidth(float width);
	float getHeight();	void setHeight(float height);

	void setSize(float width, float height);

	// Di chuyển theo khoảng cách nhập vào
	void move(float dx, float dy);
	void moveX(float dx);
	void moveY(float dy);
	// Di chuyển tới điểm x,y
	void moveTo(float x, float y);

	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	float getMidX();
	float getMidY();
};


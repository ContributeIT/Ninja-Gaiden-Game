#include "Collision.h"
#include <iostream>


Collision::Collision()
{
}


Collision::~Collision()
{
}

MovableRect Collision::GetSweptBroadphaseBox(MovableRect box)
{
	MovableRect broadphaseBox;

	broadphaseBox.setX(box.getVelX() > 0 ? box.getX() : box.getX() + box.getVelX());
	broadphaseBox.setY(box.getVelY() > 0 ? box.getY() + box.getVelY() : box.getY());
	broadphaseBox.setWidth(box.getVelX() > 0 ? box.getWidth() + box.getVelX() : box.getWidth() - box.getVelX());
	broadphaseBox.setHeight(box.getVelY() > 0 ? box.getHeight() + box.getVelY() : box.getHeight() - box.getVelY());

	return broadphaseBox;
}

float Collision::SweptAABB(MovableRect box1, MovableRect box2, float & normalx, float & normaly)
{
	// Nếu 2 vật đè lên nhau thì rõ ràng là va chạm
	if (AABBCheck(box1, box2))
	{
		normalx = 0.0f;
		normaly = 1.0f;	// mình thích áp đặt cho nó là dạng va chạm từ trên xuống (box1 ở trên box2)

		return 0.0f;	// collisionTime = 0 luôn;
	}

	// Còn không đè lên nhau thì áp dụng thuật toán quét
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// tìm khoảng cách giữa 2 vật thể ở cạnh gần và cạnh xa
	if (box1.getVelX() > 0.0f)
	{
		xInvEntry = box2.getLeft() - box1.getRight();
		xInvExit = box2.getRight() - box1.getLeft();
	}
	else
	{
		xInvEntry = box2.getRight() - box1.getLeft();
		xInvExit = box2.getLeft() - box1.getRight();
	}

	if (box1.getVelY() > 0.0f)	// lưu ý: trục Oy mình đi ngược so với Oy của console
	{
		yInvEntry = box2.getBottom() - box1.getTop();	// theo lý thuyết thì box1.vy > 0 thì yInvEntry = box2.top - box1.bottom;
		yInvExit = box2.getTop() - box1.getBottom();
	}
	else
	{
		yInvEntry = box2.getTop() - box1.getBottom();
		yInvExit = box2.getBottom() - box1.getTop();
	}

	// Tính thời gian xảy ra va chạm và kết thúc va chạm theo các trục (t = s / v);
	float xEntry, yEntry;
	float xExit, yExit;

	if (box1.getVelX() == 0.0f)		// để tránh chia vận tốc cho 0;
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1.getVelX();
		xExit = xInvExit / box1.getVelX();
	}

	if (box1.getVelY() == 0.0f)		// để tránh chia vận tốc cho 0;
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / box1.getVelY();
		yExit = yInvExit / box1.getVelY();
	}

	// trục nào sẽ xảy ra va chạm trước?
	float entryTime = std::fmaxf(xEntry, yEntry);
	float exitTime = std::fminf(xExit, yExit);

	// Trường hợp không xảy ra va chạm
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	// Trường hợp xảy ra va chạm
	else
	{
		// Xác định chiều của vector pháp tuyến khi va chạm
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// Trả về thời gian sẽ xảy ra va chạm
		return entryTime;
	}
}

bool Collision::AABBCheck(Rect box1, Rect box2)
{
	// trả về true nếu box1 và box2 'giao nhau'
	return !(box1.getRight() < box2.getLeft() || box1.getLeft() > box2.getRight() ||
			box1.getBottom() > box2.getTop() || box1.getTop() < box2.getBottom());
}

void Collision::CollisionHandle(GameObject &box1, GameObject &box2)
{
	float normalx = 0.0f, normaly = 0.0f;
	float collisionTime = 1.0f;

	MovableRect broadphaseBox = GetSweptBroadphaseBox(box1);
	if (AABBCheck(broadphaseBox, box2))
	{
		collisionTime = SweptAABB(box1, box2, normalx, normaly);
	}

	box2.UpdateCollisionStatus(normalx, normaly, collisionTime);
	box2.CheckCollisionStatus(&box1);
}

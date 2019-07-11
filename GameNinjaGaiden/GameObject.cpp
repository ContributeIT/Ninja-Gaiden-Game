#include "GameObject.h"
#include "Collision.h"


GameObject::GameObject()
{
	sprite = new Sprite();

	// ? ? :D ? ?
	timer.startTime = GetTickCount();
	timer.tickPerAnim = 3000;
}


GameObject::~GameObject()
{
	sprite->Release();
}

void GameObject::UpdateCollisionStatus(int nx, int ny, float collisionTime)
{
	this->nx = nx;
	this->ny = ny;
	this->collisionTime = collisionTime;
}

void GameObject::CheckCollisionStatus(GameObject * player)
{
}

void GameObject::setObjectType(GAME_OBJECT_TYPE objectType)
{
	this->objType = objectType;
}

GAME_OBJECT_TYPE GameObject::getObjectType()
{
	return objType;
}

void GameObject::setCollisionType(COLLISION_TYPE collisionType)
{
	this->clsType = collisionType;
}

COLLISION_TYPE GameObject::getCollisionType()
{
	return clsType;
}

void GameObject::Init()
{
}

void GameObject::Update(DWORD dt, GameObject & player)
{
}

void GameObject::Freeze(DWORD time)
{
	isFreezing = true;
	startFreezeTime = GetTickCount();
	freezeTime = time;
}

void GameObject::Draw()
{
	// vòng lặp animation
	if (timer.isAtTime())
	{
		if (startAnimation)
		{
			if (sprite->getCurrentAnimation() == sprite->getLastAnimation())
			{
				sprite->lapDone = true;
				sprite->setCurrentAnimation(sprite->getFirstAnimation());
			}
			else
			{
				sprite->setCurrentAnimation(sprite->getCurrentAnimation() + 1);
			}
		}
		else
		{
			sprite->setCurrentAnimation(sprite->getFirstAnimation());
		}
	}

	// vẽ object
	if (isExist) sprite->Draw(getX(), getY(), this);
}

void GameObject::Release()
{
	//sprite->Release();
}
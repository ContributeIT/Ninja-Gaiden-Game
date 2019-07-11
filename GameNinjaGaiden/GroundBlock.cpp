#include "GroundBlock.h"
#include "Collision.h"
#include "Player.h"
#include <math.h>

#include "DXInput.h"
#include <string>

GroundBlock::GroundBlock(float x, float y, float width, float height, int groundType)
{
	setObjectType(OBJECT_GROUND);
	setCollisionType(COLLISION_TYPE_GROUND);
	this->groundType = groundType;
	setSize(width, height);
	setX(x);
	setY(y + getHeight());
}

GroundBlock::~GroundBlock()
{
}

bool GroundBlock::blockMovingX()
{
	return groundType == 1 ? true : false;
}

void GroundBlock::CheckCollisionStatus(GameObject * player)
{
	if (Player::getInstance()->started)
	//if (collisionTime < 1.0f)
	{
		if (this->blockMovingX())
		{
			if (player->getBottom() < this->getTop())
			{
				// va chạm bên trái block
				if (player->getX() + player->getRealWidth() > this->getLeft() && player->getLeft() < this->getLeft())
				{
					player->setX(this->getLeft() - player->getRealWidth());
				}

				// va chạm bên phải block
				if (player->getRight() - player->getRealWidth() < this->getRight() && player->getRight() > this->getRight())
				{
					player->setX(this->getRight() - player->getWidth() + player->getRealWidth());
				}
			}
		}

		// bám thang
		if (groundType == 3 && (player->isJumping || !player->isOnGround))
		{
			//MessageBox(0, "", "", 0);
			if (player->getTop() < this->getTop())
			{
				// va chạm bên trái block
				if (player->getX() + player->getRealWidth() > this->getLeft() && player->getLeft() < this->getLeft()
					&& Key_Down(DIK_RIGHTARROW))
				{
					player->SetStatus(PLAYER_CLINGING, player->directionX);
					player->setX(this->getLeft() - player->getRealWidth());
					player->setMinClimbHeight(this->getBottom());
					player->setMaxClimbHeight(this->getTop());
				}
				// va chạm bên phải block tương tự
				else
				{
					//... stage 3 ko có trường hợp này ^_^ hihi
				}
			}
		}
	}
}

void GroundBlock::Update(DWORD dt, GameObject &player)
{
	Collision::CollisionHandle(player, *this);
	CheckCollisionStatus(&player);
}

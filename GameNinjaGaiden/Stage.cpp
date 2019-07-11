#include "Stage.h"
#include "Game.h"


// Stage

Stage * Stage::instance = NULL;
Stage * Stage::getInstance()
{
	if (instance == NULL)
	{
		instance = new Stage();
	}
	return instance;
}

Stage::Stage()
{
	mapStart = playerStart = 0;
	tilemap = new Tilemap();
	grid = new Grid();
}

Stage::~Stage()
{
}

int Stage::getMapStart()
{
	return mapStart;
}

void Stage::setMapStart(int mapStart)
{
	this->mapStart = mapStart;
}

int Stage::getMapEnd()
{
	return mapEnd;
}

void Stage::setMapEnd(int mapEnd)
{
	this->mapEnd = mapEnd;
}

int Stage::getPlayerStart()
{
	return playerStart;
}

void Stage::setPlayerStart(int playerStart)
{
	this->playerStart = playerStart;
}

int Stage::getPlayerEnd()
{
	return playerEnd;
}

void Stage::setPlayerEnd(int playerEnd)
{
	this->playerEnd = playerEnd;
}

// OBJECT

void Stage::InitGrid(const char * gridInfoPath, const char * cellsInfoPath)
{
	grid->readGridInfo(gridInfoPath, cellsInfoPath);
	grid->InitGrid(Camera::getInstance());

	if (!grid->isEmpty)
	{
		objectList = grid->GetObjectList(Camera::getInstance());

		prevFirstCellPosition = grid->GetFirstCellPosition();
		prevLastCellPosition = grid->GetLastCellPosition();
	}
}

std::vector<GameObject*> Stage::GetObjectList()
{
	return grid->GetObjectList(Camera::getInstance());
}

std::vector<GameObject*> Stage::GetAllObjects()
{
	return grid->GetObjectList();
}

GameObject * Stage::getBoss()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->isBoss())
			return objectList[i];
	}

	return NULL;
}

void Stage::Update(DWORD dt, Player * player)
{
	// Update grid
	if (!grid->isEmpty)
	{
		// Cập nhật thông tin firstCell và lastCell
		grid->UpdateCellsSet(Camera::getInstance());
		D3DXVECTOR2 firstCellPosition = grid->GetFirstCellPosition();
		D3DXVECTOR2	lastCellPosition = grid->GetLastCellPosition();

		// Khi camera đi vào cell mới của grid thì load object của cell mới zô objectList 
		#pragma region Show code
		if (firstCellPosition.x != prevFirstCellPosition.x || firstCellPosition.y != prevFirstCellPosition.y ||
			lastCellPosition.x != prevLastCellPosition.x || lastCellPosition.y != prevLastCellPosition.y)
		{
			grid->UpdateObjectList(Camera::getInstance());

			// camera dịch qua phải => xóa object của cell bên trái
			if (firstCellPosition.x > prevFirstCellPosition.x || lastCellPosition.x > prevLastCellPosition.x)
			{
				grid->IgnoreLeft(Camera::getInstance());
				if (lastCellPosition.x > prevLastCellPosition.x)
				{
					grid->AddRight(Camera::getInstance(), Player::getInstance());
				}
			}
			// camera dịch qua trái => xóa object của cell bên phải
			else
			{
				grid->IgnoreRight(Camera::getInstance());
				if (firstCellPosition.x < prevFirstCellPosition.x)
				{
					grid->AddLeft(Camera::getInstance(), Player::getInstance());
				}
			}

			objectList.clear();
			objectList.shrink_to_fit();
			objectList = grid->GetObjectList(Camera::getInstance());
			
			prevFirstCellPosition = firstCellPosition;
			prevLastCellPosition = lastCellPosition;
		}
#pragma endregion

		// update các object
		#pragma region Show code
		for (int i = 0; i < objectList.size(); i++)
		{
			GameObject * object = objectList[i];

			if (object->isExist)
			{
				Collision::CollisionHandle(*player, *object);

				// Xác định block đang đứng
				for (int j = 0; j < groundBlocks->getNumberOfBlocks(); j++)
				{
					if (object->getLeft() > groundBlocks->getGroundBlock(j)->getLeft() - object->getWidth() &&
						object->getRight() < groundBlocks->getGroundBlock(j)->getRight() + object->getWidth())
					{
						if (object->getBottom() == groundBlocks->getGroundBlock(j)->getTop() && groundBlocks->getGroundBlock(j)->getWidth() > 16)
							object->currentBlock = groundBlocks->getGroundBlock(j);
					}
				}

				object->Update(dt, *player);
			}
		}
#pragma endregion
	}

	// Update ground
	groundBlocks->Update(dt, *player);
}


// MAP

void Stage::LoadTilemap(const char * imagePath, const char * matrixPath)
{
	tilemap->LoadTilemap(imagePath, matrixPath);

	mapStart = playerStart = 0;
	mapEnd = playerEnd = tilemap->mapWidth;
}

void Stage::LoadGroundBlocks(const char * filePath)
{
	groundBlocks = new GroundBlocks(filePath);
}

void Stage::Draw(Camera * camera)
{
	tilemap->Draw(camera);
}

void Stage::Release()
{
	// tilemap
	tilemap->Release();
	// groundblock;
	delete groundBlocks;
	// grid
	grid->Release();
	//	objectlist
	objectList.clear();
	objectList.shrink_to_fit();
}

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Tilemap.h"
#include "Camera.h"
#include "GameObject.h"
#include <vector>
#include "Player.h"
#include "Grid.h"
#include "GroundBlocks.h"

class Stage
{
	static Stage * instance;

	Tilemap * tilemap;
	GroundBlocks * groundBlocks;

	int mapStart, mapEnd;
	int playerStart, playerEnd;

	std::vector<GameObject*> objectList;

	Grid * grid;
	//D3DXVECTOR2 prevFirstCellPosition;
	//D3DXVECTOR2 prevLastCellPosition;

	Stage();
	~Stage();
public:
	D3DXVECTOR2 prevFirstCellPosition;
	D3DXVECTOR2 prevLastCellPosition;
	static Stage * getInstance();

	int getMapStart();	void setMapStart(int mapStart);
	int getMapEnd();	void setMapEnd(int mapEnd);
	int getPlayerStart();	void setPlayerStart(int playerStart);
	int getPlayerEnd();	void setPlayerEnd(int playerEnd);

	void Update(DWORD dt, Player * player);

	// dùng grid
	void InitGrid(const char * gridInfoPath, const char * cellsInfoPath);
	std::vector<GameObject*> GetObjectList();
	std::vector<GameObject*> GetAllObjects();
	GameObject * getBoss();

	// Tilemap
	void LoadTilemap(const char * imagePath, const char * matrixPath);
	void LoadGroundBlocks(const char * filePath);
	void Draw(Camera * camera);	// vẽ lên camera

	void Release();
};


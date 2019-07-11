#pragma once
#include "GameTexture.h"
#include "Camera.h"

class Tilemap
{
	GameTexture * tilesheet;
	int tileSize;
	int mapCols, mapRows;	// số hàng và cột của map	(tính theo tile)
	int **matrix;	// ma trận các tile index hiển thị cho map;

public:
	int mapWidth;

	Tilemap();
	~Tilemap();

	void LoadTilemap(const char * imagePath, const char * matrixPath);	// đường dẫn tilesheet và matrix
	void Draw(Camera * camera);
	void Release();
};


#include "Tilemap.h"
#include <fstream>

// Hiển thị integer lên MessageBox:
//	#include <string>
//		std::string message = std::to_string(int);
//		MessageBox(0, message.c_str(), "Show int", 0);
// Để test thôi ý mà

Tilemap::Tilemap()
{
}


Tilemap::~Tilemap()
{
}

void Tilemap::LoadTilemap(const char * imagePath, const char * matrixPath)
{
	tilesheet = new GameTexture();
	tilesheet->LoadTexture(imagePath);

	std::ifstream fs(matrixPath);

	if (!fs.is_open()) {
		MessageBox(0, "Loi mo file", "Loi kia", 0);
		return;
	}

	fs >> mapCols >> mapRows >> tileSize;

	matrix = new int*[mapRows];
	for (int row = 0; row < mapRows; row++)
	{
		matrix[row] = new int[mapCols];
		for (int col = 0; col < mapCols; col++)
		{
			fs >> matrix[row][col];
		}
	}

	mapWidth = mapCols * tileSize;

	fs.close();
}

void Tilemap::Draw(Camera * camera)
{
	// Tile 4 rìa camera
	int firstCol, lastCol, firstRow, lastRow;
	int mapHeight = mapRows * tileSize;

	firstCol = camera->getLeft() / tileSize;
	lastCol = camera->getRight() / tileSize;
	firstRow = (mapHeight - camera->getTop()) / tileSize;
	lastRow = (mapHeight - camera->getBottom()) / tileSize;

	if (firstCol < 0) {
		firstCol = 0;
	}
	if (lastCol >= mapCols) {
		lastCol = mapCols - 1;
	}
	if (firstRow < 0) {
		firstRow = 0;
	}
	if (lastRow >= mapRows) {
		lastRow = mapRows - 1;
	}

	// xét tọa độ và vẽ tile trên camera
	for (int row = firstRow; row <= lastRow; row++)
	{
		for (int col = firstCol; col <= lastCol; col++)
		{
			// tọa độ World
			int xW = col * tileSize;
			int yW = mapHeight - row * tileSize;

			//if (xW >= camera->getLeft() - tileSize && xW <= camera->getRight())
			{
				// Chuyển thành tọa độ View
				float xV, yV;
				camera->worldToView(xW, yW, xV, yV);

				// Lấy tile từ tilesheet vẽ lên camera theo tọa độ view
				int chosenTile = matrix[row][col];
				int tileInTilesheet_X = chosenTile * tileSize;

				RECT rect;
				SetRect(&rect, tileInTilesheet_X, 0, tileInTilesheet_X + tileSize, tileSize);
				tilesheet->Draw(xV, yV, &rect);
			}
		}
	}
}

void Tilemap::Release()
{
	delete tilesheet;

	for (int row = 0; row < mapRows; row++)
	{
		delete[] matrix[row];
	}
	delete[] matrix;
}
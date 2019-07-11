#pragma once
#include <vector>
#include "GridCell.h"
#include "Camera.h"
#include "GameObject.h"

class Grid
{
	GridCell **cell;
	int cellSize;
	int numberOfColumns, numberOfRows;
	int numberOfObjects;

	// Giới hạn nhóm các cell giao với camera
	int firstColumn, firstRow, lastColumn, lastRow;

	// active objects
	std::vector<GameObject*> objects;

public:
	bool isEmpty;

	Grid();
	~Grid();

	void readGridInfo(const char * gridInfoPath, const char * cellsInfoPath);
	void readCellsInfo(const char * cellsInfoPath);
	// Khởi tạo grid
	void InitGrid(Camera * camera);
	
	// liên tục cập nhật bộ cells tùy theo vị trí của camera
	void UpdateCellsSet(Camera * camera);
	// để check xem bộ cells có thay đổi hay không
	D3DXVECTOR2 GetFirstCellPosition();
	D3DXVECTOR2 GetLastCellPosition();

	void IgnoreLeft(Camera * camera);
	void IgnoreRight(Camera * camera);
	void AddLeft(Camera * camera, GameObject * player);
	void AddRight(Camera * camera, GameObject * player);

	// Cập nhật objectList mỗi khi có cell thay đổi
	void UpdateObjectList(Camera * camera);
	// Lấy object từ những cell giao với camera
	std::vector<GameObject*> GetObjectList(Camera * camera);
	std::vector<GameObject*> GetObjectList();

	void Release();
};


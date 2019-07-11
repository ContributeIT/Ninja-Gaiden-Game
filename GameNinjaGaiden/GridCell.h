#pragma once
#include "Rect.h"
#include "Collision.h"
#include "GameObject.h"
#include <vector>

#define DEFAULT_CELL_SIZE	120

class GridCell
{
	int columnIndex, rowIndex;
	int size;
	int listSize;
	std::vector<GameObject*> objectList;
	std::vector<D3DXVECTOR3*> objectInfoList;
	// for itemContainer
	std::vector<D3DXVECTOR2*> itemInfoList;

public:
	bool isEmpty;

	GridCell();
	~GridCell();

	int getColumnIndex();	void setColumnIndex(int x);
	int getRowIndex();		void setRowIndex(int y);
	int getSize();		void setSize(int size);
	int getListSize();	void setListSize(int n);

	void InitObject(float x, float y, int objTypeID, int itemTypeID = -1, int itemBase = -1);
	void InitObject(D3DXVECTOR3 * objectInfo, D3DXVECTOR2 * itemInfo = new D3DXVECTOR2(-1, -1));
	void InitAllObjects();

	void addObjectInfo(float x, float y, int objTypeID, int itemTypeID = -1, int itemBase = -1);
	std::vector<GameObject*> getObjectList();
	std::vector<D3DXVECTOR3*> getObjectInfoList();
	std::vector<D3DXVECTOR2*> getItemInfoList();

	void enableUpdate(GameObject * player);
	void disableUpdate();

	void Release();
};


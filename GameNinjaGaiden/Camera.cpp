#include "Camera.h"
#include <d3dx9.h>


Camera * Camera::instance = NULL;
Camera * Camera::getInstance()
{
	if (instance == NULL)
	{
		instance = new Camera();
	}
	return instance;
}

Camera::Camera()
{
	// default setting ? ? ? ?
	setX(0);
	setY(DEFAULT_CAMERA_HEIGHT);	// điểm góc trên bên trái
	setSize(DEFAULT_CAMERA_WIDTH, DEFAULT_CAMERA_HEIGHT);
}


Camera::~Camera()
{
}

void Camera::trackPlayer(Player * player)
{
	//this->setVelX(player.getVelX());
	this->setX(player->getX() + (player->getWidth() - this->getWidth()) / 2);
}

void Camera::worldToView(float xW, float yW, float & xV, float & yV)
{
	// lập matrix translate
	D3DXMATRIX matrix;

	// Flip Y + Ox
	//	1	0	0	0
	//	0	-1	0	0
	//	-x0	y0	1	0
	//	0	0	0	1
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._31 = -getX();		// x0
	matrix._32 = getY();		// y0

	// transform
	D3DXVECTOR4 matrixP(xW, yW, 1, 1);
	D3DXVec4Transform(&matrixP, &matrixP, &matrix);

	// Translate Y 40
	D3DXMatrixTranslation(&matrix, 0, 40, 0);
	D3DXVec4Transform(&matrixP, &matrixP, &matrix);

	xV = matrixP.x;
	yV = matrixP.y;
}


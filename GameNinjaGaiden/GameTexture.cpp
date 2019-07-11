#include "GameTexture.h"
#include "Game.h"



GameTexture::GameTexture()
{
}


GameTexture::~GameTexture()
{
}

void GameTexture::LoadTexture(const char * imagePath, D3DCOLOR transColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	d3ddev = Game::getInstance()->get3DDevice();

	result = D3DXGetImageInfoFromFile(imagePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(NULL, "Texture Error!", "Loi kia", MB_OK);
		return;
	}

	Release();
	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		imagePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,		      // bộ lọc ảnh
		D3DX_DEFAULT,		      // bộ lọc mip
		transColor,				// chỉ ra màu trong suốt
		&info,			          // thông tin của sprite
		NULL,			          // đổ màu
		&texture			      // texture sẽ chứa sprite
	);

	if (result != D3D_OK)
	{
		MessageBox(NULL, "Texture Error!", "Loi kia", MB_OK);
		return;
	}

	this->spriteHandler = Game::getInstance()->getSpriteHandler();
}

void GameTexture::Draw(int x, int y, RECT * r)
{
	HRESULT result;
	D3DXVECTOR3 pos(x, y, 0);
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	result = spriteHandler->Draw(
		texture,
		r,							// hiển thị phần này 
		NULL,				            // đặt tâm ở đây, NULL là góc trên bên trái
		&pos,							// hiện thị sprite lên tọa độ này trên backbuffer
		D3DCOLOR_XRGB(255, 255, 255)	// màu thay thế
	);
	if (result != D3D_OK)
	{
		MessageBox(NULL, "Draw Texture Error!", "Loi kia", MB_OK);
		return;
	}
	spriteHandler->End();
}

void GameTexture::Release()
{
	if (texture != NULL) texture->Release();
}

#include "Sprite.h"
#include "Camera.h"


Sprite::Sprite()
{
	currentAnimation = 0;
}

Sprite::Sprite(float x, float y)
{
	position.x = x;
	position.y = y;
	position.z = 0;
	texture = NULL;
	spriteHandle = NULL;
}

Sprite::~Sprite()
{
}

int Sprite::getCurrentAnimation()
{
	return currentAnimation;
}

void Sprite::setCurrentAnimation(int currentAnimation)
{
	this->currentAnimation = currentAnimation;
}

int Sprite::getFirstAnimation()
{
	return firstAnimation;
}

void Sprite::setFirstAnimation(int firstAnimation)
{
	this->firstAnimation = firstAnimation;
}

int Sprite::getLastAnimation()
{
	return lastAnimation;
}

void Sprite::setLastAnimation(int lastAnimation)
{
	this->lastAnimation = lastAnimation;
}

void Sprite::LoadTexture(const char * imagePath, D3DCOLOR transColor)
{
	spriteTexture.LoadTexture(imagePath, transColor);
}

void Sprite::SetAnimation(float animationWidth, float animationHeight, int animationCount, int animationsPerRow, int firstAnimation, int lastAnimation)
{
	if (animationCount > 0)
	{
		//
		this->firstAnimation = firstAnimation;
		if (this->currentAnimation < firstAnimation || this->currentAnimation > lastAnimation)
			this->currentAnimation = firstAnimation;
		this->lastAnimation = lastAnimation;

		// Lưu tọa độ các animation trong sprite vào mảng animation;
		animation = new myPoint[animationCount];
		animation[0].X = 0;
		animation[0].Y = 0;
		int i = 0;
		int j = 1;
		do
		{
			// Nếu đạt số lượng animation tối đa của dòng thì chuyển X về 0 và tăng Y
			if (i == animationsPerRow * j)
			{
				animation[i].X = 0;
				animation[i].Y = animation[i - 1].Y + animationHeight;
				j++;
			}

			// Tăng tọa độ X sang animation kế tiếp
			animation[i + 1].X = animation[i].X + animationWidth;
			animation[i + 1].Y = animation[i].Y;
			i++;
		} while (i < lastAnimation);
	}
}

void Sprite::Draw(float x, float y, Rect * rect)
{
	RECT frame;
	frame.left = animation[currentAnimation].X;
	frame.top = animation[currentAnimation].Y;
	frame.right = frame.left + rect->getWidth();
	frame.bottom = frame.top + rect->getHeight();

	float xV, yV;
	Camera::getInstance()->worldToView(x, y, xV, yV);
	spriteTexture.Draw(xV, yV, &frame);
}

void Sprite::Release()
{
	spriteTexture.Release();
}

//chổ thêm
LPDIRECT3DTEXTURE9 Sprite::LoadTexture(LPDIRECT3DDEVICE9 device, const char * file)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(file, &info);
	if (result != D3D_OK)
	{
		return NULL;
	}

	width = info.Width;
	height = info.Height;

	//create texture
	result = D3DXCreateTextureFromFileEx(
		device,
		file,
		info.Width,
		info.Height,
		1,									//Mipmap levels
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),				//Transparent color
		&info,								//Image infomation
		NULL,
		&texture							//result
	);

	if (FAILED(result))
		return NULL;
	return texture;
}

void Sprite::Draw(D3DXVECTOR3 pos, RECT *rect)
{
	if (spriteHandle && texture)
	{
		spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);

		spriteHandle->Draw(texture, rect, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));

		spriteHandle->End();
	}
}
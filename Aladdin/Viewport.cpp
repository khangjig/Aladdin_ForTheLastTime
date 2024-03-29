#include "Viewport.h"
#include "Game.h"
#include "Debug.h"

Viewport *Viewport::__instance = NULL;

Viewport::Viewport()
{
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	x = 0;
	y = 0;
}

Viewport::~Viewport()
{

}

RECT Viewport::GetRect()
{
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.right = x + width;
	rect.bottom = y - height;
	return rect;
}

Viewport *Viewport::GetInstance()
{
	if (__instance == NULL)
		__instance = new Viewport();
	return __instance;
}

void Viewport::Reset()
{
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	if (Game::GetInstance()->GetStage() == STAGE_2)
	{
		x = 0;
		y = 225;
	}
	else
	{
		x = 50;
		y = 225;
	}
}
void Viewport::ResetPosision(int x, int y)
{
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;

	this->x = x;
	this->y = y;
}

void Viewport::Update(DWORD dt)
{
	Aladdin * aladdin = Aladdin::GetInstance();

	int right = 0;
	if (aladdin->GetLV() == 1)
	{
		right = (int)(TileMap::GetInstance()->currentMap->size * 100 - SCREEN_WIDTH / 2) - 130;
	}
	else
	{
		right = (int)(TileMap::GetInstance()->currentMap->size * 100 - SCREEN_WIDTH / 2) - 10;
	}
	int left = (int)SCREEN_WIDTH / 2;
	int bottom = (int)(TileMap::GetInstance()->currentMap->height * 100 - SCREEN_HEIGHT / 2 );
	int top = (int)SCREEN_HEIGHT / 2;

	if (aladdin->GetPositionX() > left && aladdin->GetPositionX() < right)
	{
		this->x = aladdin->GetPositionX() - left;
	}
	if (aladdin->GetPositionY() > top && aladdin->GetPositionY() < bottom)
	{
		this->y = aladdin->GetPositionY() + top - 30;
	}
}

bool Viewport::IsObjectInCamera(GameObject *gameobject)
{
	RECT rec = GetRect();

	float GameObjectPosX = gameobject->GetPositionX();
	float GameObjectPosY = gameobject->GetPositionY();
	if (GameObjectPosX >= rec.left && GameObjectPosX <= rec.right && GameObjectPosY >= rec.bottom && GameObjectPosY <= rec.top)
		return true;
	return false;
}

bool Viewport::IsObjectInCamera2(TileObjectMap* tile)
{
	RECT rec = GetRect();

	float GameObjectPosX = tile->x;
	float GameObjectPosY = tile->y;
	if (GameObjectPosX >= rec.left && GameObjectPosX <= rec.right && GameObjectPosY >= rec.bottom && GameObjectPosY <= rec.top)
		return true;
	return false;
}

void Viewport::SetRenderData(D3DXVECTOR2 &center, D3DXVECTOR2 &translate, D3DXVECTOR2 &scaling)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1;
	mt._41 = -this->x;
	mt._42 = this->y;
	D3DXVECTOR4 curTranslate;
	D3DXVECTOR4 curCenter;
	D3DXVec2Transform(&curCenter, &D3DXVECTOR2(center.x, center.y), &mt);
	D3DXVec2Transform(&curTranslate, &D3DXVECTOR2(translate.x, translate.y), &mt);

	center.x = curCenter.x;
	center.y = curCenter.y;
	translate.x = curTranslate.x;
	translate.y = curTranslate.y;
}
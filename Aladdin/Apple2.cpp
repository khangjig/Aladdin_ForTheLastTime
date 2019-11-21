﻿#include "Apple2.h"
#include "Grid.h"

#define APPLE_NONE 1
#define APPLE_FLYING 2
#define APPLE_BOOM 3

Apple2 * Apple2::__instance = NULL;

Apple2 * Apple2::GetInstance()
{
	if (__instance == NULL)
		__instance = new Apple2();
	return __instance;
}

Apple2::Apple2()
{
	LoadResources();

	width = APPLE_WIDTH;
	height = APPLE_HEIGHT;

	vx = APPLE_SPEED;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = APPLE_WIDTH;
	collider.height = APPLE_HEIGHT;

	maxDistance = SCREEN_WIDTH / 2.5;
}

void Apple2::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resource\\Character\\Aladdin.txt");

	// Apple flying
	Animation * anim = new Animation(100);
	Sprite * apple_flying = new Sprite(ALADDIN_TEXTURE_LOCATION, listSprite[280], TEXTURE_TRANS_COLOR);
	anim->AddFrame(apple_flying);
	animations.push_back(anim);

	// Apple collision
	anim = new Animation(100);
	Sprite *apple_collision_1 = new Sprite(ALADDIN_TEXTURE_LOCATION, listSprite[281], TEXTURE_TRANS_COLOR);
	apple_collision_1->SetOffSetY(3);
	anim->AddFrame(apple_collision_1);
	Sprite * apple_collision_2 = new Sprite(ALADDIN_TEXTURE_LOCATION, listSprite[282], TEXTURE_TRANS_COLOR);
	apple_collision_2->SetOffSetX(6);
	apple_collision_2->SetOffSetY(11);
	anim->AddFrame(apple_collision_2);
	Sprite * apple_collision_3 = new Sprite(ALADDIN_TEXTURE_LOCATION, listSprite[283], TEXTURE_TRANS_COLOR);
	apple_collision_3->SetOffSetX(10);
	apple_collision_3->SetOffSetY(15);
	anim->AddFrame(apple_collision_3);
	Sprite * apple_collision_4 = new Sprite(ALADDIN_TEXTURE_LOCATION, listSprite[284], TEXTURE_TRANS_COLOR);
	apple_collision_4->SetOffSetX(11);
	apple_collision_4->SetOffSetY(18);
	anim->AddFrame(apple_collision_4);
	animations.push_back(anim);
	Sprite * apple_collision_5 = new Sprite(ALADDIN_TEXTURE_LOCATION, listSprite[285], TEXTURE_TRANS_COLOR);
	apple_collision_5->SetOffSetX(10);
	apple_collision_5->SetOffSetY(20);
	anim->AddFrame(apple_collision_5);
	animations.push_back(anim);

	// Apple none
	anim = new Animation(100);
	Sprite * apple_none = new Sprite(ALADDIN_TEXTURE_LOCATION, listSprite[280], TEXTURE_TRANS_COLOR);
	anim->AddFrame(apple_none);
	animations.push_back(anim);
}

void Apple2::Update(DWORD dt)
{
	this->SetSpeedY(0);
	Aladdin* aladdin = Aladdin::GetInstance();
	AladdinState* aladdinState = AladdinState::GetInstance(aladdin);
	aladdinState->GetState();

	if (!aladdin->GetisApple())
	{
		this->state = APPLE_FLYING;
		this->SetIsFlying(true);
		this->AppleFlying();
	}
	else
	{
		this->SetIsFlying(false);
		this->SetSpeedX(0);
		this->state = APPLE_NONE;
	}

	this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt*(isLeft == true ? -1 : 1)));
	this->SetPositionY((float)(this->GetPositionY() + this->GetSpeedY()* dt));
}

void Apple2::AppleFlying()
{
	Aladdin* aladdin = Aladdin::GetInstance();
	if (isStartThrow)
	{
		DebugOut(L"asdadasdasda \n");
		this->isAladdinLeft = aladdin->IsLeft();
		if (aladdin->IsLeft())
			this->SetPositionX(aladdin->GetPositionX() + 20);
		else
			this->SetPositionX(aladdin->GetPositionX() - 14);
		this->distance = aladdin->GetPositionX() + maxDistance * (isAladdinLeft ? -1 : 1);
		this->SetSpeedX(APPLE_SPEED * 1 * (isAladdinLeft ? -1 : 1));
		this->SetPositionY(aladdin->GetPositionY() - 6);

		this->isStartThrow = false;
		aladdin->SetIsApple(false);
	}
	else
	{

		int cpos = aladdin->GetPositionY() - 16;
		if ((isAladdinLeft ? (this->GetPositionX() < this->distance) : (this->GetPositionX() >= this->distance) && isReturn))
		{
			this->SetSpeedX(APPLE_SPEED * -1 * (isAladdinLeft ? -1 : 1));
			isReturn = false;
		}
		if (abs(this->GetPositionY() - cpos) >= 1)
		{
			if (this->GetPositionY() > cpos)
			{
				float temp = this->GetPositionY() - 2.5;
				this->SetPositionY(temp);
			}
			else
			{
				float temp = this->GetPositionY() + 2.5;
				this->SetPositionY(temp);
			}
		}
		if (!isReturn && abs(this->GetPositionX() - aladdin->GetPositionX()) <= 30)
		{

			isStartThrow = true;
			isReturn = true;
			aladdin->SetIsApple(true);

		}
	}
}

void Apple2::Render()
{
	int state = this->state;
	Aladdin * aladdin = Aladdin::GetInstance();
	AladdinState * aladdinState = AladdinState::GetInstance(aladdin);


	SpriteData spriteData;

	spriteData.width = APPLE_WIDTH;
	spriteData.height = APPLE_HEIGHT;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;
	spriteData.isLeft = aladdin->IsLeft();
	spriteData.isFlipped = aladdin->IsFlipped();

	switch (state)
	{
	case APPLE_NONE:
	{

		this->animations[2]->Render(spriteData);
	}
	break;
	case APPLE_FLYING:
	{
		this->animations[0]->Render(spriteData);
	}
	break;
	case APPLE_BOOM:
	{
		this->animations[1]->Render(spriteData);
	}
	break;
	}
}

Apple2::~Apple2()
{
}

﻿#include "BatState.h"
#include <math.h>

BatState * BatState::__instance = NULL;

BatState *BatState::GetInstance(Bat *bat)
{
	if (__instance == NULL)
		__instance = new BatState(bat);
	return __instance;
}

BatState::BatState(Bat *bat)
{
	this->bat = bat;
	this->stateBat = BAT_IDLE;
}

StateBat BatState::GetState()
{
	return this->stateBat;
}

void BatState::SetState(StateBat state)
{
	this->stateBat = state;
}

void BatState::stateIdle() 
{
	this->bat->SetSpeedX(0);
	this->bat->SetSpeedY(0);
	this->anim = bat->GetAnimationsList()[BAT_IDLE];

	if (abs(Aladdin::GetInstance()->GetPositionY() - this->bat->GetPositionY()) <= 150)
	{
		if (abs(Aladdin::GetInstance()->GetPositionX() - this->bat->GetPositionX()) <= 100)
		{
			this->SetState(BAT_START_FLY);
			return;
		}
	}
}

void BatState::stateStartFly()
{
	this->anim = bat->GetAnimationsList()[BAT_START_FLY];

	if (Aladdin::GetInstance()->GetPositionX() < this->bat->GetPositionX())
	{
		this->bat->SetSpeedX(BAT_FLY_UP_SPEED_X);
	}
	else
	{
		this->bat->SetSpeedX(-BAT_FLY_UP_SPEED_X);
	}

	if (this->anim->IsDone())
	{
		this->anim->Reset();
		this->SetState(BAT_READY_ATTACK);
		return;
	}
}

void BatState::stateReadyAttack()
{
	this->bat->SetSpeedX(0);
	this->bat->SetSpeedY(0);
	this->anim = bat->GetAnimationsList()[BAT_FLYING];

	if (this->bat->GetReadyAttack() && Aladdin::GetInstance()->GetAladdinHP() > 0)
	{
		if (abs(Aladdin::GetInstance()->GetPositionY() - this->bat->GetPositionY()) <= 150)
		{
			if (abs(Aladdin::GetInstance()->GetPositionX() - this->bat->GetPositionX()) <= 120)
			{
				if (Aladdin::GetInstance()->GetPositionX() < this->bat->GetPositionX())
				{
					this->bat->SetSpeedX(-BAT_FLY_DOWN_SPEED_X);
				}
				else if (Aladdin::GetInstance()->GetPositionX() > this->bat->GetPositionX())
				{
					this->bat->SetSpeedX(BAT_FLY_DOWN_SPEED_X);
				}
				else
				{
					this->bat->SetSpeedX(0);
				}

				if (Aladdin::GetInstance()->GetPositionY() < this->bat->GetPositionY())
				{
					this->bat->SetSpeedY(-BAT_FLY_DOWN_SPEED_Y);
				}
				else if (Aladdin::GetInstance()->GetPositionY() > this->bat->GetPositionY())
				{
					this->bat->SetSpeedY(BAT_FLY_DOWN_SPEED_Y);
				}
				else
				{
					this->bat->SetSpeedY(0);
				}

				return;
			}
		}
	}
}

void BatState::stateFlying()
{
	anim = bat->GetAnimationsList()[BAT_FLYING];
	this->bat->SetSpeedY(BAT_FLY_UP_SPEED_Y);

	if (this->anim->IsDone())
	{
		if (this->bat->IsLeft())
		{
			this->bat->SetSpeedX(BAT_FLY_UP_SPEED_X);
		}
		else
		{
			this->bat->SetSpeedX(-BAT_FLY_UP_SPEED_X);
		}
	}

	if (this->bat->GetReadyAttack())
	{
		this->SetState(BAT_READY_ATTACK);
		return;
	}
}

void BatState::stateBeKillApple()
{
	this->bat->SetSpeedX(0);
	this->bat->SetSpeedY(-BAT_FLY_DOWN_SPEED_Y);
	anim = bat->GetAnimationsList()[BAT_BE_KILL_APPLE];

	if (this->anim->IsDone())
	{
		this->anim->Reset();
		Grid::GetInstance()->SetisLifeListObject(this->bat->GetID(), false);
		return;
	}
}

void BatState::stateBeKillSword()
{
	this->bat->SetSpeedX(0);
	this->bat->SetSpeedY(0);
	anim = bat->GetAnimationsList()[BAT_BE_KILL_SWORD];
	
	if (this->bat->GetEnemiesDeadEffect()->GetHidden())
	{
		Grid::GetInstance()->SetisLifeListObject(this->bat->GetID(), false);
		return;
	}
}

void BatState::Colision()
{

}

void BatState::Update(DWORD dt)
{

	switch (stateBat)
	{

	case BAT_IDLE:
		this->stateIdle();
		break;

	case BAT_START_FLY:
		this->stateStartFly();
		break;

	case BAT_FLYING:
		this->stateFlying();
		break;

	case BAT_BE_KILL_APPLE:
		this->stateBeKillApple();
		break;

	case BAT_BE_KILL_SWORD:
		this->stateBeKillSword();
		break;

	case BAT_READY_ATTACK:
		this->stateReadyAttack();
		break;

	default:
		break;
	}


	this->timeCount += dt;
}

void BatState::Render()
{
	SpriteData spriteData;
	if (this->bat != NULL)
	{
		spriteData.width = BAT_SPRITE_WIDTH;
		spriteData.height = BAT_SPRITE_HEIGHT;
		spriteData.x = bat->GetPositionX();
		spriteData.y = bat->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = false;
		spriteData.isFlipped = false;
	}

	anim->Render(spriteData);
}

BatState::~BatState()
{
	delete anim;
}
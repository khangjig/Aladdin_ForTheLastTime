﻿#include "Aladdin.h"

vector<Animation *> Aladdin::animations = vector<Animation *>();

Aladdin *Aladdin::__instance = NULL;

Aladdin *Aladdin::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Aladdin();
	}
	return __instance;
}

Aladdin::Aladdin()
{
	LoadResources();
	state = AladdinState::GetInstance(this);

	apple = Apple::GetInstance();
	itemEffect = new ItemEffect(-100, -100);
	this->SetIsApple(true);

	this->x = 50;
	this->y = 150;
	this->AladdinHP = ALADDIN_DEFAULT_HP;
	this->AppleNumber = ALADDIN_DEFAULT_APPLE;
	this->DiamondNumber = ALADDIN_DEFAULT_DIAMOND;
	this->LifeNumber = ALADDIN_DEFAULT_HEART;
	this->ScoreNumber = ALADDIN_DEFAULT_SCORE;
	this->DmgAttack = ALADDIN_DAMAGE;
	this->LV = 1;
	this->Attacking = false;
	this->JumpOnBrick = false;
	this->JumpOnRope = false;
	this->OnCollisonRope = false;
	this->OnTopRope= false;
	this->OnBotRope = false;
	this->BlockedByWall = false;
	this->LeftWall = true;
	this->width = ALADDIN_SPRITE_WIDTH;
	this->height = ALADDIN_SPRITE_HEIGHT;

	this->GeneratePosX = 50;
	this->GeneratePosY = 150;
	this->GeneratePosCameraX = Viewport::GetInstance()->GetX();
	this->GeneratePosCameraY = Viewport::GetInstance()->GetY();

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ALADDIN_SPRITE_WIDTH;
	collider.height = ALADDIN_SPRITE_HEIGHT;

	this->theme1 = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_A_WHOLE_NEW_WORLD);
	this->theme2 = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_THEMES);

	this->aladdinHurt = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_ALADDIN_HURT);
	this->aladdinOof = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_ALADDIN_OOF);
	this->aladdinPush = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_ALADDIN_PUSH);
	this->bodyCrunch = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_BODY_CRUNCH);

	this->highSword = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_HIGH_SWORD);
	this->lowSword = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_LOW_SWORD);
	this->throwApple = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_OBJECT_THROW);
	this->genieFumes = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_GENIE_FUMES);
	this->comingOut = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_COMING_OUT);

	this->bonesTinkle = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_BONES_TINKLE);
	this->boxingBell = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_BOXING_BELL);
	this->cashRegister = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_CASH_RES3);

	this->appleCollect = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_APPLE_COLLECT);
	this->gemCollect = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_GEM_COLLECT);
	this->extraHeart = Sound::GetInstance()->LoadSound((LPTSTR)SOUND_EXTRA_HEALTH);

	Sound::GetInstance()->PlaySound(theme1);
}

void Aladdin::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resource\\Character\\Aladdin.txt");
	Sprite * aladdin2 = new Sprite(ALADDIN_TEXTURE_LOCATION, TEXTURE_TRANS_COLOR);

#pragma region STAND
	Animation * anim = new Animation(300);
	Sprite * stand;
	stand = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(stand);
	stand = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(stand);
	stand = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(stand);
	stand = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(stand);
	stand = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(stand);
	stand = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(stand);
	animations.push_back(anim);
#pragma endregion

#pragma region HEAD UP
	anim = new Animation(130);

	Sprite * head_up_1 = new Sprite(aladdin2->GetTexture(), listSprite[50], TEXTURE_TRANS_COLOR);
	head_up_1->SetOffSetY(3);
	anim->AddFrame(head_up_1);
	Sprite * head_up_2 = new Sprite(aladdin2->GetTexture(), listSprite[51], TEXTURE_TRANS_COLOR);
	head_up_2->SetOffSetX(4);
	head_up_2->SetOffSetY(9);
	anim->AddFrame(head_up_2);
	Sprite * head_up_3 = new Sprite(aladdin2->GetTexture(), listSprite[52], TEXTURE_TRANS_COLOR);
	head_up_3->SetOffSetX(7);
	head_up_3->SetOffSetY(8);
	anim->AddFrame(head_up_3);

	animations.push_back(anim);
#pragma endregion

#pragma region RUN
	anim = new Animation(100);

	Sprite * run_1 = new Sprite(aladdin2->GetTexture(), listSprite[141], TEXTURE_TRANS_COLOR);
	run_1->SetOffSetX(0);
	run_1->SetOffSetY(-2);
	anim->AddFrame(run_1);
	Sprite * run_2 = new Sprite(aladdin2->GetTexture(), listSprite[142], TEXTURE_TRANS_COLOR);
	run_2->SetOffSetX(1);
	run_2->SetOffSetY(1);
	anim->AddFrame(run_2);
	Sprite * run_3 = new Sprite(aladdin2->GetTexture(), listSprite[143], TEXTURE_TRANS_COLOR);
	run_3->SetOffSetX(0);
	run_3->SetOffSetY(3);
	anim->AddFrame(run_3);
	Sprite * run_4 = new Sprite(aladdin2->GetTexture(), listSprite[144], TEXTURE_TRANS_COLOR);
	run_4->SetOffSetX(0);
	run_4->SetOffSetY(7);
	anim->AddFrame(run_4);
	Sprite * run_5 = new Sprite(aladdin2->GetTexture(), listSprite[145], TEXTURE_TRANS_COLOR);
	run_5->SetOffSetX(6);
	run_5->SetOffSetY(7);
	anim->AddFrame(run_5);
	Sprite * run_6 = new Sprite(aladdin2->GetTexture(), listSprite[146], TEXTURE_TRANS_COLOR);
	run_6->SetOffSetX(2);
	run_6->SetOffSetY(4);
	anim->AddFrame(run_6);
	Sprite * run_7 = new Sprite(aladdin2->GetTexture(), listSprite[147], TEXTURE_TRANS_COLOR);
	run_7->SetOffSetX(1);
	run_7->SetOffSetY(8);
	anim->AddFrame(run_7);
	Sprite * run_8 = new Sprite(aladdin2->GetTexture(), listSprite[148], TEXTURE_TRANS_COLOR);
	run_8->SetOffSetX(0);
	run_8->SetOffSetY(2);
	anim->AddFrame(run_8);
	Sprite * run_9 = new Sprite(aladdin2->GetTexture(), listSprite[149], TEXTURE_TRANS_COLOR);
	run_9->SetOffSetX(-3);
	run_9->SetOffSetY(4);
	anim->AddFrame(run_9);
	Sprite * run_10 = new Sprite(aladdin2->GetTexture(), listSprite[150], TEXTURE_TRANS_COLOR);
	run_10->SetOffSetX(4);
	run_10->SetOffSetY(8);
	anim->AddFrame(run_10);
	Sprite * run_11 = new Sprite(aladdin2->GetTexture(), listSprite[152], TEXTURE_TRANS_COLOR);
	run_11->SetOffSetX(7);
	run_11->SetOffSetY(5);
	anim->AddFrame(run_11);
	Sprite * run_12 = new Sprite(aladdin2->GetTexture(), listSprite[153], TEXTURE_TRANS_COLOR);
	run_12->SetOffSetX(2);
	run_12->SetOffSetY(7);
	anim->AddFrame(run_12);

	animations.push_back(anim);
#pragma endregion

#pragma region JUMP
	anim = new Animation(80);

	Sprite * jump_1 = new Sprite(aladdin2->GetTexture(), listSprite[91], TEXTURE_TRANS_COLOR);
	jump_1->SetOffSetX(15);
	jump_1->SetOffSetY(12);
	anim->AddFrame(jump_1);
	Sprite * jump_2 = new Sprite(aladdin2->GetTexture(), listSprite[92], TEXTURE_TRANS_COLOR);
	jump_2->SetOffSetX(12);
	jump_2->SetOffSetY(11);
	anim->AddFrame(jump_2);
	Sprite * jump_3 = new Sprite(aladdin2->GetTexture(), listSprite[93], TEXTURE_TRANS_COLOR);
	jump_3->SetOffSetX(9);
	jump_3->SetOffSetY(19);
	anim->AddFrame(jump_3);
	Sprite * jump_4 = new Sprite(aladdin2->GetTexture(), listSprite[94], TEXTURE_TRANS_COLOR);
	jump_4->SetOffSetX(6);
	jump_4->SetOffSetY(24);
	anim->AddFrame(jump_4);
	Sprite * jump_5 = new Sprite(aladdin2->GetTexture(), listSprite[95], TEXTURE_TRANS_COLOR);
	jump_5->SetOffSetX(-3);
	jump_5->SetOffSetY(16);
	anim->AddFrame(jump_5);

	animations.push_back(anim);
#pragma endregion

#pragma region FALL
	anim = new Animation(70);

	Sprite * fall_1 = new Sprite(aladdin2->GetTexture(), listSprite[96], TEXTURE_TRANS_COLOR);
	fall_1->SetOffSetY(29);
	anim->AddFrame(fall_1);
	Sprite * fall_2 = new Sprite(aladdin2->GetTexture(), listSprite[97], TEXTURE_TRANS_COLOR);
	fall_2->SetOffSetX(-1);
	fall_2->SetOffSetY(43);
	anim->AddFrame(fall_2);
	Sprite * fall_3 = new Sprite(aladdin2->GetTexture(), listSprite[98], TEXTURE_TRANS_COLOR);
	fall_3->SetOffSetX(1);
	fall_3->SetOffSetY(43);
	anim->AddFrame(fall_3);
	Sprite * fall_4 = new Sprite(aladdin2->GetTexture(), listSprite[99], TEXTURE_TRANS_COLOR);
	fall_4->SetOffSetX(1);
	fall_4->SetOffSetY(43);
	anim->AddFrame(fall_4);

	animations.push_back(anim);
#pragma endregion

#pragma region TOUCH ON THE GROUND
	anim = new Animation(190);

	Sprite * on_ground_1 = new Sprite(aladdin2->GetTexture(), listSprite[108], TEXTURE_TRANS_COLOR);
	on_ground_1->SetOffSetX(7);
	on_ground_1->SetOffSetY(35);
	anim->AddFrame(on_ground_1);
	Sprite * on_ground_2 = new Sprite(aladdin2->GetTexture(), listSprite[90], TEXTURE_TRANS_COLOR);
	on_ground_2->SetOffSetX(14);
	on_ground_2->SetOffSetY(-7);
	anim->AddFrame(on_ground_2);

	animations.push_back(anim);
#pragma endregion

#pragma region SIT
	anim = new Animation(100);

	Sprite * sit_1 = new Sprite(aladdin2->GetTexture(), listSprite[74], TEXTURE_TRANS_COLOR);
	sit_1->SetOffSetX(6);
	sit_1->SetOffSetY(-1);
	anim->AddFrame(sit_1);
	Sprite * sit_2 = new Sprite(aladdin2->GetTexture(), listSprite[75], TEXTURE_TRANS_COLOR);
	sit_2->SetOffSetX(8);
	sit_2->SetOffSetY(-10);
	anim->AddFrame(sit_2);
	Sprite * sit_3 = new Sprite(aladdin2->GetTexture(), listSprite[76], TEXTURE_TRANS_COLOR);
	sit_3->SetOffSetX(8);
	sit_3->SetOffSetY(-20);
	anim->AddFrame(sit_3);
	Sprite * sit_4 = new Sprite(aladdin2->GetTexture(), listSprite[77], TEXTURE_TRANS_COLOR);
	sit_4->SetOffSetX(3);
	sit_4->SetOffSetY(-15);
	anim->AddFrame(sit_4);

	animations.push_back(anim);
#pragma endregion

#pragma region IDLE_SIT
	anim = new Animation(100);

	Sprite * sit_idle = new Sprite(aladdin2->GetTexture(), listSprite[77], TEXTURE_TRANS_COLOR);
	sit_idle->SetOffSetX(3);
	sit_idle->SetOffSetY(-15);
	anim->AddFrame(sit_idle);

	animations.push_back(anim);
#pragma endregion

#pragma region STAND-HIT
	anim = new Animation(100);

	Sprite * stand_hit_1 = new Sprite(aladdin2->GetTexture(), listSprite[45], TEXTURE_TRANS_COLOR);
	stand_hit_1->SetOffSetX(8);
	stand_hit_1->SetOffSetY(1);
	anim->AddFrame(stand_hit_1);
	Sprite * stand_hit_2 = new Sprite(aladdin2->GetTexture(), listSprite[46], TEXTURE_TRANS_COLOR);
	stand_hit_2->SetOffSetX(10);
	stand_hit_2->SetOffSetY(12);
	anim->AddFrame(stand_hit_2);
	Sprite * stand_hit_3 = new Sprite(aladdin2->GetTexture(), listSprite[47], TEXTURE_TRANS_COLOR);
	stand_hit_3->SetOffSetX(4);
	stand_hit_3->SetOffSetY(24);
	anim->AddFrame(stand_hit_3);
	Sprite * stand_hit_4 = new Sprite(aladdin2->GetTexture(), listSprite[48], TEXTURE_TRANS_COLOR);
	stand_hit_4->SetOffSetY(19);
	anim->AddFrame(stand_hit_4);
	Sprite * stand_hit_5 = new Sprite(aladdin2->GetTexture(), listSprite[49], TEXTURE_TRANS_COLOR);
	stand_hit_5->SetOffSetX(8);
	stand_hit_5->SetOffSetY(3);
	anim->AddFrame(stand_hit_5);

	animations.push_back(anim);
#pragma endregion

#pragma region STAND-THROW
	anim = new Animation(80);

	Sprite * stand_throw_1 = new Sprite(aladdin2->GetTexture(), listSprite[39], TEXTURE_TRANS_COLOR);
	stand_throw_1->SetOffSetY(6);
	anim->AddFrame(stand_throw_1);
	Sprite * stand_throw_2 = new Sprite(aladdin2->GetTexture(), listSprite[40], TEXTURE_TRANS_COLOR);
	stand_throw_2->SetOffSetY(9);
	anim->AddFrame(stand_throw_2);
	Sprite * stand_throw_3 = new Sprite(aladdin2->GetTexture(), listSprite[41], TEXTURE_TRANS_COLOR);
	stand_throw_3->SetOffSetY(8);
	anim->AddFrame(stand_throw_3);
	Sprite * stand_throw_4 = new Sprite(aladdin2->GetTexture(), listSprite[42], TEXTURE_TRANS_COLOR);
	stand_throw_4->SetOffSetX(1);
	stand_throw_4->SetOffSetY(10);
	anim->AddFrame(stand_throw_4);
	Sprite * stand_throw_5 = new Sprite(aladdin2->GetTexture(), listSprite[43], TEXTURE_TRANS_COLOR);
	stand_throw_5->SetOffSetY(8);
	anim->AddFrame(stand_throw_5);
	Sprite * stand_throw_6 = new Sprite(aladdin2->GetTexture(), listSprite[44], TEXTURE_TRANS_COLOR);
	stand_throw_6->SetOffSetX(2);
	stand_throw_6->SetOffSetY(2);
	anim->AddFrame(stand_throw_6);

	animations.push_back(anim); 
#pragma endregion

#pragma region SIT-THROW
	anim = new Animation(80);

	Sprite * sit_throw_1 = new Sprite(aladdin2->GetTexture(), listSprite[78], TEXTURE_TRANS_COLOR);
	sit_throw_1->SetOffSetX(0);
	sit_throw_1->SetOffSetY(-6);
	anim->AddFrame(sit_throw_1);
	Sprite * sit_throw_2 = new Sprite(aladdin2->GetTexture(), listSprite[79], TEXTURE_TRANS_COLOR);
	sit_throw_2->SetOffSetX(0);
	sit_throw_2->SetOffSetY(-2);
	anim->AddFrame(sit_throw_2);
	Sprite * sit_throw_3 = new Sprite(aladdin2->GetTexture(), listSprite[80], TEXTURE_TRANS_COLOR);
	sit_throw_3->SetOffSetX(0);
	sit_throw_3->SetOffSetY(-2);
	anim->AddFrame(sit_throw_3);
	Sprite * sit_throw_4 = new Sprite(aladdin2->GetTexture(), listSprite[81], TEXTURE_TRANS_COLOR);
	sit_throw_4->SetOffSetX(12);
	sit_throw_4->SetOffSetY(-13);
	anim->AddFrame(sit_throw_4);
	Sprite * sit_throw_5 = new Sprite(aladdin2->GetTexture(), listSprite[82], TEXTURE_TRANS_COLOR);
	sit_throw_5->SetOffSetX(7);
	sit_throw_5->SetOffSetY(-13);
	anim->AddFrame(sit_throw_5);

	animations.push_back(anim);
#pragma endregion

#pragma region SIT-HIT
	anim = new Animation(80);

	Sprite * sit_hit_1 = new Sprite(aladdin2->GetTexture(), listSprite[83], TEXTURE_TRANS_COLOR);
	sit_hit_1->SetOffSetY(-17);
	anim->AddFrame(sit_hit_1);
	Sprite * sit_hit_2 = new Sprite(aladdin2->GetTexture(), listSprite[84], TEXTURE_TRANS_COLOR);
	sit_hit_2->SetOffSetY(-19);
	anim->AddFrame(sit_hit_2);
	Sprite * sit_hit_3 = new Sprite(aladdin2->GetTexture(), listSprite[85], TEXTURE_TRANS_COLOR);
	sit_hit_3->SetOffSetY(-17);
	anim->AddFrame(sit_hit_3);
	Sprite * sit_hit_4 = new Sprite(aladdin2->GetTexture(), listSprite[86], TEXTURE_TRANS_COLOR);
	sit_hit_4->SetOffSetY(-16);
	anim->AddFrame(sit_hit_4);
	Sprite * sit_hit_5 = new Sprite(aladdin2->GetTexture(), listSprite[87], TEXTURE_TRANS_COLOR);
	sit_hit_5->SetOffSetY(-17);
	anim->AddFrame(sit_hit_5);
	Sprite * sit_hit_6 = new Sprite(aladdin2->GetTexture(), listSprite[88], TEXTURE_TRANS_COLOR);
	sit_hit_6->SetOffSetY(-17);
	anim->AddFrame(sit_hit_6);
	Sprite * sit_hit_7 = new Sprite(aladdin2->GetTexture(), listSprite[89], TEXTURE_TRANS_COLOR);
	sit_hit_7->SetOffSetY(-19);
	anim->AddFrame(sit_hit_7);

	animations.push_back(anim);
#pragma endregion

#pragma region RUN-JUMP
	anim = new Animation(150);

	Sprite * run_jump_1 = new Sprite(aladdin2->GetTexture(), listSprite[102], TEXTURE_TRANS_COLOR);
	run_jump_1->SetOffSetX(4);
	run_jump_1->SetOffSetY(26);
	anim->AddFrame(run_jump_1);
	Sprite * run_jump_2 = new Sprite(aladdin2->GetTexture(), listSprite[103], TEXTURE_TRANS_COLOR);
	run_jump_2->SetOffSetX(10);
	run_jump_2->SetOffSetY(7);
	anim->AddFrame(run_jump_2);
	Sprite * run_jump_3 = new Sprite(aladdin2->GetTexture(), listSprite[104], TEXTURE_TRANS_COLOR);
	run_jump_3->SetOffSetX(11);
	run_jump_3->SetOffSetY(-8);
	anim->AddFrame(run_jump_3);

	animations.push_back(anim);
#pragma endregion

#pragma region FALL 2
	anim = new Animation(100);

	Sprite * fall2_1 = new Sprite(aladdin2->GetTexture(), listSprite[105], TEXTURE_TRANS_COLOR);
	fall2_1->SetOffSetX(12);
	fall2_1->SetOffSetY(-2);
	anim->AddFrame(fall2_1);
	Sprite * fall2_2 = new Sprite(aladdin2->GetTexture(), listSprite[106], TEXTURE_TRANS_COLOR);
	fall2_2->SetOffSetX(10);
	fall2_2->SetOffSetY(3);
	anim->AddFrame(fall2_2);
	Sprite * fall2_3 = new Sprite(aladdin2->GetTexture(), listSprite[107], TEXTURE_TRANS_COLOR);
	fall2_3->SetOffSetX(8);
	fall2_3->SetOffSetY(8);
	anim->AddFrame(fall2_3);

	animations.push_back(anim);
#pragma endregion

#pragma region JUMP-THROW
	anim = new Animation(50);

	Sprite * jump_throw_1 = new Sprite(aladdin2->GetTexture(), listSprite[122], TEXTURE_TRANS_COLOR);
	jump_throw_1->SetOffSetX(6);
	jump_throw_1->SetOffSetY(5);
	anim->AddFrame(jump_throw_1);
	Sprite * jump_throw_2 = new Sprite(aladdin2->GetTexture(), listSprite[123], TEXTURE_TRANS_COLOR);
	jump_throw_2->SetOffSetX(1);
	jump_throw_2->SetOffSetY(2);
	anim->AddFrame(jump_throw_2);
	Sprite * jump_throw_3 = new Sprite(aladdin2->GetTexture(), listSprite[124], TEXTURE_TRANS_COLOR);
	jump_throw_3->SetOffSetX(3);
	jump_throw_3->SetOffSetY(3);
	anim->AddFrame(jump_throw_3);
	Sprite * jump_throw_4 = new Sprite(aladdin2->GetTexture(), listSprite[125], TEXTURE_TRANS_COLOR);
	jump_throw_4->SetOffSetX(8);
	jump_throw_4->SetOffSetY(3);
	anim->AddFrame(jump_throw_4);
	Sprite * jump_throw_5 = new Sprite(aladdin2->GetTexture(), listSprite[126], TEXTURE_TRANS_COLOR);
	jump_throw_5->SetOffSetX(2);
	jump_throw_5->SetOffSetY(2);
	anim->AddFrame(jump_throw_5);

	animations.push_back(anim);
#pragma endregion

#pragma region JUMP-HIT
	anim = new Animation(50);

	Sprite * jump_hit_1 = new Sprite(aladdin2->GetTexture(), listSprite[127], TEXTURE_TRANS_COLOR);
	jump_hit_1->SetOffSetX(8);
	jump_hit_1->SetOffSetY(4);
	anim->AddFrame(jump_hit_1);
	Sprite * jump_hit_2 = new Sprite(aladdin2->GetTexture(), listSprite[128], TEXTURE_TRANS_COLOR);
	jump_hit_2->SetOffSetX(7);
	jump_hit_2->SetOffSetY(2);
	anim->AddFrame(jump_hit_2);
	Sprite * jump_hit_3 = new Sprite(aladdin2->GetTexture(), listSprite[129], TEXTURE_TRANS_COLOR);
	jump_hit_3->SetOffSetX(5);
	jump_hit_3->SetOffSetY(16);
	anim->AddFrame(jump_hit_3);
	Sprite * jump_hit_4 = new Sprite(aladdin2->GetTexture(), listSprite[130], TEXTURE_TRANS_COLOR);
	jump_hit_4->SetOffSetX(7);
	jump_hit_4->SetOffSetY(6);
	anim->AddFrame(jump_hit_4);
	Sprite * jump_hit_5 = new Sprite(aladdin2->GetTexture(), listSprite[131], TEXTURE_TRANS_COLOR);
	jump_hit_5->SetOffSetX(23);
	jump_hit_5->SetOffSetY(10);
	anim->AddFrame(jump_hit_5);
	Sprite * jump_hit_6 = new Sprite(aladdin2->GetTexture(), listSprite[132], TEXTURE_TRANS_COLOR);
	jump_hit_6->SetOffSetX(5);
	jump_hit_6->SetOffSetY(5);
	anim->AddFrame(jump_hit_6);

	animations.push_back(anim);
#pragma endregion

#pragma region DOUBLE HIT
	anim = new Animation(90);

	Sprite * double_hit_1 = new Sprite(aladdin2->GetTexture(), listSprite[62], TEXTURE_TRANS_COLOR);
	double_hit_1->SetOffSetX(0);
	double_hit_1->SetOffSetY(3);
	anim->AddFrame(double_hit_1);
	Sprite * double_hit_2 = new Sprite(aladdin2->GetTexture(), listSprite[63], TEXTURE_TRANS_COLOR);
	double_hit_2->SetOffSetX(-1);
	double_hit_2->SetOffSetY(10);
	anim->AddFrame(double_hit_2);
	Sprite * double_hit_3 = new Sprite(aladdin2->GetTexture(), listSprite[64], TEXTURE_TRANS_COLOR);
	double_hit_3->SetOffSetX(29);
	double_hit_3->SetOffSetY(11);
	anim->AddFrame(double_hit_3);
	Sprite * double_hit_4 = new Sprite(aladdin2->GetTexture(), listSprite[65], TEXTURE_TRANS_COLOR);
	double_hit_4->SetOffSetX(12);
	double_hit_4->SetOffSetY(8);
	anim->AddFrame(double_hit_4);
	Sprite * double_hit_5 = new Sprite(aladdin2->GetTexture(), listSprite[66], TEXTURE_TRANS_COLOR);
	double_hit_5->SetOffSetX(11);
	double_hit_5->SetOffSetY(4);
	anim->AddFrame(double_hit_5);
	Sprite * double_hit_6 = new Sprite(aladdin2->GetTexture(), listSprite[67], TEXTURE_TRANS_COLOR);
	double_hit_6->SetOffSetX(18);
	double_hit_6->SetOffSetY(-2);
	anim->AddFrame(double_hit_6);
	Sprite * double_hit_7 = new Sprite(aladdin2->GetTexture(), listSprite[68], TEXTURE_TRANS_COLOR);
	double_hit_7->SetOffSetX(0);
	double_hit_7->SetOffSetY(21);
	anim->AddFrame(double_hit_7);

	animations.push_back(anim);
#pragma endregion

#pragma region HURT
	anim = new Animation(40);

	Sprite * hurt_1 = new Sprite(aladdin2->GetTexture(), listSprite[296], TEXTURE_TRANS_COLOR);
	anim->AddFrame(hurt_1);
	Sprite * hurt_2 = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(hurt_2);
	Sprite * hurt_3 = new Sprite(aladdin2->GetTexture(), listSprite[296], TEXTURE_TRANS_COLOR);
	anim->AddFrame(hurt_3);
	Sprite * hurt_4 = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(hurt_4);

	animations.push_back(anim);
#pragma endregion

#pragma region IDLE CLIMB
	anim = new Animation(100);

	Sprite * climb_idle = new Sprite(aladdin2->GetTexture(), listSprite[163], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_idle);

	animations.push_back(anim);
#pragma endregion

#pragma region CLIMB HURT
	anim = new Animation(100);

	Sprite * climb_hurt_1 = new Sprite(aladdin2->GetTexture(), listSprite[296], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_hurt_1);
	Sprite * climb_hurt_2 = new Sprite(aladdin2->GetTexture(), listSprite[163], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_hurt_2);
	Sprite * climb_hurt_3 = new Sprite(aladdin2->GetTexture(), listSprite[296], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_hurt_3);
	Sprite * climb_hurt_4 = new Sprite(aladdin2->GetTexture(), listSprite[163], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_hurt_4);

	animations.push_back(anim);
#pragma endregion

#pragma region CLIMB JUMP
	anim = new Animation(100);

	Sprite * climb_jump_1 = new Sprite(aladdin2->GetTexture(), listSprite[200], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_jump_1);
	Sprite * climb_jump_2 = new Sprite(aladdin2->GetTexture(), listSprite[201], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_jump_2);
	Sprite * climb_jump_3 = new Sprite(aladdin2->GetTexture(), listSprite[202], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_jump_3);
	Sprite * climb_jump_4 = new Sprite(aladdin2->GetTexture(), listSprite[203], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_jump_4);
	Sprite * climb_jump_5 = new Sprite(aladdin2->GetTexture(), listSprite[204], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_jump_5);

	animations.push_back(anim);
#pragma endregion

#pragma region CLIMB FALL
	anim = new Animation(100);

	Sprite * climb_fall_1 = new Sprite(aladdin2->GetTexture(), listSprite[205], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_fall_1);
	Sprite * climb_fall_2 = new Sprite(aladdin2->GetTexture(), listSprite[206], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_fall_2);
	Sprite * climb_fall_3 = new Sprite(aladdin2->GetTexture(), listSprite[207], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_fall_3);
	Sprite * climb_fall_4 = new Sprite(aladdin2->GetTexture(), listSprite[208], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_fall_4);

	animations.push_back(anim);
#pragma endregion

#pragma region CLIMBING
	anim = new Animation(100);

	Sprite * climbing_1 = new Sprite(aladdin2->GetTexture(), listSprite[164], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_1);
	Sprite * climbing_2 = new Sprite(aladdin2->GetTexture(), listSprite[165], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_2);
	Sprite * climbing_3 = new Sprite(aladdin2->GetTexture(), listSprite[166], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_3);
	Sprite * climbing_4 = new Sprite(aladdin2->GetTexture(), listSprite[167], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_4);
	Sprite * climbing_5 = new Sprite(aladdin2->GetTexture(), listSprite[168], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_5);
	Sprite * climbing_6 = new Sprite(aladdin2->GetTexture(), listSprite[169], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_6);
	Sprite * climbing_7 = new Sprite(aladdin2->GetTexture(), listSprite[170], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_7);
	Sprite * climbing_8 = new Sprite(aladdin2->GetTexture(), listSprite[171], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_8);
	Sprite * climbing_9 = new Sprite(aladdin2->GetTexture(), listSprite[172], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climbing_9);

	animations.push_back(anim);
#pragma endregion

#pragma region CLIMB HIT
	anim = new Animation(100);

	Sprite * climb_hit = new Sprite(aladdin2->GetTexture(), listSprite[163], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_hit);

	animations.push_back(anim);
#pragma endregion

#pragma region CLIMB THROW
	anim = new Animation(100);

	Sprite * climb_throw = new Sprite(aladdin2->GetTexture(), listSprite[163], TEXTURE_TRANS_COLOR);
	anim->AddFrame(climb_throw);

	animations.push_back(anim);
#pragma endregion

#pragma region DEAD
	anim = new Animation(200);

	Sprite * dead_1 = new Sprite(aladdin2->GetTexture(), listSprite[215], TEXTURE_TRANS_COLOR);
	dead_1->SetOffSetX(27);
	dead_1->SetOffSetY(-2);
	anim->AddFrame(dead_1);
	Sprite * dead_2 = new Sprite(aladdin2->GetTexture(), listSprite[216], TEXTURE_TRANS_COLOR);
	dead_2->SetOffSetX(13);
	dead_2->SetOffSetY(1);
	anim->AddFrame(dead_2);
	Sprite * dead_3 = new Sprite(aladdin2->GetTexture(), listSprite[217], TEXTURE_TRANS_COLOR);
	dead_3->SetOffSetY(8);
	anim->AddFrame(dead_3);
	Sprite * dead_4 = new Sprite(aladdin2->GetTexture(), listSprite[218], TEXTURE_TRANS_COLOR);
	dead_4->SetOffSetX(-1);
	dead_4->SetOffSetY(8);
	anim->AddFrame(dead_4);
	Sprite * dead_5 = new Sprite(aladdin2->GetTexture(), listSprite[219], TEXTURE_TRANS_COLOR);
	anim->AddFrame(dead_5);
	Sprite * dead_6 = new Sprite(aladdin2->GetTexture(), listSprite[220], TEXTURE_TRANS_COLOR);
	dead_6->SetOffSetX(-1);
	dead_6->SetOffSetY(1);
	anim->AddFrame(dead_6);
	Sprite * dead_7 = new Sprite(aladdin2->GetTexture(), listSprite[221], TEXTURE_TRANS_COLOR);
	dead_7->SetOffSetX(1);
	dead_7->SetOffSetY(1);
	anim->AddFrame(dead_7);
	Sprite * dead_8 = new Sprite(aladdin2->GetTexture(), listSprite[222], TEXTURE_TRANS_COLOR);
	dead_8->SetOffSetX(1);
	dead_8->SetOffSetY(1);
	anim->AddFrame(dead_8);
	Sprite * dead_9 = new Sprite(aladdin2->GetTexture(), listSprite[223], TEXTURE_TRANS_COLOR);
	dead_9->SetOffSetX(3);
	dead_9->SetOffSetY(-1);
	anim->AddFrame(dead_9);
	Sprite * dead_10 = new Sprite(aladdin2->GetTexture(), listSprite[224], TEXTURE_TRANS_COLOR);
	dead_10->SetOffSetX(8);
	dead_10->SetOffSetY(6);
	anim->AddFrame(dead_10);
	Sprite * dead_11 = new Sprite(aladdin2->GetTexture(), listSprite[225], TEXTURE_TRANS_COLOR);
	dead_11->SetOffSetX(4);
	dead_11->SetOffSetY(3);
	anim->AddFrame(dead_11);
	Sprite * dead_12 = new Sprite(aladdin2->GetTexture(), listSprite[226], TEXTURE_TRANS_COLOR);
	dead_12->SetOffSetX(1);
	anim->AddFrame(dead_12);
	Sprite * dead_13 = new Sprite(aladdin2->GetTexture(), listSprite[227], TEXTURE_TRANS_COLOR);
	dead_13->SetOffSetX(2);
	dead_13->SetOffSetY(1);
	anim->AddFrame(dead_13);

	animations.push_back(anim);
#pragma endregion

#pragma region GENESIS
	anim = new Animation(60);

	Sprite * genesis_1 = new Sprite(aladdin2->GetTexture(), listSprite[243], TEXTURE_TRANS_COLOR);
	genesis_1->SetOffSetX(10);
	genesis_1->SetOffSetY(19);
	anim->AddFrame(genesis_1);
	Sprite * genesis_2 = new Sprite(aladdin2->GetTexture(), listSprite[244], TEXTURE_TRANS_COLOR);
	genesis_2->SetOffSetX(8);
	genesis_2->SetOffSetY(16);
	anim->AddFrame(genesis_2);
	Sprite * genesis_3 = new Sprite(aladdin2->GetTexture(), listSprite[245], TEXTURE_TRANS_COLOR);
	genesis_3->SetOffSetY(-17);
	anim->AddFrame(genesis_3);
	Sprite * genesis_4 = new Sprite(aladdin2->GetTexture(), listSprite[246], TEXTURE_TRANS_COLOR);
	genesis_4->SetOffSetY(-12);
	anim->AddFrame(genesis_4);
	Sprite * genesis_5 = new Sprite(aladdin2->GetTexture(), listSprite[247], TEXTURE_TRANS_COLOR);
	genesis_5->SetOffSetY(-4);
	anim->AddFrame(genesis_5);
	Sprite * genesis_6 = new Sprite(aladdin2->GetTexture(), listSprite[248], TEXTURE_TRANS_COLOR);
	genesis_6->SetOffSetY(8);
	anim->AddFrame(genesis_6);
	Sprite * genesis_7 = new Sprite(aladdin2->GetTexture(), listSprite[249], TEXTURE_TRANS_COLOR);
	genesis_7->SetOffSetX(2);
	genesis_7->SetOffSetY(17);
	anim->AddFrame(genesis_7);
	Sprite * genesis_8 = new Sprite(aladdin2->GetTexture(), listSprite[250], TEXTURE_TRANS_COLOR);
	genesis_8->SetOffSetY(31);
	anim->AddFrame(genesis_8);
	Sprite * genesis_9 = new Sprite(aladdin2->GetTexture(), listSprite[251], TEXTURE_TRANS_COLOR);
	genesis_9->SetOffSetX(5);
	genesis_9->SetOffSetY(34);
	anim->AddFrame(genesis_9);
	Sprite * genesis_10 = new Sprite(aladdin2->GetTexture(), listSprite[252], TEXTURE_TRANS_COLOR);
	genesis_10->SetOffSetX(0);
	genesis_10->SetOffSetY(37);
	anim->AddFrame(genesis_10);
	Sprite * genesis_11 = new Sprite(aladdin2->GetTexture(), listSprite[253], TEXTURE_TRANS_COLOR);
	genesis_11->SetOffSetX(10);
	genesis_11->SetOffSetY(50);
	anim->AddFrame(genesis_11);
	Sprite * genesis_12 = new Sprite(aladdin2->GetTexture(), listSprite[254], TEXTURE_TRANS_COLOR);
	genesis_12->SetOffSetX(23);
	genesis_12->SetOffSetY(65);
	anim->AddFrame(genesis_12);
	Sprite * genesis_13 = new Sprite(aladdin2->GetTexture(), listSprite[255], TEXTURE_TRANS_COLOR);
	genesis_13->SetOffSetX(17);
	genesis_13->SetOffSetY(84);
	anim->AddFrame(genesis_13);
	Sprite * genesis_14 = new Sprite(aladdin2->GetTexture(), listSprite[256], TEXTURE_TRANS_COLOR);
	genesis_14->SetOffSetX(13);
	genesis_14->SetOffSetY(91);
	anim->AddFrame(genesis_14);

	animations.push_back(anim);
#pragma endregion

#pragma region LOOK AROUND
	anim = new Animation(200);
	Sprite * look_around;

	look_around = new Sprite(aladdin2->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[1], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(2);
	look_around->SetOffSetY(-3);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[2], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetY(2);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[3], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetY(5);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[3], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetY(5);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[3], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetY(5);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[3], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetY(5);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[4], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(3);
	look_around->SetOffSetY(1);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[5], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(7);
	look_around->SetOffSetY(1);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[6], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(7);
	look_around->SetOffSetY(3);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[6], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(7);
	look_around->SetOffSetY(3);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[6], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(7);
	look_around->SetOffSetY(3);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[6], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(7);
	look_around->SetOffSetY(3);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[5], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(7);
	look_around->SetOffSetY(1);
	anim->AddFrame(look_around);
	look_around = new Sprite(aladdin2->GetTexture(), listSprite[4], TEXTURE_TRANS_COLOR);
	look_around->SetOffSetX(3);
	look_around->SetOffSetY(1);
	anim->AddFrame(look_around);

	animations.push_back(anim);
#pragma endregion

#pragma region PLAY WITH APPLE 1
	anim = new Animation(130);

	Sprite * playing_with_apple_1_1 = new Sprite(aladdin2->GetTexture(), listSprite[7], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_1->SetOffSetY(2);
	anim->AddFrame(playing_with_apple_1_1);
	Sprite * playing_with_apple_1_2 = new Sprite(aladdin2->GetTexture(), listSprite[8], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_2->SetOffSetX(8);
	playing_with_apple_1_2->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_1_2);
	Sprite * playing_with_apple_1_3 = new Sprite(aladdin2->GetTexture(), listSprite[9], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_3->SetOffSetX(7);
	playing_with_apple_1_3->SetOffSetY(4);
	anim->AddFrame(playing_with_apple_1_3);
	Sprite * playing_with_apple_1_4 = new Sprite(aladdin2->GetTexture(), listSprite[10], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_4->SetOffSetX(-8);
	playing_with_apple_1_4->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_1_4);
	Sprite * playing_with_apple_1_5 = new Sprite(aladdin2->GetTexture(), listSprite[11], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_5->SetOffSetX(-8);
	playing_with_apple_1_5->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_1_5);
	Sprite * playing_with_apple_1_6 = new Sprite(aladdin2->GetTexture(), listSprite[12], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_6->SetOffSetX(-8);
	playing_with_apple_1_6->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_1_6);
	Sprite * playing_with_apple_1_7 = new Sprite(aladdin2->GetTexture(), listSprite[13], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_7->SetOffSetX(-8);
	playing_with_apple_1_7->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_1_7);
	Sprite * playing_with_apple_1_8 = new Sprite(aladdin2->GetTexture(), listSprite[14], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_8->SetOffSetX(-8);
	playing_with_apple_1_8->SetOffSetY(5);
	anim->AddFrame(playing_with_apple_1_8);
	Sprite * playing_with_apple_1_9 = new Sprite(aladdin2->GetTexture(), listSprite[15], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_9->SetOffSetX(-8);
	playing_with_apple_1_9->SetOffSetY(22);
	anim->AddFrame(playing_with_apple_1_9);
	Sprite * playing_with_apple_1_10 = new Sprite(aladdin2->GetTexture(), listSprite[16], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_10->SetOffSetX(-8);
	playing_with_apple_1_10->SetOffSetY(26);
	anim->AddFrame(playing_with_apple_1_10);
	Sprite * playing_with_apple_1_11 = new Sprite(aladdin2->GetTexture(), listSprite[17], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_11->SetOffSetX(-8);
	playing_with_apple_1_11->SetOffSetY(21);
	anim->AddFrame(playing_with_apple_1_11);
	Sprite * playing_with_apple_1_12 = new Sprite(aladdin2->GetTexture(), listSprite[18], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_12->SetOffSetX(-8);
	playing_with_apple_1_12->SetOffSetY(12);
	anim->AddFrame(playing_with_apple_1_12);
	Sprite * playing_with_apple_1_13 = new Sprite(aladdin2->GetTexture(), listSprite[19], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_13->SetOffSetX(-8);
	playing_with_apple_1_13->SetOffSetY(4);
	anim->AddFrame(playing_with_apple_1_13);
	Sprite * playing_with_apple_1_14 = new Sprite(aladdin2->GetTexture(), listSprite[20], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_14->SetOffSetX(-8);
	playing_with_apple_1_14->SetOffSetY(4);
	anim->AddFrame(playing_with_apple_1_14);
	Sprite * playing_with_apple_1_15 = new Sprite(aladdin2->GetTexture(), listSprite[21], TEXTURE_TRANS_COLOR);
	playing_with_apple_1_15->SetOffSetX(-8);
	playing_with_apple_1_15->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_1_15);

	animations.push_back(anim);
#pragma endregion

#pragma region PLAY WITH APPLE 2
	anim = new Animation(130);

	Sprite * playing_with_apple_2_1 = new Sprite(aladdin2->GetTexture(), listSprite[22], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_1->SetOffSetX(-8);
	playing_with_apple_2_1->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_2_1);
	Sprite * playing_with_apple_2_2 = new Sprite(aladdin2->GetTexture(), listSprite[23], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_2->SetOffSetX(-8);
	playing_with_apple_2_2->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_2_2);
	Sprite * playing_with_apple_2_3 = new Sprite(aladdin2->GetTexture(), listSprite[24], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_3->SetOffSetX(-8);
	playing_with_apple_2_3->SetOffSetY(5);
	anim->AddFrame(playing_with_apple_2_3);
	Sprite * playing_with_apple_2_4 = new Sprite(aladdin2->GetTexture(), listSprite[25], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_4->SetOffSetX(-8);
	playing_with_apple_2_4->SetOffSetY(13);
	anim->AddFrame(playing_with_apple_2_4);
	Sprite * playing_with_apple_2_5 = new Sprite(aladdin2->GetTexture(), listSprite[26], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_5->SetOffSetX(-9);
	playing_with_apple_2_5->SetOffSetY(17);
	anim->AddFrame(playing_with_apple_2_5);
	Sprite * playing_with_apple_2_6 = new Sprite(aladdin2->GetTexture(), listSprite[27], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_6->SetOffSetX(-9);
	playing_with_apple_2_6->SetOffSetY(8);
	anim->AddFrame(playing_with_apple_2_6);
	Sprite * playing_with_apple_2_7 = new Sprite(aladdin2->GetTexture(), listSprite[28], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_7->SetOffSetX(-10);
	playing_with_apple_2_7->SetOffSetY(-1);
	anim->AddFrame(playing_with_apple_2_7);
	Sprite * playing_with_apple_2_8 = new Sprite(aladdin2->GetTexture(), listSprite[29], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_8->SetOffSetX(-10);
	playing_with_apple_2_8->SetOffSetY(-1);
	anim->AddFrame(playing_with_apple_2_8);
	Sprite * playing_with_apple_2_9 = new Sprite(aladdin2->GetTexture(), listSprite[30], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_9->SetOffSetX(-10);
	playing_with_apple_2_9->SetOffSetY(-1);
	anim->AddFrame(playing_with_apple_2_9);
	Sprite * playing_with_apple_2_10 = new Sprite(aladdin2->GetTexture(), listSprite[31], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_10->SetOffSetX(-11);
	playing_with_apple_2_10->SetOffSetY(10);
	anim->AddFrame(playing_with_apple_2_10);
	Sprite * playing_with_apple_2_11 = new Sprite(aladdin2->GetTexture(), listSprite[32], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_11->SetOffSetX(-12);
	playing_with_apple_2_11->SetOffSetY(17);
	anim->AddFrame(playing_with_apple_2_11);
	Sprite * playing_with_apple_2_12 = new Sprite(aladdin2->GetTexture(), listSprite[33], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_12->SetOffSetX(-12);
	playing_with_apple_2_12->SetOffSetY(24);
	anim->AddFrame(playing_with_apple_2_12);
	Sprite * playing_with_apple_2_13 = new Sprite(aladdin2->GetTexture(), listSprite[34], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_13->SetOffSetX(-10);
	playing_with_apple_2_13->SetOffSetY(29);
	anim->AddFrame(playing_with_apple_2_13);
	Sprite * playing_with_apple_2_14 = new Sprite(aladdin2->GetTexture(), listSprite[35], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_14->SetOffSetX(-8);
	playing_with_apple_2_14->SetOffSetY(12);
	anim->AddFrame(playing_with_apple_2_14);
	Sprite * playing_with_apple_2_15 = new Sprite(aladdin2->GetTexture(), listSprite[36], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_15->SetOffSetX(-8);
	playing_with_apple_2_15->SetOffSetY(4);
	anim->AddFrame(playing_with_apple_2_15);
	Sprite * playing_with_apple_2_16 = new Sprite(aladdin2->GetTexture(), listSprite[37], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_16->SetOffSetX(-8);
	playing_with_apple_2_16->SetOffSetY(4);
	anim->AddFrame(playing_with_apple_2_16);
	Sprite * playing_with_apple_2_17 = new Sprite(aladdin2->GetTexture(), listSprite[38], TEXTURE_TRANS_COLOR);
	playing_with_apple_2_17->SetOffSetX(-8);
	playing_with_apple_2_17->SetOffSetY(3);
	anim->AddFrame(playing_with_apple_2_17);

	animations.push_back(anim);
#pragma endregion

#pragma region PUSH WALL
	anim = new Animation(100);
	Sprite * push_wall_1 = new Sprite(aladdin2->GetTexture(), listSprite[286], TEXTURE_TRANS_COLOR);
	anim->AddFrame(push_wall_1);
	Sprite * push_wall_2 = new Sprite(aladdin2->GetTexture(), listSprite[287], TEXTURE_TRANS_COLOR);
	push_wall_2->SetOffSetX(9);
	push_wall_2->SetOffSetY(-2);
	anim->AddFrame(push_wall_2);
	Sprite * push_wall_3 = new Sprite(aladdin2->GetTexture(), listSprite[288], TEXTURE_TRANS_COLOR);
	push_wall_3->SetOffSetX(14);
	push_wall_3->SetOffSetY(-1);
	anim->AddFrame(push_wall_3);
	Sprite * push_wall_4 = new Sprite(aladdin2->GetTexture(), listSprite[289], TEXTURE_TRANS_COLOR);
	push_wall_4->SetOffSetX(21);
	push_wall_4->SetOffSetY(-2);
	anim->AddFrame(push_wall_4);
	Sprite * push_wall_5 = new Sprite(aladdin2->GetTexture(), listSprite[290], TEXTURE_TRANS_COLOR);
	push_wall_5->SetOffSetX(16);
	push_wall_5->SetOffSetY(-2);
	anim->AddFrame(push_wall_5);
	Sprite * push_wall_6 = new Sprite(aladdin2->GetTexture(), listSprite[291], TEXTURE_TRANS_COLOR);
	push_wall_6->SetOffSetX(19);
	push_wall_6->SetOffSetY(-2);
	anim->AddFrame(push_wall_6);
	Sprite * push_wall_7 = new Sprite(aladdin2->GetTexture(), listSprite[292], TEXTURE_TRANS_COLOR);
	push_wall_7->SetOffSetX(25);
	push_wall_7->SetOffSetY(-2);
	anim->AddFrame(push_wall_7);
	Sprite * push_wall_8 = new Sprite(aladdin2->GetTexture(), listSprite[293], TEXTURE_TRANS_COLOR);
	push_wall_8->SetOffSetX(19);
	push_wall_8->SetOffSetY(-2);
	anim->AddFrame(push_wall_8);
	Sprite * push_wall_9 = new Sprite(aladdin2->GetTexture(), listSprite[294], TEXTURE_TRANS_COLOR);
	push_wall_9->SetOffSetX(19);
	push_wall_9->SetOffSetY(-2);
	anim->AddFrame(push_wall_9);
	animations.push_back(anim);
#pragma endregion

#pragma region NONE
	anim = new Animation(80);
	Sprite * none = new Sprite(aladdin2->GetTexture(), listSprite[295], TEXTURE_TRANS_COLOR);
	anim->AddFrame(none);
	animations.push_back(anim);
#pragma endregion

	listSprite = loadTXT.LoadRect((char*)"Resource\\Character\\run-hit-n-throw.txt");
	Sprite * aladdin3 = new Sprite(ALADDIN_TEXTURE_LOCATION2, TEXTURE_TRANS_COLOR_2);

#pragma region RUN-HIT
	anim = new Animation(80);
	
	Sprite * run_throw_1 = new Sprite(aladdin3->GetTexture(), listSprite[0], TEXTURE_TRANS_COLOR_2);
	run_throw_1->SetOffSetY(2);
	anim->AddFrame(run_throw_1);
	Sprite * run_throw_2 = new Sprite(aladdin3->GetTexture(), listSprite[1], TEXTURE_TRANS_COLOR_2);
	run_throw_2->SetOffSetX(6);
	run_throw_2->SetOffSetY(10);
	anim->AddFrame(run_throw_2);
	Sprite * run_throw_3 = new Sprite(aladdin3->GetTexture(), listSprite[2], TEXTURE_TRANS_COLOR_2);
	run_throw_3->SetOffSetX(10);
	run_throw_3->SetOffSetY(3);
	anim->AddFrame(run_throw_3);
	Sprite * run_throw_4 = new Sprite(aladdin3->GetTexture(), listSprite[3], TEXTURE_TRANS_COLOR_2);
	run_throw_4->SetOffSetX(7);
	run_throw_4->SetOffSetY(10);
	anim->AddFrame(run_throw_4);
	Sprite * run_throw_5 = new Sprite(aladdin3->GetTexture(), listSprite[4], TEXTURE_TRANS_COLOR_2);
	run_throw_5->SetOffSetX(5);
	run_throw_5->SetOffSetY(5);
	anim->AddFrame(run_throw_5);
	Sprite * run_throw_6 = new Sprite(aladdin3->GetTexture(), listSprite[5], TEXTURE_TRANS_COLOR_2);
	run_throw_6->SetOffSetX(1);
	anim->AddFrame(run_throw_6);

	animations.push_back(anim);
#pragma endregion

#pragma region RUN-THROW
	anim = new Animation(80);

	Sprite * run_hit_1 = new Sprite(aladdin3->GetTexture(), listSprite[6], TEXTURE_TRANS_COLOR_2);
	run_hit_1->SetOffSetY(6);
	anim->AddFrame(run_hit_1);
	Sprite * run_hit_2 = new Sprite(aladdin3->GetTexture(), listSprite[7], TEXTURE_TRANS_COLOR_2);
	run_hit_2->SetOffSetX(16);
	run_hit_2->SetOffSetY(8);
	anim->AddFrame(run_hit_2);
	Sprite * run_hit_3 = new Sprite(aladdin3->GetTexture(), listSprite[8], TEXTURE_TRANS_COLOR_2);
	run_hit_3->SetOffSetX(18);
	run_hit_3->SetOffSetY(6);
	anim->AddFrame(run_hit_3);
	Sprite * run_hit_4 = new Sprite(aladdin3->GetTexture(), listSprite[9], TEXTURE_TRANS_COLOR_2);
	run_hit_4->SetOffSetX(15);
	run_hit_4->SetOffSetY(12);
	anim->AddFrame(run_hit_4);
	Sprite * run_hit_5 = new Sprite(aladdin3->GetTexture(), listSprite[10], TEXTURE_TRANS_COLOR_2);
	run_hit_5->SetOffSetX(11);
	run_hit_5->SetOffSetY(12);
	anim->AddFrame(run_hit_5);
	Sprite * run_hit_6 = new Sprite(aladdin3->GetTexture(), listSprite[10], TEXTURE_TRANS_COLOR_2);
	run_hit_6->SetOffSetX(6);
	run_hit_6->SetOffSetY(2);
	anim->AddFrame(run_hit_6);

	animations.push_back(anim);
#pragma endregion
}

void Aladdin::Reset()
{
	this->SetPositionX(50);
	this->SetPositionY(120);
	this->ResetSettings();
	Viewport::GetInstance()->Reset();
}

void Aladdin::Update(DWORD dt)
{
	//DebugOut(L"Aladdin %d %d \n", (int)this->GetPositionX(), (int)this->GetPositionY());
	timeCount += dt;

#pragma region	Shortcut Keys

	if (Keyboard::GetInstance()->IsKeyDown(DIK_F1))
	{
		this->LV = 1;
		Game::GetInstance()->SetStage(STAGE_1);

		this->state->SetState(IDLE_STAND);
		this->SetPositionX(100);
		this->SetPositionY(150);
		Viewport::GetInstance()->Reset();

		TileMap::GetInstance()->SetCurrentMap(STAGE_1);
		Grid::GetInstance()->InitializeMapGrid(TileMap::GetInstance());

		Sound::GetInstance()->StopSound(theme2);
		Sound::GetInstance()->PlaySound(theme1);
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F2))
	{
		this->LV = 2;
		Game::GetInstance()->SetStage(STAGE_2);

		this->state->SetState(IDLE_STAND);
		this->SetPositionX(100);
		this->SetPositionY(150);		
		this->GeneratePosX = 100;
		this->GeneratePosY = 150;
		this->GeneratePosCameraX = Viewport::GetInstance()->GetX();
		this->GeneratePosCameraY = Viewport::GetInstance()->GetY();
		Viewport::GetInstance()->Reset();

		TileMap::GetInstance()->SetCurrentMap(STAGE_2);
		Grid::GetInstance()->InitializeMapGrid(TileMap::GetInstance());

		Sound::GetInstance()->StopSound(theme1);
		Sound::GetInstance()->PlaySound(theme2);
	}
	if (Keyboard::GetInstance()->IsKeyDown(DIK_F3))
	{
		trueImortal = !trueImortal;
	}

#pragma endregion

#pragma region	Collide with map

	vector<ColliedEvent*> coEvents;
	vector<ColliedEvent*> coEventsResult;

	vector<TileObjectMap *> tiles = Grid::GetInstance()->GetNearbyObjectTiles();

	vector<TileObjectMap *> tilesRope = Grid::GetInstance()->GetNearbyObjectTilesThorn();
	coEvents.clear();

	this->SetDt(dt);
	this->UpdateObjectCollider();
	this->isLeft ? this->collider.x = x - 10 : this->collider.x = x;
	this->MapCollisions(tiles, coEvents);

#pragma region	BRICK - WALL - DOOR
	if (coEvents.size() == 0)
	{
		float moveX = trunc(this->GetSpeedX()* dt);
		float moveY = trunc(this->GetSpeedY()* dt);
		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		Collision::GetInstance()->GetNearestCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;

		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);

		switch (coEventsResult[0]->collisionID)
		{
		case ObjectType::BRICK:
		{
			if (ny == 1)
			{
				this->SetIsClimb(false);
				this->SetOnTopRope(false);
				this->SetOnBotRope(false);
				this->SetJumpOnRope(false);
				this->SetJumpOnBrick(false);
				this->SetIsGrounded(true);
			}
		}break;
		case ObjectType::WALL:
		{
			this->BlockedByWall = true;
			this->SetSpeedX(0);
			if (this->IsLeft())
			{
				this->LeftWall = true;
			}
			else
			{
				this->LeftWall = false;
			}
		}break;
		case ObjectType::DOOR:
		{
			DebugOut(L"DOOR \n");
			this->LV = 2;
			Game::GetInstance()->SetStage(STAGE_2);

			this->SetPositionX(100);
			this->SetPositionY(150);
			this->GeneratePosX = 100;
			this->GeneratePosY = 150;
			Viewport::GetInstance()->Reset();
			this->GeneratePosCameraX = Viewport::GetInstance()->GetX();
			this->GeneratePosCameraY = Viewport::GetInstance()->GetY();

			TileMap::GetInstance()->SetCurrentMap(STAGE_2);
			Grid::GetInstance()->InitializeMapGrid(TileMap::GetInstance());

			Sound::GetInstance()->StopSound(theme1);
			Sound::GetInstance()->PlaySound(theme2);
		}break;
		}
	}
	for (int i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion


#pragma region	ROPE

	if (tilesRope.size() != 0)
	{
		Collider a;
		for (int i = 0; i < tilesRope.size(); i++)
		{
			a.x = tilesRope.at(i)->x;
			a.y = tilesRope.at(i)->y;
			a.width = tilesRope.at(i)->width;
			a.height = tilesRope.at(i)->height;

			if (Collision::GetInstance()->AABB(a, this->GetCollider()) && !Keyboard::GetInstance()->IsKeyDown(DIK_LSHIFT))
			{
				this->SetOnCollisonRope(true);

				if (!this->GetIsGrounded() && !this->GetIsClimb() && !this->GetJumpOnRope())
				{
					this->SetIsClimb(true);
					this->SetPositionX(tilesRope.at(i)->x + tilesRope.at(i)->width / 2 - ALADDIN_SPRITE_WIDTH / 2);
				}
				if (this->GetIsClimb())
				{
					if (this->GetPositionY() - 30 >= tilesRope.at(i)->y)
					{
						this->SetOnTopRope(true);
						this->SetJumpOnRope(true);
					}
					else if (this->GetPositionY() - 47 <= tilesRope.at(i)->y - tilesRope.at(i)->height)
					{
						this->SetOnBotRope(true);
					}
					else
					{
						this->SetOnTopRope(false);
						this->SetOnBotRope(false);
					}
				}
			}
		}
	}
	else
	{
		this->SetIsClimb(false);
		this->SetOnTopRope(false);
		this->SetOnBotRope(false);
		this->SetJumpOnRope(false);
		this->SetOnCollisonRope(false);
	}
#pragma endregion

#pragma endregion

#pragma region	Update HP Taskbar
	
	if (this->AladdinHP == 500)
	{
		HP::GetInstance()->SetState(LV_TEN);
	}
	else
	{
		if (this->AladdinHP >= 450)
		{
			HP::GetInstance()->SetState(LV_NINE);
		}
		else
		{
			if (this->AladdinHP >= 400)
			{
				HP::GetInstance()->SetState(LV_EIGHT);
			}
			else
			{
				if (this->AladdinHP >= 350)
				{
					HP::GetInstance()->SetState(LV_SEVEN);
				}
				else
				{
					if (this->AladdinHP >= 300)
					{
						HP::GetInstance()->SetState(LV_SIX);
					}
					else
					{
						if (this->AladdinHP >= 250)
						{
							HP::GetInstance()->SetState(LV_FIVE);
						}
						else
						{
							if (this->AladdinHP >= 200)
							{
								HP::GetInstance()->SetState(LV_FOUR);
							}
							else
							{
								if (this->AladdinHP >= 150)
								{
									HP::GetInstance()->SetState(LV_THREE);
								}
								else
								{
									if (this->AladdinHP >= 100)
									{
										HP::GetInstance()->SetState(LV_TWO);
									}
									else
									{
										if (this->AladdinHP >= 50)
										{
											HP::GetInstance()->SetState(LV_ONE);
										}
										else
										{
											if (this->AladdinHP <= 0)
											{
												HP::GetInstance()->SetState(LV_ZERO);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

#pragma endregion
	
	AppleMenu::GetInstance()->SetNum(this->AppleNumber);
	DiamondMenu::GetInstance()->SetNum(this->DiamondNumber);
	LifeMenu::GetInstance()->SetNum(this->LifeNumber);
	Score::GetInstance()->SetNum(this->ScoreNumber);
	apple->Update(dt);
	apple->UpdateCollision(tiles);
	state->Colision();
	state->Update(dt);

#pragma region Set new area collision when Aladdin is attacking

	if (this->GetAttacking())
	{
		if (this->isLeft)
			this->collider.x = x - 35;
		this->collider.width = ALADDIN_SPRITE_WIDTH + 35;
	}
	else
	{
		this->collider.width = ALADDIN_SPRITE_WIDTH;
		this->collider.x = x;
	}

	if (this->state->GetState() == IDLE_SIT ||
		this->state->GetState() == STATE_SIT_HIT ||
		this->state->GetState() == STATE_SIT_THROW ||
		this->state->GetState() == STATE_SIT)
	{
		this->collider.y = y - 35;
	}
	else
	{
		this->collider.y = y;
	}

#pragma endregion

}

void Aladdin::UpdateCollision(DWORD dt)
{
	if (trueImortal)
		return;

	if (bImortal)
	{
		if (timeCount > 700)
		{
			timeCount = 0;
			bImortal = false;
		}
		return;
	}

	vector<OnUpdateObject> listUpdateObject = Grid::GetInstance()->GetListUpdateObject();

	for (int i = 0; i < listUpdateObject.size(); i++)
	{
		if (!listUpdateObject.at(i).isGenerated || !listUpdateObject.at(i).isLife)
			continue;

		bool isCollide = Collision::GetInstance()->AABB(this->GetCollider(), listUpdateObject.at(i).object->GetCollider());
	
		if (!isCollide)
			continue;

		switch (listUpdateObject.at(i).ene.SpawnObjectID)
		{
		case ObjectAndEnemies::GUARD1:
		{
			if (((Guard1*)listUpdateObject.at(i).object)->GetAttacking())
			{
				this->AladdinHP = this->AladdinHP - ((Guard1*)listUpdateObject.at(i).object)->GetGuard1DmgAttack();
				DebugOut(L"Aladdin HP :  %d \n", this->AladdinHP);
				this->state->SetState(STATE_HURT);
				Sound::GetInstance()->PlaySound(aladdinHurt);
			}
		}break;
		case ObjectAndEnemies::GUARD2:
		{
			if (((Guard2*)listUpdateObject.at(i).object)->GetAttacking())
			{
				this->AladdinHP = this->AladdinHP - ((Guard2*)listUpdateObject.at(i).object)->GetGuard2DmgAttack();
				DebugOut(L"Aladdin HP :  %d \n", this->AladdinHP);
				this->state->SetState(STATE_HURT);
				Sound::GetInstance()->PlaySound(aladdinHurt);
			}
		}break;
		case ObjectAndEnemies::SKELETON:
		{
			if (((Skeleton*)listUpdateObject.at(i).object)->GetAttacking())
			{
				this->AladdinHP = this->AladdinHP - ((Skeleton*)listUpdateObject.at(i).object)->GetDmg();
				DebugOut(L"Aladdin HP :  %d \n", this->AladdinHP);
				this->state->SetState(STATE_HURT);
				Sound::GetInstance()->PlaySound(aladdinHurt);
			}
		}break;
		case ObjectAndEnemies::BAT:
		{
			if (((Bat*)listUpdateObject.at(i).object)->GetReadyAttack())
			{
				this->AladdinHP = this->AladdinHP - ((Bat*)listUpdateObject.at(i).object)->GetDmg();
				DebugOut(L"Aladdin HP :  %d \n", this->AladdinHP);
				this->state->SetState(STATE_HURT);
				Sound::GetInstance()->PlaySound(aladdinHurt);
			}
		}break;
		case ObjectAndEnemies::THORN:
		{
			int x = ((ThornObject*)listUpdateObject.at(i).object)->GetAnimation()[1]->GetCurFrame();
			if (x == 3)
			{
				this->AladdinHP = this->AladdinHP - THORN_DAMAGE_BY_TIME;
				DebugOut(L"Aladdin HP :  %d \n", this->AladdinHP);
				this->state->SetState(STATE_HURT);
				if (this->AladdinHP > 0)
				{
					Sound::GetInstance()->PlaySound(aladdinHurt);
				}
			}
		}break;
		case ObjectAndEnemies::BALL:
		{
			int x = ((BallObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame();
			if (x == 9 || x == 19)
			{
				this->AladdinHP = this->AladdinHP - BALL_DAMAGE_BY_TIME;
				DebugOut(L"Aladdin HP :  %d \n", this->AladdinHP);
				this->state->SetState(STATE_HURT);
				if (this->AladdinHP > 0)
				{
					Sound::GetInstance()->PlaySound(aladdinHurt);
				}
			}
		}break;
		case ObjectAndEnemies::BRICK_IN:
		{
			if (this->JumpOnBrick)
			{
				if (((BrickInObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 2 ||
					((BrickInObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 3 ||
					((BrickInObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 4 ||
					((BrickInObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 5 )
				{
					if(this->GetPositionY() - ALADDIN_SPRITE_HEIGHT + 25 >= ((BrickInObject*)listUpdateObject.at(i).object)->GetY() && !Keyboard::GetInstance()->IsKeyDown(DIK_LSHIFT))
					{
						this->state->SetState(STAND_ON_BRICK);
						this->state->stateStandOnBrick();
						this->SetPositionY(((BrickInObject*)listUpdateObject.at(i).object)->GetY() + ALADDIN_SPRITE_HEIGHT -1);
						this->SetIsGrounded(true);
					}
				}
				else
				{
					if (this->state->GetState() == STAND_ON_BRICK)
					{
						this->SetSpeedY(-ALADDIN_JUMP_SPEED_Y);
						this->state->SetState(STATE_FALL);
						this->state->stateFalling();
					}
				}
			}

		}break;
		case ObjectAndEnemies::BRICK_OUT:
		{
			if (this->JumpOnBrick)
			{
				if (((BrickOutObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 0 ||
					((BrickOutObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 1 ||
					((BrickOutObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 7 ||
					((BrickOutObject*)listUpdateObject.at(i).object)->GetAnimation()[0]->GetCurFrame() == 8)
				{
					if (this->GetPositionY() - ALADDIN_SPRITE_HEIGHT + 25 >= ((BrickOutObject*)listUpdateObject.at(i).object)->GetY() && !Keyboard::GetInstance()->IsKeyDown(DIK_LSHIFT))
					{
						this->state->SetState(STAND_ON_BRICK);
						this->state->stateStandOnBrick();
						this->SetPositionY(((BrickOutObject*)listUpdateObject.at(i).object)->GetY() + ALADDIN_SPRITE_HEIGHT - 1);
						this->SetIsGrounded(true);
					}
				}
				else
				{
					if (this->state->GetState() == STAND_ON_BRICK)
					{
						this->SetSpeedY(-ALADDIN_JUMP_SPEED_Y);
						this->state->SetState(STATE_FALL);
						this->state->stateFalling();
					}
				}
			}

		}break;
		case ObjectAndEnemies::APPLE:
		{
			Sound::GetInstance()->PlaySound(appleCollect);
			Grid::GetInstance()->SetisLifeListObject(((AppleItem*)listUpdateObject.at(i).object)->GetID(), false);
			itemEffect->SetPos(listUpdateObject.at(i).ene.x + APPLE_ITEM_WIDTH / 2, listUpdateObject.at(i).ene.y, false);
			if (this->AppleNumber < ALADDIN_DEFAULT_MAX_APPLE)
			{
				this->AppleNumber++;
			}
		}break;
		case ObjectAndEnemies::DIAMOND:
		{
			Sound::GetInstance()->PlaySound(gemCollect);
			this->ScoreNumber += DIAMOND_ITEM_POINT;
			if (this->ScoreNumber > ALADDIN_DEFAULT_MAXS_SCORE)
			{
				this->ScoreNumber = ALADDIN_DEFAULT_MAXS_SCORE;
			}
			Grid::GetInstance()->SetisLifeListObject(((DiamondItem*)listUpdateObject.at(i).object)->GetID(), false);
			itemEffect->SetPos(listUpdateObject.at(i).ene.x + DIAMOND_ITEM_WIDTH / 2, listUpdateObject.at(i).ene.y, false);
			if (this->DiamondNumber < ALADDIN_DEFAULT_MAX_DIAMOND)
			{
				this->DiamondNumber++;
			}
		}break;
		case ObjectAndEnemies::BOTTLE:
		{
			if (!((BottleItem*)listUpdateObject.at(i).object)->GetCheck())
			{
				this->GeneratePosX = this->GetPositionX() + BOTTLE_ITEM_WIDTH / 2;
				this->GeneratePosY = this->GetPositionY();
				this->GeneratePosCameraX = Viewport::GetInstance()->GetX();
				this->GeneratePosCameraY = Viewport::GetInstance()->GetY();

				((BottleItem*)listUpdateObject.at(i).object)->SetCheck(true);
				Sound::GetInstance()->PlaySound(comingOut);
				itemEffect->SetPos(listUpdateObject.at(i).ene.x + BOTTLE_ITEM_WIDTH / 2, listUpdateObject.at(i).ene.y, false);
			}
		}break;
		case ObjectAndEnemies::GENIE_FACE:
		{
			Sound::GetInstance()->PlaySound(genieFumes);
			this->ScoreNumber += GENIE_FACE_POINT;
			if (this->ScoreNumber > ALADDIN_DEFAULT_MAXS_SCORE)
			{
				this->ScoreNumber = ALADDIN_DEFAULT_MAXS_SCORE;
			}
			Grid::GetInstance()->SetisLifeListObject(((GenieFaceItem*)listUpdateObject.at(i).object)->GetID(), false);
			itemEffect->SetPos(listUpdateObject.at(i).ene.x + GENIE_FACE_ITEM_WIDTH / 2, listUpdateObject.at(i).ene.y, false);
		}break;
		case ObjectAndEnemies::EXTRA_HEART:
		{
			Sound::GetInstance()->PlaySound(extraHeart);
			this->ScoreNumber += EXTRA_HEART_ITEM_POINT;
			if (this->ScoreNumber > ALADDIN_DEFAULT_MAXS_SCORE)
			{
				this->ScoreNumber = ALADDIN_DEFAULT_MAXS_SCORE;
			}
			Grid::GetInstance()->SetisLifeListObject(((ExtraHeartItem*)listUpdateObject.at(i).object)->GetID(), false);
			itemEffect->SetPos(listUpdateObject.at(i).ene.x + EXTRA_HEART_ITEM_WIDTH / 2, listUpdateObject.at(i).ene.y, false);
			if (this->LifeNumber < ALADDIN_DEFAULT_MAX_HEART)
			{
				this->LifeNumber++;
			}
		}break;
		case ObjectAndEnemies::SHOP:
		{

		}break;
		case ObjectAndEnemies::JAFAR:
		{
			//DebugOut(L"Aladdin touch Jafar\n");
		}break;
		}
	}
	if (this->AladdinHP <= 0)
	{
		this->state->SetState(STATE_DEAD);
	}
}

void Aladdin::Render()
{
	state->Render();
	apple->Render();
	itemEffect->Render();
}
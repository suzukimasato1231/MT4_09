#include "Stage.h"
#include"Shape.h"
Stage::Stage()
{}

Stage::~Stage()
{
	//ÉÅÉÇÉäâï˙
	for (int i = (int)floor.size() - 1; i >= 0; i--)
	{
		delete floor[i];
		floor.erase(floor.begin() + i);
	}
}

void Stage::Init()
{
	StageOne();
}

void Stage::MainInit(int stageNum)
{
	//ÉÅÉÇÉäâï˙éŒÇﬂè∞
	for (int i = (int)floor.size() - 1; i >= 0; i--)
	{
		delete floor[i];
		floor.erase(floor.begin() + i);
	}


	switch (stageNum)
	{
	case 0:
		StageOne();
		break;
	}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//éŒÇﬂè∞
	for (int i = 0; i < floor.size(); i++)
	{
		Object::Instance()->Draw(floor[i]->polygon, floor[i]->position,
			Vec3(1.0f, 1.0f, 1.0f), floor[i]->angle);
	}
}

void Stage::StageOne()
{
	floor.push_back(new Floor);
	floor[floor.size() - 1]->scale = { 100.0f,10.0f,100.0f };
	floor[floor.size() - 1]->polygon = Shape::CreateSquare(
		floor[floor.size() - 1]->scale.x, floor[floor.size() - 1]->scale.y, floor[floor.size() - 1]->scale.z);
	floor[floor.size() - 1]->position = { 0.0f,0.0f,0.0f };
	floor[floor.size() - 1]->angle = { 0.0f,0.0f,0.0f };

	floor.push_back(new Floor);
	floor[floor.size() - 1]->scale = { 100.0f,10.0f,100.0f };
	floor[floor.size() - 1]->polygon= Shape::CreateSquare(
		floor[floor.size() - 1]->scale.x, floor[floor.size() - 1]->scale.y, floor[floor.size() - 1]->scale.z);
	floor[floor.size() - 1]->position = { 0.0f,0.0f,0.0f };
	floor[floor.size() - 1]->angle = { 135.0f,0.0f,0.0f };
}



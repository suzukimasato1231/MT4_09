#pragma once
#include"Vec.h"
#include"Object.h"
#include<vector>
#include <CollisionPrimitive.h>

/// <summary>
/// ��
/// </summary>
struct Floor
{
	Object::ObjectData polygon;
	Box box;
	Vec3 position{};
	Vec3 scale = {};
	Vec3 angle = {};
};

class Stage
{
public:
	//�R���X�g���N�^
	Stage();
	//�f�X�R���X�g���N�^
	~Stage();
	//������
	void Init();
	//�X�e�[�W�I��
	void MainInit(int stageNum);
	//�X�V
	void Update();
	//�`��
	void Draw();
private:
	//�X�e�[�W�P�̍\��
	void StageOne();
public://��
	 Box GetFloorBox(int i) { if (floor.size() > 0) { return floor[i]->box; } }

	Vec3 GetFloorPos(int i) { if (floor.size() > 0) { return floor[i]->position; } }

	Vec3 GetFloorAngle(int i) { if (floor.size() > 0) { return floor[i]->angle; } }

	Vec3 GetFloorScale(int i){ if (floor.size() > 0) { return floor[i]->scale; } }

	int GetFloorSize() { return floor.size(); };
private:
	//��
	std::vector<Floor *> floor;
};
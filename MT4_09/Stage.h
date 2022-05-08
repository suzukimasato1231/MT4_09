#pragma once
#include"Vec.h"
#include"Object.h"
#include<vector>
#include <CollisionPrimitive.h>

/// <summary>
/// 床
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
	//コンストラクタ
	Stage();
	//デスコンストラクタ
	~Stage();
	//初期化
	void Init();
	//ステージ選択
	void MainInit(int stageNum);
	//更新
	void Update();
	//描画
	void Draw();
private:
	//ステージ１の構成
	void StageOne();
public://床
	 Box GetFloorBox(int i) { if (floor.size() > 0) { return floor[i]->box; } }

	Vec3 GetFloorPos(int i) { if (floor.size() > 0) { return floor[i]->position; } }

	Vec3 GetFloorAngle(int i) { if (floor.size() > 0) { return floor[i]->angle; } }

	Vec3 GetFloorScale(int i){ if (floor.size() > 0) { return floor[i]->scale; } }

	int GetFloorSize() { return floor.size(); };
private:
	//床
	std::vector<Floor *> floor;
};
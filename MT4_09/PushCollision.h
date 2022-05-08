#pragma once
#include"Player.h"
#include"MapStage.h"
#include"Collision.h"
#include"Enemy.h"
#include"Stage.h"
class PushCollision
{
public:
	/// <summary>
	/// 押し戻し処理
	/// </summary>
	/// <param name="stage">ステージクラス</param>
	/// <param name="player">プレイヤークラス</param>
	static void Player2Floor(Stage *stage, Player *player);
};
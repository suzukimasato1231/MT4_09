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
	/// �����߂�����
	/// </summary>
	/// <param name="stage">�X�e�[�W�N���X</param>
	/// <param name="player">�v���C���[�N���X</param>
	static void Player2Floor(Stage *stage, Player *player);
};
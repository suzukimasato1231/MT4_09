#include"Enemy.h"
#include"Shape.h"
#include"Input.h"
#include "MapStage.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	//���������
	for (int i = (int)eData.size() - 1; i >= 0; i--)
	{
		delete eData[i];
		eData.erase(eData.begin() + i);
	}
}

void Enemy::Init()
{

}

void Enemy::Update(Player *player)
{
	//�G����
	Generation(player);


	for (size_t i = 0; i < eData.size(); i++)
	{
		//�ړ�
		Move(i);
		//�_���[�W
		Damege(i, player);
	}
		//�폜
		Delete();
}

void Enemy::Draw()
{
	for (size_t i = 0; i < eData.size(); i++)
	{
		Object::Instance()->Draw(eData[i]->enemyObject, eData[i]->position, eData[i]->scale, eData[i]->angle, eData[i]->color);
	}
}


void Enemy::WasAttack(int i)
{
	eData[i]->wasAttackFlag = true;
}

void Enemy::Move(int i)
{
	eData[i]->oldPosition = eData[i]->position;

	//���W�����킹��
	eData[i]->eBox.minPosition = XMVectorSet(
		eData[i]->position.x - eData[i]->r,
		eData[i]->position.y - eData[i]->r,
		eData[i]->position.z - eData[i]->r,
		1);
	eData[i]->eBox.maxPosition = XMVectorSet(
		eData[i]->position.x + eData[i]->r,
		eData[i]->position.y + eData[i]->r,
		eData[i]->position.z + eData[i]->r,
		1);
}

void Enemy::Damege(int i, Player *player)
{
	
}

void Enemy::Generation(Player *player)
{
	//�G����
	if (Input::Instance()->KeybordTrigger(DIK_E))
	{
		eData.push_back(new EnemyData);
		eData[eData.size() - 1]->enemyObject = Object::Instance()->CreateOBJ("enemy");
		eData[eData.size() - 1]->eBox.minPosition = XMVectorSet(0, 2, 0, 1);
		eData[eData.size() - 1]->eBox.maxPosition = XMVectorSet(0, 2, 0, 1);
		eData[eData.size() - 1]->position = player->GetPosition() + Vec3(+10, 0, 0);
		eData[eData.size() - 1]->oldPosition = eData[eData.size() - 1]->position;
	}
}

void Enemy::Delete()
{
	//�G��������
	for (int i = (int)eData.size() - 1; i >= 0; i--)
	{
		if (eData[i]->HP <= 0)
		{
			delete eData[i];
			eData.erase(eData.begin() + i);
		}
	}
}



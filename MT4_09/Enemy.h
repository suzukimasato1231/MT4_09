#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include<vector>
#include"Player.h"
class Enemy
{
private://�\����
	//�G�̏��
	struct EnemyData
	{
		Object::ObjectData enemyObject;		//�v���C���[�I�u�W�F�N�g
		Box eBox;							//�G�{�b�N�X
		Vec3 position{ 50.0f,0.0f,0.0f };	//���W
		Vec3 oldPosition{};					//1�O�̍��W
		Vec3 speed{ 2.0f,2.0f,2.0f };		//�v���C���[�X�s�[�h
		Vec3 scale{ 1.0f,1.0f,1.0f };		//�傫��
		Vec3 angle{ 0.0f,0.0f,0.0f };		//�p�x
		Vec4 color{ 1.0f,1.0f,1.0f,1.0f };	//�F
		int HP = 10;						//HP
		float r = 5;						//�傫��
		bool wasAttackFlag = false;			//�U�����ꂽ���ǂ���
	};
private:
	//�G�z��
	std::vector<EnemyData *>eData;
public:
	Enemy();//�R���X�g���N�^

	~Enemy();//�ł��R���X�g���N�^

	void Init();//������

	void Update(class Player *player);//�X�V

	void Draw();//�`��

	//TRUE�ɂ���
	void WasAttack(int i);
private:
	//�ړ�
	void Move(int i);
	//�_���[�W����
	void Damege(int i, class Player *player);
	//����
	void Generation(class Player *player);
	//�폜
	void Delete();
public://�擾�n
	// ���W�擾
	Vec3 GetPosition(int i) { return eData[i]->position; }

	Box GetBox(int i) { return eData[i]->eBox; }
	//�G�l�~�[���擾
	int GetEnemySize() { return eData.size(); }
	//�U�����ꂽ�����擾
	bool GetWasAttackFlag(int i) { return eData[i]->wasAttackFlag; }
};
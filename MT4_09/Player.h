#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include"Easing.h"
#include"Enemy.h"

class Player
{
public:
	Player();//�R���X�g���N�^

	~Player();//�ł��R���X�g���N�^

	void Init();//������

	void Update(class Enemy *enemy);//�X�V

	void Draw();//�`��

	void SetPosition(Vec3 position);
	/// <summary>
	/// true�ɂ���
	/// </summary>
	void GroundFlag();
private:
	/// <summary>
	/// �v���C���[�ړ�
	/// </summary>
	void Move();
	/// <summary>
	/// �v���C���[�W�����v
	/// </summary>
	void Jump();
public://�擾�n
	//���W
	Vec3 GetPosition() { return position; }

	Vec3 GetOldPosition() { return oldPosition; }

	//Vec3 GetOldPosition() { return oldPosition; }

	Vec3 GetPSize() { return pScale; }
private:
	Object::ObjectData playerObject;	//�v���C���[�I�u�W�F�N�g
	Vec3 position{ 10.0f,0.0f,0.0f };	//���W
	Vec3 oldPosition{};					//1�O�̍��W
	Vec3 speed{ 2.0f,2.0f,2.0f };		//�v���C���[�X�s�[�h
	Vec3 scale{ 1.0f,1.0f,1.0f };		//�傫��
	Vec3 angle{ 0.0f,0.0f,0.0f };		//�p�x
	Vec4 color{ 1.0f,1.0f,1.0f,1.0f };	//�F
	Vec3 pScale = { 5.0f,10.0f,5.0f };						//�v���C���[�傫��
	int HP = 10;						//�v���C���[HP

	//�W�����v
	const float jumpPowerMax = 5.0f;
	float jumpPower = 5.0f;//�W�����v�p���[
	float jumpPowerDelay = 0.2;
	float gravity = 2.0f;//�d��
	bool jumpFlag = false;//�W�����v��������
	bool groundFlag = false;//�n�ʂɐڂ��Ă��邩�ǂ���
};
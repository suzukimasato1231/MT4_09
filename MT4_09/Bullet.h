#pragma once
#include <Object.h>
#include"DebugText.h"
enum Physics
{
	fall = 1,
	cannon,
	friction,
	airresistance,
	repulsion,
};
class Bullet
{
public:

	Bullet() {}

	~Bullet() {}

	void Load();
	//������
	void Init(int number);
	//�X�V
	void Update();
	//�`��
	void Draw();
private:
	//�����^��
	void FallMovement();
	//��C
	void Cannon();
	//���C
	void Friction();
	//��C��R
	void AirResistance();
	//����
	void Repulsion();
private:
	DebugText debugText;
	//�ǂ̏�����
	int number = 1;

	Object::ObjectData bulletOBJ;
	Vec3 position{};
	Vec3 position2{};
	Vec3 scale{ 5.0f,5.0f,5.0f };
	Vec3 angle{};
	Vec4 color{};
	float time = 0;

	Vec3 vec = {};						//���x
	float gravity = 0.0f;		//�d��
	const float gravityAccel = 0.03f;	//�d�͉����x

public:	//���C
	const float   m = 1.0f;//����
	const float staticFriction = 0.8f;	//�Î~���C
	const float dynamicFriction = 0.02f;	//�����C
public:	//��C��R
	const float airResistance = 0.015f;	//��C��R�萔
	float air = 0.0f;					//��C��R
	Vec3 Vec0 = { 1.0f,1.0f,0.0f };		//�����x
public://����
	float m1 = 1.0f;	//����
	float v1 = 3.0f;	//����
	float v01 = 2.0f;	//�����x

	float m2 = 1.0f;	//����
	float v2 = 5.0f;	//����
	float v02 = 2.0f;	//�����x

	bool Flag = true;

};


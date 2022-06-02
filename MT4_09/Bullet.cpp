#include "Bullet.h"
#include"Input.h"
#include"Collision.h"

//���Ƌ��̓����蔻��
bool CheckSphere2Sphere(const Sphere& sphere1, const Sphere& sphere2)
{
	//�Q�̋��̒��S���W�����ԃx�N�g�������߂�
	XMVECTOR vec = sphere1.center - sphere2.center;

	//�x�N�g���̒����̂Q��i�Q�_�Ԃ̋����̂Q��j�����߂�
	float sqLength = vec.m128_f32[0] * vec.m128_f32[0] + vec.m128_f32[1] * vec.m128_f32[1] + vec.m128_f32[2] * vec.m128_f32[2];

	//2�̋��̔��a�̍��v�����߂�
	float r = sphere1.radius + sphere2.radius;

	//�Q�_�Ԃ̋����̂Q�恃���a�̍��v�̂Q��Ȃ�Q�̋��͌������Ă���
	return  sqLength < r* r;
}

void Bullet::Load()
{
	bulletOBJ = Object::Instance()->CreateOBJ("sphere");
	//�f�o�b�N�e�L�X�g������
	debugText.Initialize();
}

void Bullet::Init(int number)
{

	if (number == fall)
	{//�����^��
		position = { 0.0f,50.0f,0.0f };
		gravity = 0.0f;
		vec = {};
	}
	else if (number == cannon)
	{//��C
		position = { -100.0f,0.0f,0.0f };
		gravity = 0.0f;
		vec = {};
	}
	else if (number == friction)
	{//���C
		position = { -50.0f,0.0f,0.0f };
		vec = { 2.0f,0.0f,0.0f };
		gravity = 1.0f;
	}
	else if (number == airresistance)
	{//��C��R
		position = { 0.0f,50.0f,0.0f };
		gravity = 1.0f;
		vec = {};
	}
	else if (number == repulsion)
	{
		position = { -25.0f,0.0f,0.0f };
		position2 = { 25.0f,0.0f,0.0f };
		m1 = 1.50f;	//����
		v1 = 4.50f;	//����
		v01 = 4.50f;	//�����x

		m2 = 2.00f;	//����
		v2 = -3.00f;	//����
		v02 = -3.00f;	//�����x
		Flag = true;
		vec = {};
	}
	
}

void Bullet::Update()
{

	//���Z�b�g
	if (Input::Instance()->KeybordPush(DIK_R))
	{
		Init(number);
	}
	if (Input::Instance()->KeybordTrigger(DIK_LEFT))
	{
		number -= 1;
		if (number < fall)
		{
			number = fall;
		}
		Init(number);
	}
	if (Input::Instance()->KeybordTrigger(DIK_RIGHT))
	{
		number += 1;
		if (number > repulsion)
		{
			number = repulsion;
		}
		Init(number);
	}

	if (number == fall)
	{//�����^��
		FallMovement();
	}//��C�o�[�V����
	else if (number == cannon)
	{
		Cannon();
	}
	else if (number == friction)
	{
		Friction();
	}
	else if (number == airresistance)
	{
		AirResistance();

	}
	else if (number == repulsion)
	{
		Repulsion();
	}
}

void Bullet::Draw()
{
	if (number == fall)
	{
		Object::Instance()->Draw(bulletOBJ, position, scale, angle, color);
		debugText.Print(20, 120, 2, "%d:Fall", number);
	}
	else if (number == cannon)
	{
		Object::Instance()->Draw(bulletOBJ, position, scale, angle, color);
		debugText.Print(20, 120, 2, "%d:Cannon", number);
	}
	else if (number == friction)
	{
		Object::Instance()->Draw(bulletOBJ, position, scale, angle, color);
		debugText.Print(20, 120, 2, "%d:friction", number);
	}
	else if (number == airresistance)
	{
		Object::Instance()->Draw(bulletOBJ, position, scale, angle, color);
		debugText.Print(20, 120, 2, "%d:airresistance", number);
	}
	else if (number == airresistance)
	{

	}
	else if (number == repulsion)
	{
		Object::Instance()->Draw(bulletOBJ, position, scale, angle, color);
		Object::Instance()->Draw(bulletOBJ, position2, scale, angle, color);

	}
	debugText.DrawAll();
}

void Bullet::FallMovement()
{
	//�d�͉����x
	gravity += gravityAccel;

	vec.y = -gravity;

	position += vec;
}

void Bullet::Cannon()
{
	gravity += gravityAccel;
	//���������𑫂�
	vec = Vec0;
	vec.y -= gravity;

	position += vec;
}

void Bullet::Friction()
{
	//��������
	float N = m * gravity;

	//�ő�Î~���C��
	float fs = staticFriction * N;
	if (vec.x < 0)
	{
		vec.x = 0.0f;
	}
	//�����C
	if (vec.x > 0)
	{
		float uN = dynamicFriction * N;
		vec.x -= uN;
	}


	position += vec;
}

void Bullet::AirResistance()
{
	//�d�͉����x
	gravity += gravityAccel;

	//��C��R
	float N = gravity * airResistance;


	vec.y = -gravity + N;

	position += vec;
}

void Bullet::Repulsion()
{
	Sphere sphere1;
	sphere1.center = XMVectorSet(position.x, position.y, position.z, 1);
	sphere1.radius = 5.0f;

	Sphere sphere2;
	sphere2.center = XMVectorSet(position2.x, position2.y, position2.z, 1);
	sphere2.radius = 5.0f;

	float a = m1 * v01 + m2 * v02;
	float b = m1 * v1 + m2 * v2;

	float c = v1 + v2;
	//if (Input::Instance()->KeybordTrigger(DIK_SPACE) && Flag)
	if (CheckSphere2Sphere(sphere1, sphere2) && Flag)
	{
		Flag = false;
		v1 = (v02 * m2) / m1;
		v2 = (v01 * m1) / m2;
	}

	//��C��R
	float air1 = v1 * airResistance;
	float air2 = v2 * airResistance;
	//��C��R
	float N1 = v1 * dynamicFriction;
	//��C��R
	float N2 = v2 * dynamicFriction;

	v1 = v1 - air1 - N1;
	v2 = v2 - air2 - N2;
	position.x += v1;

	position2.x += v2;

}







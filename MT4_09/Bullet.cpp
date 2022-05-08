#include "Bullet.h"

void Bullet::Load()
{
	bulletOBJ = Object::Instance()->CreateOBJ("sphere");
}

void Bullet::Init(int number)
{
	
	if (number == 1)
	{
		position = {0.0f,50.0f,0.0f};
	}
	else if (number == 2)
	{
		position = { -100.0f,0.0f,0.0f };
	}
	gravity = 0.0f;
}

void Bullet::Update(int number)
{

	vec = {};
	if (number == 1)
	{//�����^��

		//�d�͉����x
		gravity += gravityAccel;

		vec.y -= gravity;

		position += vec;
	}//��C�o�[�V����
	else if (number == 2)
	{
		gravity += gravityAccel;
		//���������𑫂�
		vec += Vec0;
		vec.y -= gravity;

		position += vec;

	}
}

void Bullet::Draw()
{

	Object::Instance()->Draw(bulletOBJ, position, scale, angle, color);

}

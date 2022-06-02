#include "Bullet.h"
#include"Input.h"
#include"Collision.h"

//球と球の当たり判定
bool CheckSphere2Sphere(const Sphere& sphere1, const Sphere& sphere2)
{
	//２つの球の中心座標を結ぶベクトルを求める
	XMVECTOR vec = sphere1.center - sphere2.center;

	//ベクトルの長さの２乗（２点間の距離の２乗）を求める
	float sqLength = vec.m128_f32[0] * vec.m128_f32[0] + vec.m128_f32[1] * vec.m128_f32[1] + vec.m128_f32[2] * vec.m128_f32[2];

	//2つの球の半径の合計を求める
	float r = sphere1.radius + sphere2.radius;

	//２点間の距離の２乗＜半径の合計の２乗なら２つの球は交差している
	return  sqLength < r* r;
}

void Bullet::Load()
{
	bulletOBJ = Object::Instance()->CreateOBJ("sphere");
	//デバックテキスト初期化
	debugText.Initialize();
}

void Bullet::Init(int number)
{

	if (number == fall)
	{//落下運動
		position = { 0.0f,50.0f,0.0f };
		gravity = 0.0f;
		vec = {};
	}
	else if (number == cannon)
	{//大砲
		position = { -100.0f,0.0f,0.0f };
		gravity = 0.0f;
		vec = {};
	}
	else if (number == friction)
	{//摩擦
		position = { -50.0f,0.0f,0.0f };
		vec = { 2.0f,0.0f,0.0f };
		gravity = 1.0f;
	}
	else if (number == airresistance)
	{//空気抵抗
		position = { 0.0f,50.0f,0.0f };
		gravity = 1.0f;
		vec = {};
	}
	else if (number == repulsion)
	{
		position = { -25.0f,0.0f,0.0f };
		position2 = { 25.0f,0.0f,0.0f };
		m1 = 1.50f;	//質量
		v1 = 4.50f;	//速さ
		v01 = 4.50f;	//初速度

		m2 = 2.00f;	//質量
		v2 = -3.00f;	//速さ
		v02 = -3.00f;	//初速度
		Flag = true;
		vec = {};
	}
	
}

void Bullet::Update()
{

	//リセット
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
	{//落下運動
		FallMovement();
	}//大砲バーション
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
	//重力加速度
	gravity += gravityAccel;

	vec.y = -gravity;

	position += vec;
}

void Bullet::Cannon()
{
	gravity += gravityAccel;
	//初期加速を足す
	vec = Vec0;
	vec.y -= gravity;

	position += vec;
}

void Bullet::Friction()
{
	//垂直効力
	float N = m * gravity;

	//最大静止摩擦力
	float fs = staticFriction * N;
	if (vec.x < 0)
	{
		vec.x = 0.0f;
	}
	//動摩擦
	if (vec.x > 0)
	{
		float uN = dynamicFriction * N;
		vec.x -= uN;
	}


	position += vec;
}

void Bullet::AirResistance()
{
	//重力加速度
	gravity += gravityAccel;

	//空気抵抗
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

	//空気抵抗
	float air1 = v1 * airResistance;
	float air2 = v2 * airResistance;
	//空気抵抗
	float N1 = v1 * dynamicFriction;
	//空気抵抗
	float N2 = v2 * dynamicFriction;

	v1 = v1 - air1 - N1;
	v2 = v2 - air2 - N2;
	position.x += v1;

	position2.x += v2;

}







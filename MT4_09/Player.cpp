#include"Player.h"
#include"Shape.h"
#include"Input.h"
#include "MapStage.h"
#include"Collision.h"
Player::Player()
{}

Player::~Player()
{}

void Player::Init()
{
	playerObject = Object::Instance()->CreateOBJ("player");
	oldPosition = position;
}

void Player::Update(Enemy *enemy)
{
	if (enemy == nullptr)
	{
		return;
	}
	//移動
	Move();
	//ジャンプ
	Jump();
}

void Player::Draw()
{
	Object::Instance()->Draw(playerObject, position, scale, angle, color);
#if _DEBUG

#endif

}

void Player::SetPosition(Vec3 position)
{
	this->position = position;
}

void Player::GroundFlag()
{
	groundFlag = true;
}

//移動
void Player::Move()
{
	oldPosition = position;
	//移動
	if (Input::Instance()->KeybordPush(DIK_RIGHT))
	{
		position.x += speed.x;
	}
	if (Input::Instance()->KeybordPush(DIK_LEFT))
	{
		position.x -= speed.x;
	}
	if (Input::Instance()->KeybordPush(DIK_UP))
	{
		position.z += speed.z;
	}
	if (Input::Instance()->KeybordPush(DIK_DOWN))
	{
		position.z -= speed.z;
	}
}

void Player::Jump()
{
	//ジャンプ
	if (Input::Instance()->KeybordPush(DIK_SPACE) && groundFlag == true)
	{
		jumpPower = jumpPowerMax;
	}

	//重力加算
	position.y -= gravity;
	if (jumpPower > 0)
	{
		position.y += jumpPower;
		jumpPower -= jumpPowerDelay;
	}

	groundFlag = false;
}





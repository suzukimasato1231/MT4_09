#pragma once
#include"Object.h"
#include"CollisionPrimitive.h"
#include"Easing.h"
#include"Enemy.h"

class Player
{
public:
	Player();//コンストラクタ

	~Player();//ですコンストラクタ

	void Init();//初期化

	void Update(class Enemy *enemy);//更新

	void Draw();//描画

	void SetPosition(Vec3 position);
	/// <summary>
	/// trueにする
	/// </summary>
	void GroundFlag();
private:
	/// <summary>
	/// プレイヤー移動
	/// </summary>
	void Move();
	/// <summary>
	/// プレイヤージャンプ
	/// </summary>
	void Jump();
public://取得系
	//座標
	Vec3 GetPosition() { return position; }

	Vec3 GetOldPosition() { return oldPosition; }

	//Vec3 GetOldPosition() { return oldPosition; }

	Vec3 GetPSize() { return pScale; }
private:
	Object::ObjectData playerObject;	//プレイヤーオブジェクト
	Vec3 position{ 10.0f,0.0f,0.0f };	//座標
	Vec3 oldPosition{};					//1つ前の座標
	Vec3 speed{ 2.0f,2.0f,2.0f };		//プレイヤースピード
	Vec3 scale{ 1.0f,1.0f,1.0f };		//大きさ
	Vec3 angle{ 0.0f,0.0f,0.0f };		//角度
	Vec4 color{ 1.0f,1.0f,1.0f,1.0f };	//色
	Vec3 pScale = { 5.0f,10.0f,5.0f };						//プレイヤー大きさ
	int HP = 10;						//プレイヤーHP

	//ジャンプ
	const float jumpPowerMax = 5.0f;
	float jumpPower = 5.0f;//ジャンプパワー
	float jumpPowerDelay = 0.2;
	float gravity = 2.0f;//重力
	bool jumpFlag = false;//ジャンプをしたか
	bool groundFlag = false;//地面に接しているかどうか
};
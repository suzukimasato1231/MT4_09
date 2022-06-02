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
	//‰Šú‰»
	void Init(int number);
	//XV
	void Update();
	//•`‰æ
	void Draw();
private:
	//—‰º‰^“®
	void FallMovement();
	//‘å–C
	void Cannon();
	//–€C
	void Friction();
	//‹ó‹C’ïR
	void AirResistance();
	//”½”­
	void Repulsion();
private:
	DebugText debugText;
	//‚Ç‚Ìˆ—‚©
	int number = 1;

	Object::ObjectData bulletOBJ;
	Vec3 position{};
	Vec3 position2{};
	Vec3 scale{ 5.0f,5.0f,5.0f };
	Vec3 angle{};
	Vec4 color{};
	float time = 0;

	Vec3 vec = {};						//‘¬“x
	float gravity = 0.0f;		//d—Í
	const float gravityAccel = 0.03f;	//d—Í‰Á‘¬“x

public:	//–€C
	const float   m = 1.0f;//¿—Ê
	const float staticFriction = 0.8f;	//Ã~–€C
	const float dynamicFriction = 0.02f;	//“®–€C
public:	//‹ó‹C’ïR
	const float airResistance = 0.015f;	//‹ó‹C’ïR’è”
	float air = 0.0f;					//‹ó‹C’ïR
	Vec3 Vec0 = { 1.0f,1.0f,0.0f };		//‰‘¬“x
public://”½”­
	float m1 = 1.0f;	//¿—Ê
	float v1 = 3.0f;	//‘¬‚³
	float v01 = 2.0f;	//‰‘¬“x

	float m2 = 1.0f;	//¿—Ê
	float v2 = 5.0f;	//‘¬‚³
	float v02 = 2.0f;	//‰‘¬“x

	bool Flag = true;

};


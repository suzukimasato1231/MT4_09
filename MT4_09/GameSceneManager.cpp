#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"

GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	safe_delete(particleMan);
	safe_delete(lightGroup);
	safe_delete(fbxObject1);
	safe_delete(model1);
	safe_delete(mapStage);
	safe_delete(bullet);
	//XAudio2解放
	audio->xAudio2.Reset();
	//音データ解放
	Audio::SoundUnload(&sound1);
	Audio::SoundUnload(&sound2);
	safe_delete(audio);
}
void GameSceneManager::Initialize(_DirectX* directX)
{
	assert(directX);
	this->directX = directX;
	//Audioクラス作成
	audio = Audio::Create();
	//カメラクラス作成
	camera = Camera::Create();
	//スプライトクラス作成
	Sprite::Instance()->Init();
	//FBX初期化
	FBXObject3d::SetDevice(directX->GetDevice());
	FBXObject3d::SetCmdList(directX->GetCmandList());
	FBXObject3d::SetCamera(camera);
	FBXObject3d::CreateGraphicsPipeline();
	//図形モデル初期化
	Shape::Init(directX->GetDevice());
	//パーティクル初期化
	ParticleManager::StaticInitialize(directX->GetDevice(), directX->GetCmandList(), window_width, window_height);
	ParticleManager::SetCamera(camera);
	//パーティクルクラス作成
	particleMan = ParticleManager::Create();
	//ライトグループクラス作成
	lightGroup = LightGroup::Create();
	//デバックテキスト初期化
	debugText.Initialize();
	//3Dオブジェクト初期化
	Object::Instance()->Init(directX->GetDevice(), directX->GetCmandList(), camera, lightGroup);
}

void GameSceneManager::Init()
{
	//音データ読み込み
	sound1 = Audio::SoundLoadWave("Resources/i.wav");

	// 3Dオブエクトにライトをセット
	//Object3d::SetLightGroup(lightGroup);
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });

	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetSpotLightActive(0, false);
	lightGroup->SetCircleShadowActive(0, false);

	//カメラ位置をセット
	camera->SetCamera(Vec3{ 0,0,-100 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });

	//スプライト画像読み込み
	BGGraph = Sprite::Instance()->SpriteCreate(L"Resources/backgroundA.png");
	operationGraph = Sprite::Instance()->SpriteCreate(L"Resources/Operation.png");
	//3Dオブジェクト画像読み込み
	graph3 = Texture::Instance()->LoadTexture(L"Resources/white1x1.png");
	graph1 = Texture::Instance()->LoadTexture(L"Resources/texture2.jpg");

	particleGraph = Texture::Instance()->LoadTexture(L"Resources/particle.jpg");

	bullet = new Bullet();
	bullet->Load();
}

void GameSceneManager::Update()
{
	//リセット
	if (Input::Instance()->KeybordPush(DIK_R))
	{
		bullet->Init(number);
	}

	if (Input::Instance()->KeybordTrigger(DIK_LEFT)|| Input::Instance()->KeybordTrigger(DIK_A))
	{
		number -= 1;
		if (number < 1)
		{
			number = 1;
		}
		bullet->Init(number);
	}
	if (Input::Instance()->KeybordTrigger(DIK_RIGHT)|| Input::Instance()->KeybordTrigger(DIK_D))
	{
		number += 1;
		if (number > 2)
		{
			number = 2;
		}
		bullet->Init(number);
	}

	bullet->Update(number);
	//パーティクル更新
	particleMan->Update();
	//ライト更新
	lightGroup->Update();
}

void GameSceneManager::Draw()
{
	//オブジェクト描画前処理
	Object::Instance()->PreDraw();
	Sprite::Instance()->PreDraw();

	//背景描画
	//Drawにカーソル合わせればコメントアウトしてあるからなにがどの変数かわかるよ
//	Sprite::Instance()->Draw(BGGraph, pos, window_width, window_height);

	//オブジェクト
	bullet->Draw();
	//パーティクル描画
	particleMan->Draw(particleGraph);

	//前景描画
	//デバックテキスト%dと%f対応

	Sprite::Instance()->Draw(operationGraph, Vec2(0.0f, 0.0f), 300, 100);
	if (number == 1)
	{
		debugText.Print(20, 120, 2, "%d:Fall", number);
	}
	else if (number == 2)
	{
		debugText.Print(20, 120, 2, "%d:Cannon", number);
	}
	

	//デバックテキスト描画ここは変わらない
	debugText.DrawAll();
}

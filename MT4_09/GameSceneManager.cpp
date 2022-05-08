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
	//XAudio2���
	audio->xAudio2.Reset();
	//���f�[�^���
	Audio::SoundUnload(&sound1);
	Audio::SoundUnload(&sound2);
	safe_delete(audio);
}
void GameSceneManager::Initialize(_DirectX* directX)
{
	assert(directX);
	this->directX = directX;
	//Audio�N���X�쐬
	audio = Audio::Create();
	//�J�����N���X�쐬
	camera = Camera::Create();
	//�X�v���C�g�N���X�쐬
	Sprite::Instance()->Init();
	//FBX������
	FBXObject3d::SetDevice(directX->GetDevice());
	FBXObject3d::SetCmdList(directX->GetCmandList());
	FBXObject3d::SetCamera(camera);
	FBXObject3d::CreateGraphicsPipeline();
	//�}�`���f��������
	Shape::Init(directX->GetDevice());
	//�p�[�e�B�N��������
	ParticleManager::StaticInitialize(directX->GetDevice(), directX->GetCmandList(), window_width, window_height);
	ParticleManager::SetCamera(camera);
	//�p�[�e�B�N���N���X�쐬
	particleMan = ParticleManager::Create();
	//���C�g�O���[�v�N���X�쐬
	lightGroup = LightGroup::Create();
	//�f�o�b�N�e�L�X�g������
	debugText.Initialize();
	//3D�I�u�W�F�N�g������
	Object::Instance()->Init(directX->GetDevice(), directX->GetCmandList(), camera, lightGroup);
}

void GameSceneManager::Init()
{
	//���f�[�^�ǂݍ���
	sound1 = Audio::SoundLoadWave("Resources/i.wav");

	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
	//Object3d::SetLightGroup(lightGroup);
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });

	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetSpotLightActive(0, false);
	lightGroup->SetCircleShadowActive(0, false);

	//�J�����ʒu���Z�b�g
	camera->SetCamera(Vec3{ 0,0,-100 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });

	//�X�v���C�g�摜�ǂݍ���
	BGGraph = Sprite::Instance()->SpriteCreate(L"Resources/backgroundA.png");
	operationGraph = Sprite::Instance()->SpriteCreate(L"Resources/Operation.png");
	//3D�I�u�W�F�N�g�摜�ǂݍ���
	graph3 = Texture::Instance()->LoadTexture(L"Resources/white1x1.png");
	graph1 = Texture::Instance()->LoadTexture(L"Resources/texture2.jpg");

	particleGraph = Texture::Instance()->LoadTexture(L"Resources/particle.jpg");

	bullet = new Bullet();
	bullet->Load();
}

void GameSceneManager::Update()
{
	//���Z�b�g
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
	//�p�[�e�B�N���X�V
	particleMan->Update();
	//���C�g�X�V
	lightGroup->Update();
}

void GameSceneManager::Draw()
{
	//�I�u�W�F�N�g�`��O����
	Object::Instance()->PreDraw();
	Sprite::Instance()->PreDraw();

	//�w�i�`��
	//Draw�ɃJ�[�\�����킹��΃R�����g�A�E�g���Ă��邩��Ȃɂ��ǂ̕ϐ����킩���
//	Sprite::Instance()->Draw(BGGraph, pos, window_width, window_height);

	//�I�u�W�F�N�g
	bullet->Draw();
	//�p�[�e�B�N���`��
	particleMan->Draw(particleGraph);

	//�O�i�`��
	//�f�o�b�N�e�L�X�g%d��%f�Ή�

	Sprite::Instance()->Draw(operationGraph, Vec2(0.0f, 0.0f), 300, 100);
	if (number == 1)
	{
		debugText.Print(20, 120, 2, "%d:Fall", number);
	}
	else if (number == 2)
	{
		debugText.Print(20, 120, 2, "%d:Cannon", number);
	}
	

	//�f�o�b�N�e�L�X�g�`�悱���͕ς��Ȃ�
	debugText.DrawAll();
}

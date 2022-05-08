#pragma once
#include<vector>
#include<string>
#include<d3dx12.h>
#include"Pipeline.h"
#include"Camera.h"
#include<unordered_map>
#include"LightGroup.h"
#include"Vec.h"
#include"Singleton.h"

#include"../Texture.h"

#pragma comment(lib,"d3d12.lib")

 const int constBufferNum = 256;
class Object:public Singleton<Object>
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	friend Singleton<Object>;
public:
	static ID3D12Device *dev;					//�f�o�C�X
	static ID3D12GraphicsCommandList *cmdList;	//�R�}���h���X�g
public://�\����
	////���_�f�[�^�\����
	struct Vertex
	{
		Vec3 pos;//xyz���W
		Vec3 normal;//�@���x�N�g��
		Vec2 uv;//uv���W
	};

	//�}�e���A��
	struct Material
	{
		std::string name;			//�}�e���A����
		Vec3 ambient;			//�A���r�G���g�e���x
		Vec3 diffuse;			//�f�B�t���[�Y�e���x
		Vec3 specular;			//�X�y�L�����[�e���x
		float alpha;				//�A���t�@
		std::string textureFilename;//�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material()
		{
			ambient = { 1.0f,1.0f,1.0f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
	/// <summary>
	/// �ʒu�A�傫���A�F���
	/// </summary>
	struct PSC
	{
		Vec3 position = {};
		Vec3 scale = {};
		Vec4 color = {};
	};

	//�I�u�W�F�N�g�f�[�^�\����
	struct ObjectData
	{
		//���_�f�[�^
		std::vector<Vertex *> vertices;
		//�C���f�b�N�X�f�[�^
		std::vector<unsigned short *> indices;
		//���_�o�b�t�@�̐���
		ComPtr<ID3D12Resource> vertBuff = nullptr;
		//�C���f�b�N�X�o�b�t�@
		ComPtr<ID3D12Resource> indexBuff = nullptr;
		//���_�o�b�t�@�r���[�̍쐬
		D3D12_VERTEX_BUFFER_VIEW vbView{};
		//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
		D3D12_INDEX_BUFFER_VIEW ibView{};
		//�I�u�W�F�ǂݍ��ݗp
		int OBJTexture = 0;
		//���_�@���X���[�W���O�p�f�[�^
		std::unordered_map<unsigned short, std::vector<unsigned short>>smoothData;
		//���[���h�ϊ�
		XMMATRIX matWorld;
		//�e�N���X
		ObjectData *parent = nullptr;
		//�}�e���A��
		Material material;
		//�ʒu�A�傫���A�F���
		PSC psc;
	};

	struct ConstBuffer
	{
		//GPU���\�[�X�̐���
		ComPtr<ID3D12Resource>constBuff = nullptr;
	};

	//OBJ�f�[�^�֘A
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;//�r���[�v���W�F�N�V�����s��
		XMMATRIX world;//���[���h���W
		Vec3 cameraPos;//�J�������W(���[���h���W)
		Vec4 color;
	};
	struct ConstBufferDataB1
	{
		Vec3 ambient;	//�A���r�G���g�W��
		float pad1;			//�p�f�B���O
		Vec3 diffuse;	//�f�B�t���[�Y�W��
		float pad2;			//�p�f�B���O
		Vec3 specular;	//�X�y�L�����[�W��
		float alpha;		//�A���t�@
	};

	//OBJ�萔�o�b�t�@
	struct OBJData
	{
		ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@
		ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@
	};
public://�p�C�v���C���ݒ�
	Pipeline::PipelineSet objPipelineSet;		//OBJ�ǂݍ���
public://�ϐ�	
	//OBJ�f�[�^
	std::vector<OBJData *> OBJdata;
public:
	Object() {};
	~Object();
	//������
	void Init(ID3D12Device *dev, ID3D12GraphicsCommandList *cmdList, Camera *camera, LightGroup *lightGroup);
	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Object *Create();
public:
	//�J�����N���X
	static Camera *camera;
	//���C�g�N���X
	static LightGroup *lightGroup;
public://�}�`���f���쐬
	/// <summary>
	/// OBJ�I�u�W�F�N�g�쐬
	/// </summary>
	/// <param name="filename">filename</param>
	/// <param name="smoothing"></param>
	/// <returns></returns>
	ObjectData CreateOBJ(const std::string filename, bool smoothing = false);
public://�I�u�W�F�N�g�֘A
	// �e�N�X�`���ǂݍ���
	//int LoadTexture(const wchar_t *filename);
	//�I�u�W�F�N�g�`��O
	void PreDraw();
public://OBJ�֘A
	//int OBJLoadTexture(const std::string &directoryPath, const std::string &filename);
	//�}�e���A���ǂݍ���
	int LoadMaterial(const std::string &directoryPath, const std::string &filename, ObjectData &polygon);
	/// <summary>
	/// �G�b�W�������f�[�^�̒ǉ�
	/// </summary>
	/// <param name="indexPosition">���W�C���f�b�N�X</param>
	/// <param name="indexVertex">���_�C���f�b�N�X</param>
	void AddSmoothData(ObjectData &polygon, unsigned short indexPosition, unsigned short indexVertex);
	///<summary>
	///���������ꂽ���_�@���̌v�Z
	/// </summary>
	void CalculateSmoothedVertexNormals(ObjectData &polygon);

	/// <summary>
	/// ���_�f�[�^�̐����擾
	/// </summary>
	/// <returns>���_�f�[�^�̐�</returns>
	inline size_t GetVertexCount(ObjectData &polygon);
	//���f���쐬
	void OBJCreateModel(ObjectData &polygon);
	//�萔�o�b�t�@�ݒ�
	void OBJConstantBuffer();
	/// <summary>
	/// �I�u�W�F�N�g�̃f�[�^�X�V
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="matRot">��]</param>
	/// <param name="color">�F</param>
	void MatWord(ObjectData &polygon, Vec3 position, Vec3 scale, Vec3 matRot, Vec4 color);
	/// <summary>
	/// OBJ�`��
	/// </summary>
	/// <param name="polygon">�I�u�W�F�N�g�f�[�^</param>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="matRot">��]</param>
	/// <param name="color">�F</param>
	void Draw(ObjectData &polygon, Vec3 position, Vec3 scale, Vec3 matRot, Vec4 color = { 1,1,1,1 }, int graph = 0);
public:
	size_t OBJNum = 0;//OBJ�ǂݍ��݂̐�
	size_t objNum = 0;//�I�u�W�F�N�g�̐�
	size_t texNum = 0;//�e�N�X�`���̐�
};
#pragma once
#include <d3dx12.h>
#include"Singleton.h"
class Texture :public Singleton<Texture>
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	template <class T> using vector = std::vector<T>;
	friend Singleton<Texture>;
public:
	static ID3D12Device *dev;					//�f�o�C�X
	static const int textureMax = 1024;
	//�e�N�X�`���f�[�^
	struct TextureData
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		ComPtr<ID3D12Resource> texbuff;
	};

	Texture();

	~Texture();
	//������
	void Init(ID3D12Device *dev);
	//�摜�ǂݍ���
	int LoadTexture(const wchar_t *filename);
	//OBJ�摜�ǂݍ���
	int OBJLoadTexture(const std::string &directoryPath, const std::string &filename);

	//SRV���l��
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSRV(int i);

	ID3D12Resource *GetTexbuff(int i);
	//desc�l��
	ID3D12DescriptorHeap *GetDescHeap();
private:
	//�萔�o�b�t�@�p�̃f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap >descHeap = { nullptr };

	//�e�N�X�`���f�[�^�̍쐬
	std::vector <TextureData *>textureData;

	int texNum = 0;
};


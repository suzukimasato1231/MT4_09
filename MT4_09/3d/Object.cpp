#include "Object.h"
#include <DirectXTex.h>
#include<fstream>
#include<sstream>
#include<string>

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

ID3D12Device *Object::dev = nullptr;
ID3D12GraphicsCommandList *Object::cmdList = nullptr;
Camera *Object::camera = nullptr;
LightGroup *Object::lightGroup = nullptr;
Object::~Object()
{
	//OBJ�f�[�^�폜
	for (int i = (int)OBJdata.size() - 1; i >= 0; i--)
	{
		delete OBJdata[i];
		OBJdata.erase(OBJdata.begin() + i);
	}
}

void  Object::Init(ID3D12Device *dev, ID3D12GraphicsCommandList *cmdList, Camera *camera, LightGroup *lightGroup)
{
	Object::dev = dev;

	Object::cmdList = cmdList;

	Object::camera = camera;

	Object::lightGroup = lightGroup;

	//�p�C�v���C������
	objPipelineSet = Pipeline::OBJCreateGraphicsPipeline(Object::dev);
}

Object *Object::Create()
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Object *object = new Object();
	if (object == nullptr) {
		return nullptr;
	}

	// ������
	return object;
}

void Object::AddSmoothData(ObjectData &polygon, unsigned short indexPosition, unsigned short indexVertex)
{
	polygon.smoothData[indexPosition].emplace_back(indexVertex);
}

void Object::CalculateSmoothedVertexNormals(ObjectData &polygon)
{
	auto itr = polygon.smoothData.begin();
	for (; itr != polygon.smoothData.end(); ++itr)
	{
		//�e�ʗp�̋��ʒ��_�R���N�V����
		std::vector<unsigned short> &v = itr->second;
		//�S���_�̖@���𕽋ς���
		XMVECTOR normal = {};
		for (unsigned short index : v)
		{
			normal += XMVectorSet(polygon.vertices[index]->normal.x, polygon.vertices[index]->normal.y, polygon.vertices[index]->normal.z, 0);
		}
		normal = XMVector3Normalize(normal / (float)v.size());
		//���ʖ@�����g�p����S�Ă̒��_�f�[�^�ɏ�������
		for (unsigned short index : v)
		{
			polygon.vertices[index]->normal = { normal.m128_f32[0],normal.m128_f32[1],normal.m128_f32[2] };
		}
	}
}

inline size_t Object::GetVertexCount(ObjectData &polygon)
{
	return polygon.vertices.size();
}


void Object::MatWord(ObjectData &polygon, Vec3 position, Vec3 scale, Vec3 rotation, Vec4 color)
{
	HRESULT result;
	if (polygon.psc.position.x != position.x || polygon.psc.position.y != position.y || polygon.psc.position.z != position.z
		|| polygon.psc.scale.x != scale.x || polygon.psc.scale.y != scale.y || polygon.psc.scale.z != scale.z
		|| polygon.psc.color.x != color.x || polygon.psc.color.y != color.y || polygon.psc.color.z != color.z || polygon.psc.color.w != color.w)
	{
		//���[���h�ϊ��F//�X�P�[�����O//��]�s��XMMATRIX//���s�ړ��s��
		XMMATRIX matScale, matRot, matTrains;
		//���[���h�ϊ�
		matScale = XMMatrixScaling(scale.x, scale.y, scale.z);//�傫��
		matTrains = XMMatrixTranslation(position.x, position.y, position.z);//���s�ړ��s����Čv�Z
		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));//Z���܂��ɂS�T�x��]
		matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));//X���܂��ɂS�T�x��]
		matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));//Y���܂��ɂS�T�x��]

		polygon.matWorld = XMMatrixIdentity();//���[���h�s��͖��t���[�����Z�b�g
		polygon.matWorld *= matScale;//���[���h�s��ɃX�P�[�����O�𔽉f
		polygon.matWorld *= matRot;//���[���h�s��ɉ�]�𔽉f
		polygon.matWorld *= matTrains;//���[���h�s��ɕύX�ړ��𔽉f

		polygon.psc.position = position;
		polygon.psc.scale = scale;
		polygon.psc.color = color;
	}


	const XMMATRIX &matViewProjection = camera->GetMatView() * camera->GetProjection();
	const Vec3 &cameraPos = camera->GetEye();
	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	ConstBufferDataB0 *constMap = nullptr;
	result = Object::OBJdata[OBJNum]->constBuffB0->Map(0, nullptr, (void **)&constMap);
	//�s��̍���   ���[���h�ϊ��s�� �� �r���[�ϊ��s�� �� �ˉe�ϊ��s��
	constMap->viewproj = matViewProjection;
	if (polygon.parent == nullptr)
	{
		constMap->world = polygon.matWorld;
	}
	else
	{
		constMap->world = polygon.matWorld * polygon.parent->matWorld;
	}
	constMap->cameraPos = cameraPos;
	constMap->color = color;
	Object::OBJdata[OBJNum]->constBuffB0->Unmap(0, nullptr);


	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB1 *constMap1 = nullptr;
	result = Object::OBJdata[OBJNum]->constBuffB1->Map(0, nullptr, (void **)&constMap1);
	constMap1->ambient = polygon.material.ambient;
	constMap1->diffuse = polygon.material.diffuse;
	constMap1->specular = polygon.material.specular;
	constMap1->alpha = polygon.material.alpha;
	Object::OBJdata[OBJNum]->constBuffB1->Unmap(0, nullptr);
}

void Object::PreDraw()
{
	objNum = 0;
	OBJNum = 0;
}

void Object::OBJConstantBuffer()
{
	HRESULT result;
	Object::OBJdata.push_back(new Object::OBJData);
	// �萔�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Object::OBJdata[Object::OBJdata.size() - 1]->constBuffB0));

	// �萔�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Object::OBJdata[Object::OBJdata.size() - 1]->constBuffB1));
}


void Object::Draw(ObjectData &polygon, Vec3 position, Vec3 scale, Vec3 rotation, Vec4 color, int graph)
{
	//�v���~�e�B�u�`��̐ݒ�R�}���h�i�O�p�`���X�g�j
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�f�X�N���v�^�q�[�v���Z�b�g
	ID3D12DescriptorHeap *ppHeaps[] = { Texture::Instance()->GetDescHeap()};
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	if (OBJNum >= Object::OBJdata.size())
	{
		//�萔�o�b�t�@
		OBJConstantBuffer();
	}
	//�X�V
	MatWord(polygon, position, scale, rotation, color);

	cmdList->SetPipelineState(objPipelineSet.pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(objPipelineSet.rootsignature.Get());

	//���_�o�b�t�@�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &polygon.vbView);

	////�C���f�b�N�X�o�b�t�@�r���[�̃Z�b�g�R�}���h
	cmdList->IASetIndexBuffer(&polygon.ibView);

	//�q�[�v�̐擪�ɂ���CBV�����[�g�p�����[�^�O�Ԃɐݒ�
	cmdList->SetGraphicsRootConstantBufferView(0, Object::OBJdata[OBJNum]->constBuffB0->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, Object::OBJdata[OBJNum]->constBuffB1->GetGPUVirtualAddress());
	if (polygon.OBJTexture == 0)
	{
		//�q�[�v�̂Q�Ԗڂɂ���SRV�����[�g�p�����[�^�P�Ԃɐݒ�
		cmdList->SetGraphicsRootDescriptorTable(2, Texture::Instance()->GetGPUSRV(graph));
	}
	else
	{
		//�q�[�v�̂Q�Ԗڂɂ���SRV�����[�g�p�����[�^�P�Ԃɐݒ�
		cmdList->SetGraphicsRootDescriptorTable(2, Texture::Instance()->GetGPUSRV(polygon.OBJTexture));
	}
	//���C�g�̕`��
	lightGroup->Draw(cmdList, 3);
	//�`��R�}���h          //���_��				//�C���X�^���X��	//�J�n���_�ԍ�		//�C���X�^���X���Ƃ̉��Z�ԍ�
	cmdList->DrawIndexedInstanced((UINT)polygon.indices.size(), 1, 0, 0, 0);
	OBJNum++;
}


int Object::LoadMaterial(const std::string &directoryPath, const std::string &filename, ObjectData &polygon)
{
	int texNumber = 0;
	//�t�@�C���X�g���[��
	std::ifstream file;
	//�}�e���A���t�@�C�����J��
	file.open(directoryPath + filename);
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}
	//1�s���ǂݍ���
	string line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ�
		std::istringstream line_stream(line);
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');
		//�擪�̃^�u�����͖�������
		if (key[0] == '\t')
		{
			key.erase(key.begin());//�擪�̕������폜
		}
		//�擪������newmtl�Ȃ�}�e���A����
		if (key == "newmtl")
		{
			//�}�e���A�����ǂݍ���
			line_stream >> polygon.material.name;
		}
		//�擪������Ka�Ȃ�A���r�G���g�F
		if (key == "Ka")
		{
			line_stream >> polygon.material.ambient.x;
			line_stream >> polygon.material.ambient.y;
			line_stream >> polygon.material.ambient.z;
		}
		//�擪������Kd�Ȃ�f�B�t���[�Y�F
		if (key == "Kd")
		{
			line_stream >> polygon.material.diffuse.x;
			line_stream >> polygon.material.diffuse.y;
			line_stream >> polygon.material.diffuse.z;
		}
		//�擪������Ks�Ȃ�X�y�L�����[�F
		if (key == "Ks")
		{
			line_stream >> polygon.material.specular.x;
			line_stream >> polygon.material.specular.y;
			line_stream >> polygon.material.specular.z;
		}
		//�擪������map_Kd�Ȃ�e�N�X�`����
		if (key == "map_Kd")
		{
			//�e�N�X�`���̃t�@�C�����ǂݍ���
			line_stream >> polygon.material.textureFilename;
			//�e�N�X�`���ǂݍ���
			polygon.OBJTexture = Texture::Instance()->OBJLoadTexture(directoryPath, polygon.material.textureFilename);
		}
	}
	//�t�@�C�������
	file.close();
	return  0;
}

void Object::OBJCreateModel(ObjectData &polygon)
{
	HRESULT result;
	//���_�f�[�^�S�̂̃T�C�Y�����_�f�[�^����̃T�C�Y�����_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * polygon.vertices.size());

	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * polygon.indices.size());

	////���_�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&polygon.vertBuff)
	);

	////�C���f�b�N�X�o�b�t�@�̐���
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&polygon.indexBuff));

	Vertex *vertMap = nullptr;
	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	result = polygon.vertBuff->Map(0, nullptr, (void **)&vertMap);

	//�S���_�ɑ΂���
	for (size_t i = 0; i < polygon.vertices.size(); i++)
	{
		vertMap[i] = *polygon.vertices[i];//���W�R�s�[
	}

	//�}�b�v������
	polygon.vertBuff->Unmap(0, nullptr);

	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	unsigned short *indexMap = nullptr;
	result = polygon.indexBuff->Map(0, nullptr, (void **)&indexMap);

	//�S�C���f�b�N�X�ɑ΂���
	for (size_t i = 0; i < polygon.indices.size(); i++)
	{
		indexMap[i] = *polygon.indices[i];//�C���f�b�N�X���R�s�[
	}
	//�q���������
	polygon.indexBuff->Unmap(0, nullptr);

	//���_�o�b�t�@�r���[�̍쐬
	polygon.vbView.BufferLocation =
		polygon.vertBuff->GetGPUVirtualAddress();
	polygon.vbView.SizeInBytes = sizeVB;
	polygon.vbView.StrideInBytes = sizeof(Vertex);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	polygon.ibView.BufferLocation = polygon.indexBuff->GetGPUVirtualAddress();
	polygon.ibView.Format = DXGI_FORMAT_R16_UINT;
	polygon.ibView.SizeInBytes = sizeIB;
}


Object::ObjectData Object::CreateOBJ(const std::string filename, bool smoothing)
{
	Object::ObjectData polygon;

	int index = 0;//�C���f�b�N�X�̐�����
	//�t�@�C���X�g���[��
	std::ifstream file;
	//.obj�t�@�C�����J��
	std::string directoryPath = "Resources/" + filename + "/";
	file.open(directoryPath + filename + ".obj");
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}
	vector<Vec3>positions;//���_���W
	vector<Vec3>normals;//�@���x�N�g��
	vector<Vec2>texcoords;//�e�N�X�`��UV
	//�P�s���ǂݍ���
	string line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		if (key == "mtllib")
		{
			//�}�e���A���̃t�@�C�����ǂݍ���
			string filename;
			line_stream >> filename;
			//�}�e���A���ǂݍ���
			//polygon.OBJTexture = LoadMaterial(directoryPath, filename);
			LoadMaterial(directoryPath, filename, polygon);
		}

		//�擪������v�Ȃ璸�_���W
		if (key == "v")
		{
			//X,Y,Z���W�ǂݍ���
			Vec3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//���W�f�[�^�ɒǉ�
			positions.emplace_back(position);
		}
		//�擪������vt�Ȃ�e�N�X�`��
		if (key == "vt")
		{
			//U,V�����ǂݍ���
			Vec2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V�������]
			texcoord.y = 1.0f - texcoord.y;
			//�e�N�X�`�����W�f�[�^�ɒǉ�
			texcoords.emplace_back(texcoord);
		}
		//�擪������vn�Ȃ�@���x�N�g��
		if (key == "vn")
		{
			//X,Y,Z�����ǂݍ���
			Vec3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;
			//�@���x�N�g���f�[�^�ɒǉ�
			normals.emplace_back(normal);
		}

		//�擪������f�Ȃ�|���S���i�O�p�`�j
		if (key == "f")
		{
			int faceIndexCount = 0;
			//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			string index_string;
			while (getline(line_stream, index_string, ' '))
			{
				//���_�C���f�b�N�X�P���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexNormal, indexTexcoord;
				index_stream >> indexPosition;
				index_stream.seekg(1, ios_base::cur);//�X���b�V�����΂�
				index_stream >> indexTexcoord;
				index_stream.seekg(1, ios_base::cur);//�X���b�V�����΂�
				index_stream >> indexNormal;

				//���_�f�[�^�̒ǉ�
				Vertex vertex{};
				vertex.pos = positions[indexPosition - 1];
				vertex.normal = normals[indexNormal - 1];
				vertex.uv = texcoords[indexTexcoord - 1];
				polygon.vertices.push_back(new Vertex);
				polygon.vertices[polygon.vertices.size() - 1]->pos = vertex.pos;
				polygon.vertices[polygon.vertices.size() - 1]->normal = vertex.normal;
				polygon.vertices[polygon.vertices.size() - 1]->uv = vertex.uv;
				//�G�b�W�~�����p�̃f�[�^��ǉ�
				if (smoothing)
				{
					//v�L�[(���W�f�[�^)�̔ԍ��ƁA�S�č����������_�̃C���f�b�N�X���Z�b�g�œo�^����
					AddSmoothData(polygon, indexPosition, (unsigned short)GetVertexCount(polygon) - 1);
				}
				// �C���f�b�N�X�f�[�^�̒ǉ�
				if (faceIndexCount >= 3) {
					// �l�p�`�|���S����4�_�ڂȂ̂ŁA
					// �l�p�`��0,1,2,3�̓� 2,3,0�ŎO�p�`���\�z����
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - 1 - index));
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - 1 - index));
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - 5 - index));
					index += 2;
				}
				else
				{
					polygon.indices.push_back(new unsigned short(polygon.indices.size() - index));
				}

				faceIndexCount++;

			}
		}
	}
	//�t�@�C�������
	file.close();
	//���_�@���̕��ςɂ��G�b�W���~����
	if (smoothing)
	{
		CalculateSmoothedVertexNormals(polygon);
	}
	OBJCreateModel(polygon);

	return polygon;
}

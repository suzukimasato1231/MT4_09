#include"Shape.h"
ID3D12Device *Shape::dev = nullptr;
Shape::Shape()
{}

void Shape::Init(ID3D12Device *dev)
{
	Shape::dev = dev;
}

Object::ObjectData Shape::CreateTriangularPyramid(const float width, const float height)
{
	Object::ObjectData polygon;
	const int DIV = 3;
	//�O�p��
	for (int i = 0; i < DIV; i++)
	{
		polygon.vertices.push_back(new Object::Vertex);
		polygon.vertices[polygon.vertices.size() - 1]->pos = { width * sinf(2 * XM_PI / DIV * i) ,width * cosf(2 * XM_PI / DIV * i),0 };
	}
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { 0,0,0 };
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { 0,0,-height };

	for (int i = 0; i < polygon.vertices.size(); i++)
	{
		polygon.vertices[i]->normal = {};

	}
	polygon.vertices[0]->uv = { 0.0f,0.0f }, polygon.vertices[1]->uv = { 1.0f,0.0f };
	polygon.vertices[2]->uv = { 0.0f,1.0f }, polygon.vertices[3]->uv = { 1.0f,1.0f };
	polygon.vertices[4]->uv = { 1.0f,1.0f };
	//�C���f�b�N�X
	//���
	polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(3));
	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(3));
	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(3));
	//����
	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(4));
	polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(4));
	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(4));

	CreateModel(polygon);

	return polygon;
}

Object::ObjectData Shape::CreateRect(const float width, const float height)
{
	Object::ObjectData polygon;
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2, -height / 2, 0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2, height / 2, 0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2, -height / 2,  0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2, height / 2, 0.0f };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };


	for (int i = 0; i < polygon.vertices.size(); i++)
	{
		polygon.vertices[i]->normal = {};
	}

	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(2));

	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(3));

	CreateModel(polygon);

	return polygon;
}

Object::ObjectData Shape::CreateCircle(const float r, const int num)
{
	Object::ObjectData polygon;
	for (int i = 0; i < num; i++)
	{
		polygon.vertices.push_back(new Object::Vertex);
		polygon.vertices[polygon.vertices.size() - 1]->pos.x = r * sinf(6.28f / num * i);
		polygon.vertices[polygon.vertices.size() - 1]->pos.y = r * cosf(6.28f / num * i);
		polygon.vertices[polygon.vertices.size() - 1]->pos.z = 0;
		polygon.vertices[polygon.vertices.size() - 1]->uv = { 0,0 };
	}

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { 0,0,0 };

	for (int i = 0; i < num; i++)
	{
		polygon.indices.push_back(new unsigned short(i));
		polygon.indices.push_back(new unsigned short(i + 1));
		polygon.indices.push_back(new unsigned short(num));
	}
	*polygon.indices[polygon.indices.size() - 2] = 0;

	CreateModel(polygon);

	return polygon;
}

Object::ObjectData Shape::CreateSquare(const float width, const float height, const float depth)
{
	Object::ObjectData polygon;
	//�O
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };

	//���
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };

	//��
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };


	//�E
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };


	//��
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,-height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };

	//��
	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { -width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 0.0f,0.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,1.0f };

	polygon.vertices.push_back(new Object::Vertex);
	polygon.vertices[polygon.vertices.size() - 1]->pos = { width / 2,height / 2,-depth / 2 };
	polygon.vertices[polygon.vertices.size() - 1]->uv = { 1.0f,0.0f };
	//�O
	polygon.indices.push_back(new unsigned short(0)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(2));
	polygon.indices.push_back(new unsigned short(2)), polygon.indices.push_back(new unsigned short(1)), polygon.indices.push_back(new unsigned short(3));
	//���
	polygon.indices.push_back(new unsigned short(5)), polygon.indices.push_back(new unsigned short(4)), polygon.indices.push_back(new unsigned short(6));
	polygon.indices.push_back(new unsigned short(5)), polygon.indices.push_back(new unsigned short(6)), polygon.indices.push_back(new unsigned short(7));
	//��
	polygon.indices.push_back(new unsigned short(8)), polygon.indices.push_back(new unsigned short(9)), polygon.indices.push_back(new unsigned short(10));
	polygon.indices.push_back(new unsigned short(10)), polygon.indices.push_back(new unsigned short(9)), polygon.indices.push_back(new unsigned short(11));
	//�E
	polygon.indices.push_back(new unsigned short(13)), polygon.indices.push_back(new unsigned short(12)), polygon.indices.push_back(new unsigned short(14));
	polygon.indices.push_back(new unsigned short(13)), polygon.indices.push_back(new unsigned short(14)), polygon.indices.push_back(new unsigned short(15));
	//��
	polygon.indices.push_back(new unsigned short(16)), polygon.indices.push_back(new unsigned short(17)), polygon.indices.push_back(new unsigned short(18));
	polygon.indices.push_back(new unsigned short(18)), polygon.indices.push_back(new unsigned short(17)), polygon.indices.push_back(new unsigned short(19));
	//��
	polygon.indices.push_back(new unsigned short(21)), polygon.indices.push_back(new unsigned short(20)), polygon.indices.push_back(new unsigned short(22));
	polygon.indices.push_back(new unsigned short(21)), polygon.indices.push_back(new unsigned short(22)), polygon.indices.push_back(new unsigned short(23));
	CreateModel(polygon);

	return polygon;
}

Object::ObjectData Shape::CreateCylinder(int division, int prizmHeight, int radius)
{
	Object::ObjectData polygon;

	HRESULT result = S_FALSE;

	std::vector<Object::Vertex> realVertices;
	// ���_���W�̌v�Z�i�d������j
	{
		realVertices.resize((division + 1) * 2);
		int index = 0;
		float zValue;

		// ���
		zValue = prizmHeight / 2.0f;
		for (int i = 0; i < division; i++)
		{
			Vec3 vertex;
			vertex.x = radius * sinf(XM_2PI / division * i);
			vertex.y = radius * cosf(XM_2PI / division * i);
			vertex.z = zValue;
			realVertices[index++].pos = vertex;
		}
		realVertices[index++].pos = Vec3(0, 0, zValue);	// ��ʂ̒��S�_
		// �V��
		zValue = -prizmHeight / 2.0f;
		for (int i = 0; i < division; i++)
		{
			Vec3 vertex;
			vertex.x = radius * sinf(XM_2PI / division * i);
			vertex.y = radius * cosf(XM_2PI / division * i);
			vertex.z = zValue;
			realVertices[index++].pos = vertex;
		}
		realVertices[index++].pos = Vec3(0, 0, zValue);	// �V�ʂ̒��S�_
	}
	// ���_���W�̌v�Z�i�d���Ȃ��j
	{
		// ���
		for (int i = 0; i < division; i++)
		{
			unsigned short index0 = i + 1;
			unsigned short index1 = i;
			unsigned short index2 = division;
			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index0].pos;
			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;
			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos; // ��ʂ̒��S�_
		}
		// ��ʂ̍Ō�̎O�p�`��1�Ԗڂ̃C���f�b�N�X��0�ɏ�������
		polygon.vertices[polygon.vertices.size() - 3]->pos = realVertices[0].pos;

		int topStart = division + 1;
		// �V��
		for (int i = 0; i < division; i++)
		{
			unsigned short index0 = topStart + i;
			unsigned short index1 = topStart + i + 1;
			unsigned short index2 = topStart + division;
			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index0].pos;
			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;
			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos; // �V�ʂ̒��S�_
		}
		// �V�ʂ̍Ō�̎O�p�`��1�Ԗڂ̃C���f�b�N�X��0�ɏ�������
		polygon.vertices[polygon.vertices.size() - 2]->pos = realVertices[topStart].pos;

		// ����
		for (int i = 0; i < division; i++)
		{
			unsigned short index0 = i + 1;
			unsigned short index1 = topStart + i + 1;
			unsigned short index2 = i;
			unsigned short index3 = topStart + i;

			if (i == division - 1)
			{
				index0 = 0;
				index1 = topStart;
			}
			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index0].pos;

			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;

			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos;

			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index2].pos;

			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index1].pos;

			polygon.vertices.push_back(new Object::Vertex);
			polygon.vertices[polygon.vertices.size() - 1]->pos = realVertices[index3].pos;
		}
	}
	int planeCount = division * 2 + division * 2;		// �ʂ̐�
	planeCount = planeCount * 3;
	// ���_�C���f�b�N�X�̐ݒ�
	{
		for (int i = 0; i < planeCount; i++)
		{
			polygon.indices.push_back(new unsigned short(i));
		}
	}
	CreateModel(polygon);
	return polygon;
}

void Shape::CreateModel(Object::ObjectData &polygon)
{
	HRESULT result = S_FALSE;
	for (size_t i = 0; i < polygon.indices.size() / 3; i++)
	{//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short indices0 = *polygon.indices[i * 3 + 0];
		unsigned short indices1 = *polygon.indices[i * 3 + 1];
		unsigned short indices2 = *polygon.indices[i * 3 + 2];
		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		XMVECTOR p0 = XMLoadFloat3(&polygon.vertices[indices0]->pos);
		XMVECTOR p1 = XMLoadFloat3(&polygon.vertices[indices1]->pos);
		XMVECTOR p2 = XMLoadFloat3(&polygon.vertices[indices2]->pos);
		//p0��p1�x�N�g���Ap0��p2�x�N�g�����v�Z�i�x�N�g���̌��Z�j
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);

		//�O�ς͗������琂���ȃx�N�g��
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//���K���i�������P�ɂ���j
		normal = XMVector3Normalize(normal);
		//���߂��@���𒸓_�f�[�^�ɑ��
		XMStoreFloat3(&polygon.vertices[indices0]->normal, normal);
		XMStoreFloat3(&polygon.vertices[indices1]->normal, normal);
		XMStoreFloat3(&polygon.vertices[indices2]->normal, normal);
	}

	//���_�f�[�^�S�̂̃T�C�Y�����_�f�[�^����̃T�C�Y�����_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(Object::Vertex) * polygon.vertices.size());

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

	Object::Vertex *vertMap = nullptr;
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
	polygon.vbView.StrideInBytes = sizeof(Object::Vertex);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	polygon.ibView.BufferLocation = polygon.indexBuff->GetGPUVirtualAddress();
	polygon.ibView.Format = DXGI_FORMAT_R16_UINT;
	polygon.ibView.SizeInBytes = sizeIB;
}

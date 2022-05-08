#pragma once
#include"Object.h"
/// <summary>
/// �}�`���f��
/// </summary>
class Shape
{
public:
	Shape();
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dev">�f�o�C�X</param>
	static void Init(ID3D12Device *dev);
public://�}�`���f��
	/// <summary>
	/// �O�p��
	/// </summary>
	/// <param name="width">���̒���</param>
	/// <param name="height">�c�̒���</param>
	/// <returns></returns>
	static Object::ObjectData CreateTriangularPyramid(const float width, const float height);
	/// <summary>
	/// �Z�`
	/// </summary>
	/// <param name="width">���̒���</param>
	/// <param name="height">�c�̒���</param>
	/// <returns></returns>
	static Object::ObjectData CreateRect(const float width, const float height);
	/// <summary>
	/// �~
	/// </summary>
	/// <param name="r">���a</param>
	/// <param name="num">������</param>
	/// <returns></returns>
	static Object::ObjectData CreateCircle(const float r, const int num);
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="width">���̒���</param>
	/// <param name="height">�c�̒���</param>
	/// <param name="depth">�[��</param>
	/// <returns></returns>
	static Object::ObjectData CreateSquare(const float width, const float height, const float depth);
	/// <summary>
	/// �~��
	/// </summary>
	/// <param name="division">������</param>
	/// <param name="prizmHeight">����</param>
	/// <param name="radius">��ʂ̔��a</param>
	/// <returns></returns>
	static Object::ObjectData CreateCylinder(int division, int prizmHeight, int radius);
public:
	static ID3D12Device *dev;					//�f�o�C�X

	static void CreateModel(Object::ObjectData &polygon);
};
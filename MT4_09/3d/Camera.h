#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include"Vec.h"
extern const int window_width;
extern const int window_height;

class Camera
{
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//�r���[�ϊ��s��
	XMMATRIX matView;
	//�ˉe�ϊ�
	XMMATRIX matProjection;

	Vec3 eye = {}, target = {}, up = {};
public:
	Camera();

	~Camera();

	/// <summary>
	/// �J��������
	/// </summary>
	/// <returns></returns>
	static Camera *Create();

	//�J����������/�J�����ʒueye/�J�����^�[�Q�b�gtarget /�J�����̌���up
	void Initilize(Vec3 eye, Vec3 target, Vec3 up);
	//�J�����ʒu�Z�b�g/�J�����ʒueye/�J�����^�[�Q�b�gtarget /�J�����̌���up
	void SetCamera(Vec3 eye, Vec3 target, Vec3 up);

	/// <summary>
	/// �J�������Ǐ]����
	/// </summary>
	/// <param name="position">�Ǐ]����I�u�W�F�N�g�̍��W</param>
	/// <param name="d">�I�u�W�F�N�g�ƃJ�����̋���</param>
	/// <param name="angleX">�J�����̌���X</param>
	/// <param name="angleY">�J�����̌���Y</param>
	/// <returns></returns>
	void FollowCamera(Vec3 position, Vec3 d, float angleX = 0, float angleY = 0);

	//matView���l��
	XMMATRIX GetMatView();
	//projection���l��
	XMMATRIX GetProjection();

	Vec3 GetEye();

	Vec3 GetTarget();

	Vec3 GetUp();
};
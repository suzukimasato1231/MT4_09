#include "Camera.h"
using namespace DirectX;

Camera::Camera()
{
	matView = XMMatrixIdentity();
	//�ˉe�ϊ�
	matProjection = XMMatrixIdentity();
}

Camera::~Camera()
{
}

Camera *Camera::Create()
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Camera *view = new Camera();
	if (view == nullptr) {
		return nullptr;
	}

	// ������
	return view;
}

void Camera::Initilize(Vec3 eye, Vec3 target, Vec3 up)
{
	//�ˉe�ϊ��p
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);
	this->eye = eye, this->target = target, this->up = up;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::SetCamera(Vec3 eye, Vec3 target, Vec3 up)
{
	this->eye = eye, this->target = target, this->up = up;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	//�ˉe�ϊ��p
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 5100.0f
	);
}

void Camera::FollowCamera(Vec3 position, Vec3 d, float angleX, float angleY)
{
	target = position;//�����_���W
   //�J�����Ǐ]
   //1
	Vec3 V0 = d;
	//2
	XMMATRIX  rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleX));//Y��
	rotM *= XMMatrixRotationX(XMConvertToRadians(angleY));//X��
	//3
	XMVECTOR v3 = { V0.x,V0.y,V0.z };
	XMVECTOR v = XMVector3TransformNormal(v3, rotM);

	//4
	Vec3 f3 = { v.m128_f32[0],v.m128_f32[1],v.m128_f32[2] };
	eye.x = target.x + f3.x, eye.y = target.y + f3.y, eye.z = target.z + f3.z;

	//5
	//�r���[�ϊ��s��
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

XMMATRIX Camera::GetMatView()
{
	return matView;
}

XMMATRIX Camera::GetProjection()
{
	return matProjection;
}

Vec3 Camera::GetEye()
{
	return eye;
}
Vec3 Camera::GetTarget()
{
	return target;
}

Vec3 Camera::GetUp()
{
	return up;
}

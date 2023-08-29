#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
	:GameObject(parent, "Controller")
{
	transform_.position_ = XMFLOAT3(7.0f, 0.0f, 7.0f);
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
}

//�X�V
void Controller::Update()
{
	//��]����
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2.0f;
	}
	if (Input::IsKey(DIK_UP)) {
		transform_.rotate_.x += 2.0f;
	}
	if (Input::IsKey(DIK_DOWN)) {
		transform_.rotate_.x -= 2.0f;
	}

	if (transform_.rotate_.x >= 60.0f) transform_.rotate_.x = 60.0f;
	if (transform_.rotate_.x <=  -25.0f) transform_.rotate_.x =  -25.0f;

	//���ݒn�����x�N�g���^�ɕϊ�
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	//transform_.rotate_.y�x��]������s��
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	//1�t���[��������̈ړ��ʁi�x�N�g���j
	XMVECTOR vMove = { 0.0f, 0.0f, 0.1f, 0.0f };     //��������0.1m

	//1�t���[��������̈ړ��ʁi�x�N�g���j
	XMVECTOR vSwipe = { 0.1f, 0.0f, 0.0f, 0.0f };     //��������0.1m

	//�ړ��x�N�g����ό`�i�����Ă�������j
	vMove = XMVector3TransformCoord(vMove, mRotY);
	vSwipe = XMVector3TransformCoord(vSwipe, mRotY);

	//�ړ�����
	if (Input::IsKey(DIK_W))
	{
		vPos += vMove;                              //�ړ�
		XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
	}
	if (Input::IsKey(DIK_S))
	{
		vPos -= vMove;                              //�ړ�
		XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
	}

	if (Input::IsKey(DIK_D))
	{
		vPos += vSwipe;                             //�ړ�
		XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
	}
	if (Input::IsKey(DIK_A))
	{
		vPos -= vSwipe;                             //�ړ�
		XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
	}

	XMFLOAT3 camTarget = { 0, 0, 0 };
	XMFLOAT3 camPos = { 0, 0, 0 };
	XMVECTOR vCam = { 0, 0, 0, 0 };
	XMVECTOR vTarget = { 0, 0, 0, 0 };

	camTarget = transform_.position_;
	vCam = { 0, 5, -10, 0 };
	vCam = XMVector3TransformCoord(vCam, mRotX);
	vCam = XMVector3TransformCoord(vCam, mRotY);
	XMStoreFloat3(&camPos, vPos + vCam);

	Camera::SetTarget(camTarget);
	Camera::SetPosition(camPos);
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}
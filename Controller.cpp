#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
	:GameObject(parent, "Controller")
{
	transform_.position_ = XMFLOAT3(7.0f, 0.0f, 7.0f);
	transform_.rotate_.x = 45.0f;
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
	InputRotate();

	//�ړ�����
	InputMove();

	//�J�����̐ݒ�
	SetCamera();
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}

void Controller::InputRotate()
{
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
		if (transform_.rotate_.x >= 89.0f) transform_.rotate_.x = 89.0f;
	}
	if (Input::IsKey(DIK_DOWN)) {
		transform_.rotate_.x -= 2.0f;
		if (transform_.rotate_.x <= 0.0f) transform_.rotate_.x = 0.0f;
	}
}

void Controller::InputMove()
{
	//1�t���[��������̈ړ��ʁi�x�N�g���j
	XMVECTOR vMoveFoward = { 0.0f, 0.0f, 0.1f, 0.0f };	//��������0.1m

	//1�t���[��������̈ړ��ʁi�x�N�g���j
	XMVECTOR vMoveRight = { 0.1f, 0.0f, 0.0f, 0.0f };	//��������0.1m

	//y���̉�]�s��
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//�ړ��x�N�g����ό`�i�����Ă�������j
	vMoveFoward = XMVector3TransformCoord(vMoveFoward, mRotY);
	vMoveRight = XMVector3TransformCoord(vMoveRight, mRotY);

	//���ݒn�����x�N�g���^�ɕϊ�
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	if (Input::IsKey(DIK_W))		//�O
	{
		vPos += vMoveFoward;						//�ړ�
		XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
	}
	if (Input::IsKey(DIK_S))		//���
	{
		vPos -= vMoveFoward;						//�ړ�
		XMStoreFloat3(&transform_.position_, vPos);	//���݈ʒu�̍X�V
	}

	if (Input::IsKey(DIK_D))		//�E
	{
		vPos += vMoveRight;							//�ړ�
		XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
	}
	if (Input::IsKey(DIK_A))		//��
	{
		vPos -= vMoveRight;							//�ړ�
		XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
	}
}

void Controller::SetCamera()
{
	XMVECTOR vCam = { 0, 0, 0, 0 };		//�J�����̈ʒu�x�N�g��
	XMVECTOR vTarget = { 0, 0, 0, 0 };	//�J�����̏œ_�x�N�g��

	//��]��\���s��
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	vCam = { 0, 0, -10, 0 };
	vCam = XMVector3TransformCoord(vCam, mRotX);
	vCam = XMVector3TransformCoord(vCam, mRotY);

	//���ݒn�����x�N�g���^�ɕϊ�
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	//�J������ݒ�
	Camera::SetTarget(transform_.position_);
	Camera::SetPosition(vPos + vCam);
}
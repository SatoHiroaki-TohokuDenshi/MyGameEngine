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

	//�㉺�̊p�x�̐���
	if (transform_.rotate_.x >= 60.0f) transform_.rotate_.x = 60.0f;
	if (transform_.rotate_.x <=  -25.0f) transform_.rotate_.x =  -25.0f;

	//���ݒn�����x�N�g���^�ɕϊ�
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	//��]��\���s��
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	//1�t���[��������̈ړ��ʁi�x�N�g���j
	XMVECTOR vMoveFoward = { 0.0f, 0.0f, 0.1f, 0.0f };	//��������0.1m

	//1�t���[��������̈ړ��ʁi�x�N�g���j
	XMVECTOR vMoveRight = { 0.1f, 0.0f, 0.0f, 0.0f };	//��������0.1m

	//�ړ��x�N�g����ό`�i�����Ă�������j
	vMoveFoward = XMVector3TransformCoord(vMoveFoward, mRotY);
	vMoveRight = XMVector3TransformCoord(vMoveRight, mRotY);

	//�ړ�����
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

	XMVECTOR vCam = { 0, 0, 0, 0 };		//�J�����̈ʒu�x�N�g��
	XMVECTOR vTarget = { 0, 0, 0, 0 };	//�J�����̏œ_�x�N�g��

	vCam = { 0, 5, -10, 0 };
	vCam = XMVector3TransformCoord(vCam, mRotX);
	vCam = XMVector3TransformCoord(vCam, mRotY);

	//�J������ݒ�
	Camera::SetTarget(transform_.position_);
	Camera::SetPosition(vPos + vCam);
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}
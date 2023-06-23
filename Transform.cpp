#include "Transform.h"

//�R���X�g���N�^
Transform::Transform() :
	matTranslate_(XMMatrixIdentity()), matRotate_(XMMatrixIdentity()), matScale_(XMMatrixIdentity()),
	position_(0.0f, 0.0f, 0.0f), rotate_(0.0f, 0.0f, 0.0f), scale_(1.0f, 1.0f, 1.0f)
{
}

//�f�X�g���N�^
Transform::~Transform() {

}

//�e�s��̌v�Z
void Transform::Calclation() {
	//�ړ��s��
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
	//��]�s��
	matRotate_ = XMMatrixRotationZ(rotate_.z) * XMMatrixRotationX(rotate_.x) * XMMatrixRotationY(rotate_.y);
	//�g��k���s��
	matScale_ = XMMatrixScaling(rotate_.x, rotate_.y, rotate_.z);
}

//���[���h�s����擾
XMMATRIX Transform::GetWorldMatrix() {
	return matScale_ * matRotate_ * matTranslate_;
}

//�@���ό`�p�s����擾
XMMATRIX Transform::GetNormalMatrix() {
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
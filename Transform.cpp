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
	
}

//���[���h�s����擾
XMMATRIX Transform::GetWorldMatrix() {
	return ;
}
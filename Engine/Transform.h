#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
class Transform {
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��

public:
	XMFLOAT3 position_;	//�ʒu
	XMFLOAT3 rotate_;	//����
	XMFLOAT3 scale_;	//�g�嗦

	Transform* pParent_;//�e�I�u�W�F�N�g��Transform

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	void Calclation();

	//���[���h�s����擾
	XMMATRIX GetWorldMatrix();

	//�@���ό`�p�s����擾
	XMMATRIX GetNormalMatrix();

	//�e�I�u�W�F�N�g�̓o�^
	void SetParentTransform(Transform* p) { pParent_ = p; };
};

//-------------------------------------
//DirectX�̕ϐ��i�\���́j�v�Z�p�̉��Z�q
//-------------------------------------

//XMFLOAT3���m�̉��Z
inline XMFLOAT3 operator +(const XMFLOAT3& f1, const XMFLOAT3& f2) {
	return XMFLOAT3(f1.x + f2.x, f1.y + f2.y, f1.z + f2.z);
};
//XMFLOAT3���m�̌��Z
inline XMFLOAT3 operator -(const XMFLOAT3& f1, const XMFLOAT3& f2) {
	return XMFLOAT3(f1.x - f2.x, f1.y - f2.y, f1.z - f2.z);
};

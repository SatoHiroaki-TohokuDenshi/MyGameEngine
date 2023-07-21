#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize() {
	hModel_ = Model::Load("Assets/Oden_2.fbx");
	assert(hModel_ >= 0);

	transform_.position_.z = 20.0f;
	transform_.rotate_.z = 180.0f;

	SphereCollider* col = new SphereCollider();
	AddCollider(col);
}

//�X�V
void Enemy::Update() {
	transform_.rotate_.y++;
}

//�`��
void Enemy::Draw() {
	Model::SetTransform(hModel_, this->transform_);
	Model::Draw(hModel_);
}

//�J��
void Enemy::Release() {
}
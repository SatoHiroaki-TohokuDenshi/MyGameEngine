#include "MiniPlayer.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//�R���X�g���N�^
MiniPlayer::MiniPlayer(GameObject* parent)
	:GameObject(parent, "MiniPlayer"), hModel_(-1)
{
}

//�f�X�g���N�^
MiniPlayer::~MiniPlayer()
{
}

//������
void MiniPlayer::Initialize() {
	hModel_ = Model::Load("Assets/Oden_2.fbx");
	assert(hModel_ >= 0);

	this->transform_.scale_ = XMFLOAT3(0.3f, 0.3f, 0.3f);
}

//�X�V
void MiniPlayer::Update() {
	transform_.rotate_.y++;
	transform_.position_.z += 0.5f;

	if (transform_.position_.z >= 50.0f)
		KillMe();
}

//�`��
void MiniPlayer::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void MiniPlayer::Release() {
}
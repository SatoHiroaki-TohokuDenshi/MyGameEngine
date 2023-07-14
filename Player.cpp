#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "MiniPlayer.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize() {
	hModel_ = Model::Load("Assets/Oden_2.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Player::Update() {
	transform_.rotate_.y++;

	if (Input::IsKey(DIK_LEFT))		transform_.position_.x -= 0.1f;
	if (Input::IsKey(DIK_RIGHT))	transform_.position_.x += 0.1f;

	if (Input::IsKeyDown(DIK_SPACE)) {
		Instantiate<MiniPlayer>(this->pParent_)->SetPosition(this->transform_.position_);
	}
}

//�`��
void Player::Draw() {
	Model::SetTransform(hModel_, this->transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release() {
}
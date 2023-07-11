#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"
#include "MiniPlayer.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize() {
	pFbx = new Fbx();
	pFbx->Load("Assets/Oden_2.fbx");
	this->transform_.rotate_.z = 38.0f;
	Instantiate< MiniPlayer>(this);
}

//�X�V
void Player::Update() {
	transform_.rotate_.y += 1.0f;
	if (Input::IsKeyDown(DIK_A)) {
		this->KillMe();
	}
}

//�`��
void Player::Draw() {
	pFbx->Draw(this->transform_);
}

//�J��
void Player::Release() {
	pFbx->Release();
	delete pFbx;
}
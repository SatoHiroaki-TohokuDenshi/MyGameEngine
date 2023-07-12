#include "MiniPlayer.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

//�R���X�g���N�^
MiniPlayer::MiniPlayer(GameObject* parent)
	:GameObject(parent, "MiniPlayer"), pFbx(nullptr)
{
}

//�f�X�g���N�^
MiniPlayer::~MiniPlayer()
{
}

//������
void MiniPlayer::Initialize() {
	pFbx = new Fbx();
	pFbx->Load("Assets/Oden_2.fbx");
	transform_.position_.x = 3.0f;
	this->transform_.scale_ = XMFLOAT3(0.3f, 0.3f, 0.3f);
}

//�X�V
void MiniPlayer::Update() {
	//transform_.rotate_.x += rand() % 60;
	//transform_.rotate_.y += rand() % 60;
	//transform_.rotate_.z += rand() % 60;

	if (Input::IsKeyDown(DIK_D))	KillMe();
}

//�`��
void MiniPlayer::Draw() {
	pFbx->Draw(this->transform_);
}

//�J��
void MiniPlayer::Release() {
	//pFbx->Release();
	//delete pFbx;
}
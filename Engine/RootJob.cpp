#include "RootJob.h"
#include "../PlayScene.h"

RootJob::RootJob() :
	GameObject()
{
}

RootJob::~RootJob() {
}

//������
void RootJob::Initialize() {
	Instantiate<PlayScene>(this);
}

//�X�V
void RootJob::Update() {
}

//�`��
void RootJob::Draw() {
}

//���
void RootJob::Release() {
}

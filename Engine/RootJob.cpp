#include "RootJob.h"
#include "SceneManager.h"

RootJob::RootJob(GameObject* parent) :
	GameObject(parent, "RootJob")
{
}

RootJob::~RootJob() {
}

//������
void RootJob::Initialize() {
	Instantiate<SceneManager>(this);
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

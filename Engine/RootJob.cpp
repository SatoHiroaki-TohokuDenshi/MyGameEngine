#include "RootJob.h"
#include "SceneManager.h"

RootJob::RootJob(GameObject* parent) :
	GameObject(parent, "RootJob")
{
}

RootJob::~RootJob() {
}

//初期化
void RootJob::Initialize() {
	Instantiate<SceneManager>(this);
}

//更新
void RootJob::Update() {
}

//描画
void RootJob::Draw() {
}

//解放
void RootJob::Release() {
}

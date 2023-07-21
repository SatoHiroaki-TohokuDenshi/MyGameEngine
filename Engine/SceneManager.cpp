#include "SceneManager.h"
#include "Model.h"
#include "SafetyMacro.h"
#include "../TestScene.h"
#include "../PlayScene.h"

SceneManager::SceneManager(GameObject* parent) :
	GameObject(parent, "SceneManager"), 
	currentSceneID_(SCENE_ID_TEST), nextSceneID(SCENE_ID_TEST)
{
}

SceneManager::~SceneManager() {
}

void SceneManager::Initialize() {
	currentSceneID_ = SCENE_ID_PLAY;
	nextSceneID = currentSceneID_;
	Instantiate<PlayScene>(this);
}

void SceneManager::Update() {
	//���݂̃V�[��ID�Ǝ��̃V�[��ID���قȂ�ꍇ�؂�ւ���
	if (currentSceneID_ != nextSceneID) {
		//���݂̃V�[�����폜
		DeleteScene();

		//���̃V�[���̏���
		switch (nextSceneID) {
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		}
		currentSceneID_ = nextSceneID;
	}

}

void SceneManager::Draw() {
}

void SceneManager::Release() {
}

/// <summary>�V�[����؂�ւ���</summary>
/// <param name="next">���̃V�[��ID</param>
void SceneManager::ChangeScene(SCENE_ID next) {
	nextSceneID = next;
}

void SceneManager::DeleteScene() {
	//���݂̃V�[���̌�Еt��
	auto scene = childList_.begin();
	(*scene)->ReleaseSub();
	SAFE_DELETE(*scene);
	childList_.clear();

	//���[�h�����f�[�^�̍폜
	Model::Release();
}
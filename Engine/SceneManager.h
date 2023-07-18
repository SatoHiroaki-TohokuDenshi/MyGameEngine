#pragma once
#include "GameObject.h"

//�V�[����񋓂���
enum SCENE_ID {
	SCENE_ID_TEST = 0,
	SCENE_ID_PLAY,
};

class SceneManager : public GameObject {
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID;
public:
	SceneManager(GameObject* parent);
	~SceneManager();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//�V�[����؂�ւ���
	void ChangeScene(SCENE_ID next);
};
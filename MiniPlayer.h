#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

//MiniPlayer���Ǘ�����N���X
class MiniPlayer : public GameObject
{
private:
    Fbx* pFbx;
public:
    //�R���X�g���N�^
    MiniPlayer(GameObject* parent);

    //�f�X�g���N�^
    ~MiniPlayer();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
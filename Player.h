#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

//Player���Ǘ�����N���X
class Player : public GameObject
{
private:
    Fbx* pFbx;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
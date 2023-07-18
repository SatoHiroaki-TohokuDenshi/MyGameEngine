#pragma once

#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;

class GameObject {
protected:
	list<GameObject*>	childList_;		//�����̎q���̃|�C���^�̃��X�g
	Transform			transform_;		//�����̈ʒu�A�����A�g�嗦
	GameObject*			pParent_;		//�����̐e�̃|�C���^
	string				objectName_;	//�����̖��O

public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	~GameObject();

	//�C���^�[�t�F�[�X�p�������z�֐�//
	//�ȉ���4�̊֐��͕K���I�[�o�[���C�h���邱��

	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Draw() = 0;
	//���
	virtual void Release() = 0;

	//Initialize�ȊO�̊֐����ċA�I�ɌĂяo���֐��Q
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	//�A�N�Z�X�֐�
	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; };
	void SetRotate(XMFLOAT3 rot) { transform_.rotate_ = rot; };
	void SetScale(XMFLOAT3 scl) { transform_.scale_ = scl; };

	//�I�u�W�F�N�g�̏�������
	bool isDead_;		//�t���O
	void KillMe();		//�t���O�𗧂Ă�
	void DeleteObject();//�I�u�W�F�N�g������

	//�I�u�W�F�N�g�̌���
	GameObject* FindChildObject(string objName);

	//�������p�N���X�e���v���[�g
	template <class T>
	GameObject* Instantiate(GameObject* parent) {
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
		return p;
	}
};
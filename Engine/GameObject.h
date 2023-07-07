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
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	template <class T>
	void Instantiate(GameObject* parent) {
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
	}
};
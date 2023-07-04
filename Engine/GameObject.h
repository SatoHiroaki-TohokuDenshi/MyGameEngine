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

	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Draw() = 0;
	//���
	virtual void Release() = 0;

	template <class T>
	void Instantiate(GameObject* parent) {
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
	}
};
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

	//�q����Update�֐����ċA�I�ɌĂяo��
	void UpdateSub();
	//�q����Draw�֐����ċA�I�ɌĂяo��
	void DrawSub();
	//�q����Release�֐����ċA�I�ɌĂяo��
	void ReleaseSub();

	//�A�N�Z�X�֐�//
	//�ʒu�̎擾
	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; };
	//��]�̎擾
	void SetRotate(XMFLOAT3 rot) { transform_.rotate_ = rot; };
	//�g�嗦�̎擾
	void SetScale(XMFLOAT3 scl) { transform_.scale_ = scl; };

	//�I�u�W�F�N�g�̏�������//
	bool isDead_;		//�t���O
	void KillMe();		//�t���O�𗧂Ă�
	void DeleteObject();//�I�u�W�F�N�g������

	//�q���̌���
	//�����F�I�u�W�F�N�g�̖��O
	//�ߒl�FGameObject�^�̃|�C���^�@������Ȃ��ꍇ��nullptr
	GameObject* FindChildObject(string objName);

	//�I�u�W�F�N�g�̌���
	//�����F�T�������I�u�W�F�N�g�̖��O
	//�ߒl�FRootJob�̃|�C���^
	GameObject* GetRootJob();

	//�I�u�W�F�N�g�̌���
	//�����F�T�������I�u�W�F�N�g�̖��O
	//�ߒl�FGameObject�^�̃|�C���^�@������Ȃ��ꍇ��nullptr
	GameObject* FindObject(string objName);

public:
	/// <summary>�������p�e���v���[�g</summary>
	/// <typeparam name="T">����������N���X</typeparam>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>�쐬���ꂽ�I�u�W�F�N�g�̃|�C���^</returns>
	template <class T>
	GameObject* Instantiate(GameObject* parent) {
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
		return p;
	}
};
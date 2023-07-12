#include "GameObject.h"
#include "SafetyMacro.h"

GameObject::GameObject() :
	transform_(Transform()),
	pParent_(nullptr), objectName_(""), isDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	transform_(Transform()),
	pParent_(parent), objectName_(name), isDead_(false)
{
	if (pParent_ != nullptr)
		this->transform_.SetParentTransform(&parent->transform_);
}

GameObject::~GameObject() {

}

void GameObject::DrawSub() {
	//������Draw���Ăяo��
	Draw();
	//�q����DrawSub���Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::UpdateSub() {
	//������Update���Ăяo��
	Update();
	//�q����UpdateSub���Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
	}

	//�I�u�W�F�N�g�̏���
	DeleteObject();
}

void GameObject::ReleaseSub() {
	//�q����ReleaseSub���Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
	//������Release���Ăяo��
	Release();
}

void GameObject::KillMe() {
	this->isDead_ = true;
}

void GameObject::DeleteObject() {
	//�I�u�W�F�N�g�̏���
	for (auto itr = childList_.begin(); itr != childList_.end();) {
		//�����t���O�������Ă���ꍇ
		if ((*itr)->isDead_) {
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		//�����Ă��Ȃ��Ȃ玟�𑖍�
		else
			itr++;
	}
}
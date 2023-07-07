#include "GameObject.h"

GameObject::GameObject() :
	transform_(Transform()),
	pParent_(nullptr), objectName_("")
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	transform_(Transform()),
	pParent_(parent), objectName_(name)
{
}

GameObject::~GameObject() {

}

void GameObject::DrawSub() {
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		//������Draw���Ăяo��
		(*itr)->Draw();
		//�q����DrawSub���Ă�
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub() {
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		//������Update���Ăяo��
		(*itr)->Update();
		//�q����UpdateSub���Ă�
		(*itr)->UpdateSub();
	}
}

void GameObject::ReleaseSub() {
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		//������Release���Ăяo��
		(*itr)->Release();
		//�q����ReleaseSub���Ă�
		(*itr)->ReleaseSub();
	}
}
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
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->UpdateSub();
}

void GameObject::ReleaseSub() {
	//������Release���Ăяo��
	Release();
	//�q����ReleaseSub���Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->ReleaseSub();
}
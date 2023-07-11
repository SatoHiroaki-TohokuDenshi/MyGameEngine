#include "GameObject.h"
#include "SafetyMacro.h"

GameObject::GameObject() :
	transform_(Transform()),
	pParent_(nullptr), objectName_(""), isDead(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	transform_(Transform()),
	pParent_(parent), objectName_(name), isDead(false)
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
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
		if ((*itr)->isDead) {
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
	}
}

void GameObject::ReleaseSub() {
	//������Release���Ăяo��
	Release();
	//�q����ReleaseSub���Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->ReleaseSub();
}

void GameObject::KillMe() {
	this->isDead = true;
}

void GameObject::DeleteObject() {
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
		delete* itr;
		childList_.erase(itr);
	}
}
#include "GameObject.h"
#include "SafetyMacro.h"
#include "SphereCollider.h"

GameObject::GameObject() :
	transform_(Transform()),
	pParent_(nullptr), objectName_(""), isDead_(false), pCollider_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	transform_(Transform()),
	pParent_(parent), objectName_(name), isDead_(false), pCollider_(nullptr)
{
	if (pParent_ != nullptr)
		this->transform_.SetParentTransform(&parent->transform_);
}

GameObject::~GameObject() {
}

void GameObject::UpdateSub() {
	//������Update���Ăяo��
	Update();

	RoundRobin(GetRootJob());
	//�q����UpdateSub���Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
	}

	//�I�u�W�F�N�g�̏���
	DeleteObject();
}

void GameObject::DrawSub() {
	//������Draw���Ăяo��
	Draw();
	//�q����DrawSub���Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
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

GameObject* GameObject::FindChildObject(string objName) {
	//�����̖��O�������玩���̃A�h���X��Ԃ�
	if (objName == this->objectName_) {
		return this;
	}
	else {
		for (auto &itr : childList_) {
			GameObject* obj = itr->FindChildObject(objName);
			if (obj != nullptr)
				return obj;
		}
	}

	//������Ȃ������ꍇ
	return nullptr;
}

GameObject* GameObject::GetRootJob() {
	//���g��RootJob�̏ꍇ
	if (pParent_ == nullptr)
		return this;

	//�e��GetRootJob�Őe�ɂ��Č���
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string objName) {
	return GetRootJob()->FindChildObject(objName);
}

void GameObject::AddCollider(SphereCollider* pCollider) {
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget) {
	//����ɔ��肪�Ȃ����ߏI��
	if (pTarget->pCollider_ == nullptr) return;
	//����������Ȃ�X�L�b�v
	if (pTarget == this) return;

	float dist = (
		(this->transform_.position_.x - pTarget->transform_.position_.x) * (this->transform_.position_.x - pTarget->transform_.position_.x) +
		(this->transform_.position_.y - pTarget->transform_.position_.y) * (this->transform_.position_.y - pTarget->transform_.position_.y) +
		(this->transform_.position_.z - pTarget->transform_.position_.z) * (this->transform_.position_.z - pTarget->transform_.position_.z)
		);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());
	if (dist <= rDist) {
		int n = 0;
	}
}

void GameObject::RoundRobin(GameObject* pTarget) {
	//����������������Ă��Ȃ��Ȃ�X�L�b�v
	if (this->pCollider_ == nullptr) return;
	if (pTarget->pCollider_ != nullptr)
		Collision(pTarget);

	for (auto itr : pTarget->childList_)
		RoundRobin(itr);
}

#pragma once

class SphereCollider {
	float radius_;		//���a
public:
	SphereCollider();
	SphereCollider(float r);
	~SphereCollider();
	float GetRadius() { return radius_; };
};
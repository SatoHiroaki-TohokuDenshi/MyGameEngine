#pragma once
#include <string>
#include <cassert>
#include "Fbx.h"
#include "Transform.h"

using std::string;

namespace Model {
	//�t�@�C���̓ǂݍ���
	int Load(string fileName);
	//�ʒu����ݒ�
	void SetTransform(int hModel, Transform t);
	//�`��
	void Draw(int hModel);

	void Release();

	void RayCast(int hModel, RayCastData& data);
}
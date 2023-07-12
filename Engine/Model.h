#pragma once
#include <string>
#include <vector>

//�O���錾
class Transform;
class Fbx;

using std::string;
using std::vector;

namespace Model {
	//�f�[�^���i�[����\����
	struct ModelData {
		Fbx* pFbx_;				//FBX�̃A�h���X
		Transform transform_;	//Transform�̏��
		string fileName_;		//�t�@�C���̖��O
	};

	vector<ModelData> data_;

	//�t�@�C���̓ǂݍ���
	int Load(string fileName);
	//�ʒu����ݒ�
	void SetTransform(int hModel, Transform t);
	//�`��
	void Draw(int hModel);
}
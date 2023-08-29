#pragma once
#include <vector>
#include "Engine/GameObject.h"

using std::vector;

//Stage���Ǘ�����N���X
class Stage : public GameObject
{
private:
	enum BOX_TYPE {
		BOX_DEFAULT = 0,
		BOX_BRICK,
		BOX_GRASS,
		BOX_SAND,
		BOX_WATER,
		BOX_MAX,
	};
	const int sizeX = 15;
	const int sizeZ = 15;
	
	vector<int> hModel_;		//���f���ԍ�
	vector<vector<int>> table_;	//�\�����e
public:
	//�R���X�g���N�^
	Stage(GameObject* parent);

	//�f�X�g���N�^
	~Stage();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
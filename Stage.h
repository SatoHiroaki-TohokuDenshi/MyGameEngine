#pragma once

#include <vector>
#include <windows.h>
#include "Engine/GameObject.h"

using std::vector;

namespace {
	//�u���b�N�̎��
	enum BOX_TYPE {
		BOX_DEFAULT = 0,		//�ʏ�
		BOX_BRICK,				//��
		BOX_GRASS,				//��
		BOX_SAND,				//��
		BOX_WATER,				//��
		BOX_MAX,				//�ő�l
	};
	const int sizeX = 15;		//x���W�̍ő�l
	const int sizeZ = 15;		//z���W�̍ő�l

	//�ҏW���[�h
	enum MODE {
		MODE_UP = 0,			//�グ��
		MODE_DOWN,				//������
		MODE_CHANGE,			//�ς���
	};
}

//Stage���Ǘ�����N���X
class Stage : public GameObject
{
private:
	struct {
		BOX_TYPE type_;
		int height_;
	} table_[sizeX][sizeZ];		//�f�[�^���i�[����2�����z��

	struct {
		int x_;
		int z_;
		float dist_;
	} selectBlock_;				//�I�񂾃u���b�N�̏���ێ�����ϐ�
	
	vector<int> hModel_;		//���f���ԍ�

	int mode_;		//0:�グ��  1:������  2:�ς���
	int select_;	//���

public:	//�I�[�o�[���C�h�֐�
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

public:
	void SetBlock(int _x, int _z, BOX_TYPE _type);
	void SetBlockHeight(int _x, int _z, int _height);

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
	void NewStage();
	void LoadStage();
	void SaveStage();

private:
	void CalcChoiceBlock();
};
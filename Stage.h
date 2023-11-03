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


	//�ҏW���[�h
	enum MODE {
		MODE_UP = 0,			//�グ��
		MODE_DOWN,				//������
		MODE_CHANGE,			//�ς���
	};

	//�u���V�̑傫��
	enum BRUSH_SIZE {
		BRUSH_SMALL = 0,		//��
		BRUSH_MEDIUM,			//��
		BRUSH_LARGE,			//��
	};
}

const int sizeX = 15;		//x���W�̍ő�l
const int sizeZ = 15;		//z���W�̍ő�l

const int brushS = 1;
const int brushM = 3;
const int brushL = 5;

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
	int brushSize_;	//�u���V�̑傫��

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
	//�Z�b�^�[�֐�
	void SetBlock(int _x, int _z, BOX_TYPE _type);
	void SetBlockHeight(int _x, int _z, int _height);

	//�Q�b�^�[�֐�
	int GetBlockHeight(int x, int z);
	int GetBlockType(int x, int z);

	//�_�C�A���O�v���V�[�W���\
	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	//�Z�[�u�E���[�h
	void NewStage();
	void LoadStage();
	void SaveStage();

private:
	void CalcChoiceBlock();
	void MoveUpBlock();
	void MoveDownBlock();
	void ChangeBlock();
};
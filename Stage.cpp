#include "Stage.h"
#include <string>
#include "Engine/Direct3D.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"

using std::string;

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), mode_(0), select_(0)
{
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			table_[x][z].type_ = (BOX_TYPE)(x % BOX_TYPE::BOX_MAX);
			table_[x][z].height_ = 1;
		}
	}
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
	string modelName[] = {
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};

	//���f���f�[�^�̃��[�h
	for (int i = 0; i < BOX_TYPE::BOX_MAX; i++) {
		hModel_.push_back(Model::Load("assets/" + modelName[i]));
		assert(hModel_.at(i) >= 0);
	}
}

//�X�V
void Stage::Update()
{
	float w = (float)Direct3D::scrWidth_ / 2.0f;
	float h = (float)Direct3D::scrHeight_ / 2.0f;
	float offsetX = 0.0f, offsetY = 0.0f;
	float maxZ = 1.0f, minZ = 0.0f;
	XMMATRIX vp = {
		w			, 0.0f			, 0.0f			, 0.0f,
		0.0f		, -h			, 0.0f			, 0.0f,
		0.0f		, 0.0f			, maxZ - minZ	, 0.0f,
		offsetX + w	, offsetY + h	, minZ			, 1.0f
	};

	//�t�s����擾
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
	XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	XMVECTOR mouseVecFront = XMLoadFloat3(&mousePosFront);
	mouseVecFront = XMVector3TransformCoord(mouseVecFront, invVP);
	mouseVecFront = XMVector3TransformCoord(mouseVecFront, invProj);
	mouseVecFront = XMVector3TransformCoord(mouseVecFront, invView);
	XMVECTOR mouseVecBack = XMLoadFloat3(&mousePosBack);
	mouseVecBack = XMVector3TransformCoord(mouseVecBack, invVP);
	mouseVecBack = XMVector3TransformCoord(mouseVecBack, invProj);
	mouseVecBack = XMVector3TransformCoord(mouseVecBack, invView);
}

//�`��
void Stage::Draw()
{
	//Stage�I�u�W�F�N�g�����炳���ɁA�X�e�[�W��z�u���邽�߂̕ϐ�
	Transform blockTrans;
	//�\�����郂�f�����Ǘ�����ϐ�
	int type = 0;
	int height = 1;

	for (int x = 0; x < sizeX; x++)
	{
		for (int z = 0; z < sizeZ; z++)
		{
			blockTrans.position_.x = (float)x;
			blockTrans.position_.z = (float)z;

			type = table_[x][z].type_;
			height = table_[x][z].height_;

			for (int h = 0; h < height; h++) {
				blockTrans.position_.y = (float)h;
				Model::SetTransform(hModel_.at(type), blockTrans);
				Model::Draw(hModel_.at(type));
			}
		}
	}
}

//�J��
void Stage::Release()
{
}

void Stage::SetBlock(int _x, int _z, BOX_TYPE _type)
{
	if (_type >= BOX_TYPE::BOX_MAX)		return;
	table_[_x][_z].type_ = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
	if (_height >= 6) return;
	table_[_x][_z].height_ = _height;
}

//�_�C�A���O�̃E�B���h�E�v���V�[�W��
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp){
	switch (msg) {
	case WM_INITDIALOG:		//������
		//���W�I�{�^��
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		//�R���{�{�b�N�X
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}
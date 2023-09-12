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

	selectBlock_.x_ = 0;
	selectBlock_.z_ = 0;
	selectBlock_.dist_ = -1.0f;
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
	if (!Input::IsMouseButtonDown(0))	return;

	CalcChoiceBlock();
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

void Stage::CalcChoiceBlock() {
	float w = (float)(Direct3D::scrWidth_ / 2.0f);
	float h = (float)(Direct3D::scrHeight_ / 2.0f);
	XMMATRIX vp = {
		w	, 0.0f	, 0.0f	, 0.0f,
		0.0f, -h	, 0.0f	, 0.0f,
		0.0f, 0.0f	, 1.0f	, 0.0f,
		w	, h		, 0.0f	, 1.0f
	};

	//�t�s����擾
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);								//�r���[�|�[�g�ϊ�
	XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());	//�v���W�F�N�V�����ϊ�
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());		//�r���[�ϊ�

	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//3D��Ԃɋt�v�Z
	XMVECTOR mouseVecFront = XMLoadFloat3(&mousePosFront);
	mouseVecFront = XMVector3TransformCoord(mouseVecFront, invVP * invProj * invView);
	//XMVECTOR camPos = XMVector3TransformCoord(Camera::GetCameraPosition(), invVP * invProj * invView);

	XMVECTOR mouseVecBack = XMLoadFloat3(&mousePosBack);
	mouseVecBack = XMVector3TransformCoord(mouseVecBack, invVP * invProj * invView);

	//�I���u���b�N�̏�����
	selectBlock_.x_ = 0;
	selectBlock_.z_ = 0;
	selectBlock_.dist_ = -1.0f;

	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			for (int y = 0; y < table_[x][z].height_ + 1; y++) {
				RayCastData data;
				XMStoreFloat4(&data.start, mouseVecFront);
				XMStoreFloat4(&data.dir, mouseVecBack - mouseVecFront);

				Transform trans;
				trans.position_ = XMFLOAT3((float)x, (float)y, (float)z);
				Model::SetTransform(hModel_.at(0), trans);

				Model::RayCast(hModel_.at(0), data);

				if (data.hit) {
					//���߂Ă̏ꍇ
					if (selectBlock_.dist_ <= 0.0f) {
						selectBlock_.x_ = x;
						selectBlock_.z_ = z;
						selectBlock_.dist_ = data.dist;
					}
					//����ȊO
					else if (selectBlock_.dist_ >= data.dist) {
						selectBlock_.x_ = x;
						selectBlock_.z_ = z;
						selectBlock_.dist_ = data.dist;
					}
					break;
				}
			}
		}
	}

	if (selectBlock_.dist_ <= 0.0f) return;
	table_[selectBlock_.x_][selectBlock_.z_].height_++;
}
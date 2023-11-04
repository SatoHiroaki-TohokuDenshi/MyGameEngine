#include "Stage.h"
#include <string>
#include "Engine/Direct3D.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"

#include <Windows.h>
#include <filesystem>

#include "CommandManager.h"
#include "CommandUp.h"
#include "CommandDown.h"
#include "CommandChange.h"

using std::string;

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), mode_(0), select_(0), brushSize_(brushS)
{
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			table_[x][z].type_ = (BOX_TYPE)(x % BOX_TYPE::BOX_MAX);
			table_[x][z].height_ = 0;
		}
	}

	selectBlock_.x_ = 0;
	selectBlock_.z_ = 0;
	selectBlock_.dist_ = -1.0f;

	pManager_ = new CommandManager();
}

//�f�X�g���N�^
Stage::~Stage()
{
	delete pManager_;
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
	//�����I�΂�Ă��Ȃ��Ȃ璆�~
	if (selectBlock_.dist_ <= 0.0f)		return;

	switch (mode_) {
	case MODE::MODE_UP:
		pManager_->RecordCommand(new CommandUp(selectBlock_.x_, selectBlock_.z_, brushSize_));
		MoveUpBlock();
		break;
	case MODE::MODE_DOWN:
		pManager_->RecordCommand(new CommandDown(selectBlock_.x_, selectBlock_.z_, brushSize_));
		MoveDownBlock();
		break;
	case MODE::MODE_CHANGE:
		pManager_->RecordCommand(new CommandChange(selectBlock_.x_, selectBlock_.z_, brushSize_, (BOX_TYPE)select_, this));
		ChangeBlock();
		break;
	default:
		break;
	}
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

			for (int h = 0; h < height + 1; h++) {
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
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_SETCURSEL, 0, 0);

		//�T�C�Y
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_ADDSTRING, 0, (LPARAM)"1");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_ADDSTRING, 0, (LPARAM)"3");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_ADDSTRING, 0, (LPARAM)"5");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_SETCURSEL, 0, 0);

		return TRUE;

	case WM_COMMAND:		//�_�C�A���O�I��
		WORD id;
		id = LOWORD(wp);
		if (id == IDC_COMBO_SELECT) {
			select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_GETCURSEL, 0, 0);
		}
		else if (id == IDC_COMBO_SIZE) {
			int size = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_GETCURSEL, 0, 0);
			switch (size) {
			case BRUSH_SIZE::BRUSH_SMALL:
				brushSize_ = brushS;
				break;
			case BRUSH_SIZE::BRUSH_MEDIUM:
				brushSize_ = brushM;
				break;
			case BRUSH_SIZE::BRUSH_LARGE:
				brushSize_ = brushL;
				break;
			default:
				break;
			}
		}
		else {
			switch (id) {
				//���W�I�{�^��
			case IDC_RADIO_UP:
				mode_ = MODE::MODE_UP;
				break;
			case IDC_RADIO_DOWN:
				mode_ = MODE::MODE_DOWN;
				break;
			case IDC_RADIO_CHANGE:
				mode_ = MODE::MODE_CHANGE;
				break;

				//�{�^��
			case IDC_BUTTON_UNDO:
				pManager_->Undo(this);
				break;
			case IDC_BUTTON_REDO:
				pManager_->Redo(this);
				break;
			default:
				break;
			}
		}
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

//�I�����ꂽ�u���b�N�̌v�Z
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

	//�}�E�X�̈ʒu�̎擾
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//�}�E�X�̈ʒu��3D��Ԃɋt�v�Z
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

				//���C�L���X�g
				Model::RayCast(hModel_.at(0), data);

				//�������Ă�����
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
}

void Stage::MoveUpBlock() {
	switch (brushSize_) {
	case brushS:
		table_[selectBlock_.x_][selectBlock_.z_].height_++;
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				//�͈͊O�Ȃ�X�L�b�v
				if (selectBlock_.x_ + x < 0)	continue;
				if (selectBlock_.x_ + x >= 15)	continue;
				if (selectBlock_.z_ + z < 0)	continue;
				if (selectBlock_.z_ + z >= 15)	continue;
				table_[selectBlock_.x_ + x][selectBlock_.z_ + z].height_++;
			}
		}
		break;
	case brushL:
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				//�͈͊O�Ȃ�X�L�b�v
				if (selectBlock_.x_ + x < 0)	continue;
				if (selectBlock_.x_ + x >= 15)	continue;
				if (selectBlock_.z_ + z < 0)	continue;
				if (selectBlock_.z_ + z >= 15)	continue;
				table_[selectBlock_.x_ + x][selectBlock_.z_ + z].height_++;
			}
		}
		break;
	default:
		break;
	}
}

void Stage::MoveDownBlock() {
	switch (brushSize_) {
	case brushS:
		//0�ȉ��ɂ͉������Ȃ�
		if (table_[selectBlock_.x_][selectBlock_.z_].height_ > 0)
			table_[selectBlock_.x_][selectBlock_.z_].height_--;
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				//�͈͊O�Ȃ�X�L�b�v
				if (selectBlock_.x_ + x < 0)	continue;
				if (selectBlock_.x_ + x >= 15)	continue;
				if (selectBlock_.z_ + z < 0)	continue;
				if (selectBlock_.z_ + z >= 15)	continue;
				//0�ȉ��ɂ͉������Ȃ�
				if (table_[selectBlock_.x_ + x][selectBlock_.z_ + z].height_ > 0)
					table_[selectBlock_.x_ + x][selectBlock_.z_ + z].height_--;
			}
		}
		break;
	case brushL:
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				//�͈͊O�Ȃ�X�L�b�v
				if (selectBlock_.x_ + x < 0)	continue;
				if (selectBlock_.x_ + x >= 15)	continue;
				if (selectBlock_.z_ + z < 0)	continue;
				if (selectBlock_.z_ + z >= 15)	continue;
				//0�ȉ��ɂ͉������Ȃ�
				if (table_[selectBlock_.x_ + x][selectBlock_.z_ + z].height_ > 0)
					table_[selectBlock_.x_ + x][selectBlock_.z_ + z].height_--;
			}
		}
		break;
	default:
		break;
	}
}

void Stage::ChangeBlock() {
	switch (brushSize_) {
	case brushS:
		table_[selectBlock_.x_][selectBlock_.z_].type_ = (BOX_TYPE)select_;
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				//�͈͊O�Ȃ�X�L�b�v
				if (selectBlock_.x_ + x < 0)	continue;
				if (selectBlock_.x_ + x >= 15)	continue;
				if (selectBlock_.z_ + z < 0)	continue;
				if (selectBlock_.z_ + z >= 15)	continue;
				table_[selectBlock_.x_ + x][selectBlock_.z_ + z].type_ = (BOX_TYPE)select_;
			}
		}
		break;
	case brushL:
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				//�͈͊O�Ȃ�X�L�b�v
				if (selectBlock_.x_ + x < 0)	continue;
				if (selectBlock_.x_ + x >= 15)	continue;
				if (selectBlock_.z_ + z < 0)	continue;
				if (selectBlock_.z_ + z >= 15)	continue;
				table_[selectBlock_.x_ + x][selectBlock_.z_ + z].type_ = (BOX_TYPE)select_;
			}
		}
		break;
	default:
		break;
	}
}

int Stage::GetBlockHeight(int x, int z) {
	return table_[x][z].height_;
}

BOX_TYPE Stage::GetBlockType(int x, int z) {
	return table_[x][z].type_;
}

void Stage::NewStage() {
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			table_[x][z].type_ = (BOX_TYPE)(x % BOX_TYPE::BOX_MAX);
			table_[x][z].height_ = 0;
		}
	}
}

void Stage::LoadStage() {
	//�Z�[�u�_�C�A���O
	char fileName[MAX_PATH] = "";  //�t�@�C����������ϐ�
	string path = std::filesystem::current_path().string();
	path += "\\����.map";
	path.copy(fileName, MAX_PATH);

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn;										//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));							//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);					//�\���̂̃T�C�Y
	ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")	//�����t�@�C���̎��
		TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");				//����
	ofn.lpstrFile = fileName;								//�t�@�C����
	ofn.nMaxFile = MAX_PATH;								//�p�X�̍ő啶����
	ofn.Flags = OFN_FILEMUSTEXIST;							//�t���O�i���݂���t�@�C�������I�ׂȂ��j
	ofn.lpstrDefExt = "map";								//�f�t�H���g�g���q

	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	///// �ǂݍ��� /////
	HANDLE hFile;        //�t�@�C���̃n���h��
	hFile = CreateFile(
		"map.csv",				//�t�@�C����
		GENERIC_READ,			//�A�N�Z�X���[�h�i�������ݗp�j
		0,						//���L�i�Ȃ��j
		NULL,					//�Z�L�����e�B�����i�p�����Ȃ��j
		OPEN_EXISTING,			//�쐬���@
		FILE_ATTRIBUTE_NORMAL,	//�����ƃt���O�i�ݒ�Ȃ��j
		NULL					//�g�������i�Ȃ��j
	);

	//�t�@�C���̃T�C�Y���擾
	DWORD fileSize = GetFileSize(hFile, NULL);

	//�t�@�C���̃T�C�Y�����������m��
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //�ǂݍ��݈ʒu

	BOOL result = ReadFile(
		hFile,		//�t�@�C���n���h��
		data,		//�f�[�^������ϐ�
		fileSize,	//�ǂݍ��ރT�C�Y
		&dwBytes,	//�ǂݍ��񂾃T�C�Y
		NULL		//�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j
	);
	if (result == FALSE) {
		delete[] data;
		CloseHandle(hFile);
		return;
	}

	string sData = data;
	string tmp = "";
	string::iterator it = sData.begin();

	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			//�����̏��̌���
			while (true) {
				if ((*it) == ',')	break;
				tmp += (*it);
				it++;
			}
			table_[x][z].height_ = std::stoi(tmp);
			tmp = "";
			it++;

			//��ނ̏��̌���
			while (true) {
				if ((*it) == ',' || (*it) == 'z')	break;
				tmp += (*it);
				it++;
			}
			table_[x][z].type_ = (BOX_TYPE)std::stoi(tmp);
			if ((*it) == 'z')	break;
			tmp = "";
			it++;

			//���s�R�[�h����������C�e���[�^��i�߂�
			if ((*it) == '\n')	it++;
		}
		if ((*it) == 'z')	break;
	}

	delete[] data;
	CloseHandle(hFile);
}

void Stage::SaveStage() {
	//�Z�[�u�_�C�A���O
	char fileName[MAX_PATH] = "";  //�t�@�C����������ϐ�
	string path = std::filesystem::current_path().string();
	path += "\\����.map";
	path.copy(fileName, MAX_PATH);

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn;										//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));							//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);					//�\���̂̃T�C�Y
	ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")	//�����t�@�C���̎��
		TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");				//����
	ofn.lpstrFile = fileName;								//�t�@�C����
	ofn.nMaxFile = MAX_PATH;								//�p�X�̍ő啶����
	ofn.Flags = OFN_OVERWRITEPROMPT;						//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = "map";								//�f�t�H���g�g���q

	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	///// �������� /////
	HANDLE hFile;        //�t�@�C���̃n���h��
	hFile = CreateFile(
		fileName,				//�t�@�C����
		GENERIC_WRITE,			//�A�N�Z�X���[�h�i�������ݗp�j
		0,						//���L�i�Ȃ��j
		NULL,					//�Z�L�����e�B�����i�p�����Ȃ��j
		CREATE_ALWAYS,			//�쐬���@
		FILE_ATTRIBUTE_NORMAL,	//�����ƃt���O�i�ݒ�Ȃ��j
		NULL					//�g�������i�Ȃ��j
	);
	if (hFile == nullptr)	return;

	DWORD dwBytes = 0;	//�������݈ʒu

	string data = "";
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			data += std::to_string(table_[x][z].height_) + ",";
			data += std::to_string(table_[x][z].type_);
			//�Ō�̃f�[�^��������R���}��ł��Ȃ�
			if (x == sizeX - 1 && z == sizeZ - 1)	break;
			data += ",";
		}
		if (x == sizeX - 1)	break;
		data += "\n";
	}

	data += "z";
	BOOL result = WriteFile(
		hFile,						//�t�@�C���n���h��
		data.c_str(),				//�ۑ�����f�[�^�i������j
		(DWORD)strlen(data.c_str()),//�������ޕ�����
		&dwBytes,					//�������񂾃T�C�Y������ϐ�
		NULL						//�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j
	);

	CloseHandle(hFile);
}
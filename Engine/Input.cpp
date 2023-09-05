#include "Input.h"
#include <string>

namespace Input {
	//DirectInput�̖{��
	LPDIRECTINPUT8   pDInput_ = nullptr;

	//----------�ϐ�----------//

	//�L�[�{�[�h
	LPDIRECTINPUTDEVICE8 pKeyDevice_ = nullptr;	//�L�[�{�[�h�f�o�C�X�I�u�W�F�N�g
	BYTE keyState_[256] = { 0 };					//���݂̏��
	BYTE prevKeyState_[256] = { 0 };				//1�t���[���O�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	POINT mousePos_;						//�}�E�X�J�[�\���̈ʒu

	//----------�֐�----------//

	//������
	void Initialize(HWND hWnd) {
		//DirectInput�̍쐬
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		
		//�L�[�{�[�h�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɛݒ�
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//�}�E�X
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	//�X�V
	void Update() {
		//1�t���[���O�̏�Ԃ̃R�s�[
		memcpy(prevKeyState_, keyState_, sizeof(BYTE) * 256);

		pKeyDevice_->Acquire();
		pKeyDevice_->GetDeviceState(sizeof(keyState_), &keyState_);

		//�}�E�X
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

	}

	//�L�[�{�[�h//
	
	//�L�[��������Ă��邩
	bool IsKey(int keyCode) {
		if (keyState_[keyCode] & 0x80) {
			return true;
		}
		return false;
	}

	//�L�[�������ꂽ��
	bool IsKeyDown(int keyCode) {
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState_[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	//�L�[�������ꂽ��
	bool IsKeyUp(int keyCode) {
		//���͉����ĂȂ��āA�O��͉����Ă�
		if (!IsKey(keyCode) && (prevKeyState_[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	//�}�E�X

	//�}�E�X�̃{�^����������Ă��邩���ׂ�
	bool IsMouseButton(int buttonCode)
	{
		//�����Ă�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//�}�E�X�̃{�^�����������������ׂ�
	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//�}�E�X�J�[�\���̈ʒu���擾
	XMFLOAT3 GetMousePosition()
	{
		XMFLOAT3 result = XMFLOAT3((float)mousePos_.x, (float)mousePos_.y, 0);
		return result;
	}

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	void SetMousePosition(int x, int y)
	{
		mousePos_.x = x;
		mousePos_.y = y;
		std::string result = "set mouse to " + std::to_string(x) + ", " + std::to_string(y) + "\n";
		OutputDebugString(result.c_str());
	}


	//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾
	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}


	//���
	void Release() {
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice_);
		SAFE_RELEASE(pDInput_);
	}
}
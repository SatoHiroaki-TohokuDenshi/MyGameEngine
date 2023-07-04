#include "Input.h"

namespace Input {
	//DirectInput�̖{��
	LPDIRECTINPUT8   pDInput = nullptr;

	//�L�[�{�[�h�f�o�C�X�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	//�L�[�{�[�h�̊Ď��p�ϐ�
	BYTE keyState[256] = { 0 };		//���݂̏��
	BYTE prevKeyState[256] = { 0 };	//1�t���[���O�̏��

	//������
	void Initialize(HWND hWnd) {
		//DirectInput�̍쐬
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		
		//�L�[�{�[�h�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɛݒ�
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	//�X�V
	void Update() {
		//1�t���[���O�̏�Ԃ̃R�s�[
		memcpy(prevKeyState, keyState, sizeof(BYTE) * 256);

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	//�L�[��������Ă��邩
	bool IsKey(int keyCode) {
		if (keyState[keyCode] & 0x80) {
			return true;
		}
		return false;
	}

	//�L�[�������ꂽ��
	bool IsKeyDown(int keyCode) {
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	//�L�[�������ꂽ��
	bool IsKeyUp(int keyCode) {
		//���͉����ĂȂ��āA�O��͉����Ă�
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	//���
	void Release() {
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}
}
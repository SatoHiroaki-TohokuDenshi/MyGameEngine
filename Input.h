#pragma once
#include <dInput.h>

//�����J
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//����}�N��
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input {
	//������
	void Initialize(HWND hWnd);
	//�X�V
	void Update();
	//�L�[�̌��o
	//�����F�L�[�̔ԍ�
	//�ߒl�Ftrue������Ă���@false������Ă��Ȃ�
	bool IsKey(int keyCode);
	//���
	void Release();
};
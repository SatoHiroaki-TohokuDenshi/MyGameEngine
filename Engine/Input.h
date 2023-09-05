#pragma once
#include <dInput.h>
#include <DirectXMath.h>
#include "SafetyMacro.h"

//�����J
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

using namespace DirectX;

namespace Input {
	//������
	void Initialize(HWND hWnd);
	//�X�V
	void Update();
	//���
	void Release();

	//----------�L�[�{�[�h�̊֐�----------//
	
	//�L�[��������Ă��邩
	bool IsKey(int keyCode);
	//�L�[�������ꂽ�u�Ԃ�
	bool IsKeyDown(int keyCode);
	//�L�[�������ꂽ�u�Ԃ�
	bool IsKeyUp(int keyCode);

	//----------�}�E�X�̊֐�----------//

	//�}�E�X��������Ă��邩
	bool IsMouseButton(int buttonCode);
	//�}�E�X�������ꂽ�u�Ԃ�
	bool IsMouseButtonDown(int buttonCode);
	//�}�E�X�������ꂽ�u�Ԃ�
	bool IsMouseButtonUp(int buttonCode);
	//�}�E�X�̈ʒu���w��
	void SetMousePosition(int x, int y);
	//�}�E�X�̈ʒu
	XMFLOAT3 GetMousePosition();
	//�}�E�X�̈ړ���
	XMFLOAT3 GetMouseMove();
};
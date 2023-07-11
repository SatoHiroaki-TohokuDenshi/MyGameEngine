#pragma once
#include <dInput.h>
#include "SafetyMacro.h"

//�����J
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

namespace Input {
	//������
	void Initialize(HWND hWnd);
	//�X�V
	void Update();

	/// <summary>�L�[��������Ă��邩</summary>
	/// <param name="keyCode">���ׂ����L�[�̔ԍ�</param>
	/// <returns>������Ă�����true</returns>
	bool IsKey(int keyCode);
	
	/// <summary>�L�[�������ꂽ��</summary>
	/// <param name="keyCode">���ׂ����L�[�̔ԍ�</param>
	/// <returns>�����ꂽ�u�ԂȂ�true</returns>
	bool IsKeyDown(int keyCode);

	/// <summary>�L�[�������ꂽ��</summary>
	/// <param name="keyCode">���ׂ����L�[�̔ԍ�</param>
	/// <returns>�����ꂽ�u�ԂȂ�true</returns>
	bool IsKeyUp(int keyCode);
	//���
	void Release();
};
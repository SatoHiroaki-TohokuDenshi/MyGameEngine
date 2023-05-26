#pragma once
#include <d3d11.h>

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Direct3D {
	//������
	void Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	void InitShader();

	//�`��J�n�i�������F��ʂ�P�F�ŏ���������j
	void BeginDraw();

	//�`��I���i�����F��ʂ�\��������j
	void EndDraw();

	//���
	void Release();
};
#pragma once
#include <d3d11.h>
#include <cassert>

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//���S�ɊJ������}�N��
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Direct3D {
	extern ID3D11Device* pDevice_;			//�f�o�C�X
	extern ID3D11DeviceContext* pContext_;	//�f�o�C�X�R���e�L�X�g

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();

	//�`��J�n�i�������F��ʂ�P�F�ŏ���������j
	void BeginDraw();

	//�`��I���i�����F��ʂ�\��������j
	void EndDraw();

	//���
	void Release();
};
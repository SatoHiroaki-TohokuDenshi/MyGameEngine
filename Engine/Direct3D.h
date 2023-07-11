#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "SafetyMacro.h"


//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

//�V�F�[�_�[�̎��
enum SHADER_TYPE {
	SHADER_2D,		//2D�p�V�F�[�_�[
	SHADER_3D,		//3D�p�V�F�[�_�[
	SHADER_MAX,
};


namespace Direct3D {
	extern ID3D11Device* pDevice_;			//�f�o�C�X
	extern ID3D11DeviceContext* pContext_;	//�f�o�C�X�R���e�L�X�g

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
};
#pragma once
#include <d3d11.h>
#include <cassert>

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//���S�ɊJ������}�N��
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

enum SHADER_TYPE {
	SHADER_3D = 0,
	SHADER_2D,
	SHADER_MAX,
};

struct ShaderBundle {
	ID3D11VertexShader* pVertexShader_;			//���_�V�F�[�_�[
	ID3D11PixelShader* pPixelShader_;			//�s�N�Z���V�F�[�_�[
	ID3D11RasterizerState* pRasterizerState_;	//���X�^���C�U�[
	ID3D11InputLayout* pVertexLayout_;			//���_�C���v�b�g���C�A�E�g
};

namespace Direct3D {
	extern ID3D11Device* pDevice_;			//�f�o�C�X
	extern ID3D11DeviceContext* pContext_;	//�f�o�C�X�R���e�L�X�g

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT Init3DShader();
	HRESULT Init2DShader();

	//�R���e�L�X�g�̐ݒ�
	//����  0:3D�p�V�F�[�_�[  1:2D�p�V�F�[�_�[
	void SetContext(SHADER_TYPE type);

	//�`��J�n�i�������F��ʂ�P�F�ŏ���������j
	void BeginDraw();

	//�`��I���i�����F��ʂ�\��������j
	void EndDraw();

	//���
	void Release();
};
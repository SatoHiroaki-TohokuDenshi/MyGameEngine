#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

class Sprite {
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER {
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;	//�ʒu���
		XMVECTOR uv;		//UV���W
	};
protected:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;				//�e�N�X�`�����
	int indexNum_;					//���_�C���f�b�N�X�̗v�f��

	float width_;
	float height_;
public:
	Sprite();
	virtual ~Sprite();
	virtual HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix, int winW, int winH);
	void Release();

	void PassInfoConstantBuffer(XMMATRIX& worldMatrix);
};
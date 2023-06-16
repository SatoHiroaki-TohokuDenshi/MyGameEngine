#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ p->Release(); p = nullptr;}

using namespace DirectX;

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

class Sprite {
protected:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;				//�e�N�X�`�����
	int indexNum_;					//���_�C���f�b�N�X�̗v�f��
public:
	Sprite();
	~Sprite();
	//������
	virtual HRESULT Initialize();

	//�`��
	void Draw(XMMATRIX& worldMatrix);

	//�J��
	void Release();

	void PassInfoConstantBuffer(XMMATRIX& worldMatrix);
};


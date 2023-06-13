#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//���_���
struct VERTEX
{
	XMVECTOR position;	//�ʒu���
	XMVECTOR uv;		//UV���W
	XMVECTOR normal;	//�@���x�N�g��
};

class Quad {
protected:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;				//�e�N�X�`�����
	int indexNum_;					//���_�C���f�b�N�X�̗v�f��
public:
	Quad();
	virtual ~Quad();
	virtual HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();

	void PassInfoConstantBuffer(XMMATRIX& worldMatrix);
};
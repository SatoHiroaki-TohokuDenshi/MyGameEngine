#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Texture.h"

//�����J
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx {
	//�R���X�^���g�o�b�t�@�ɓn�������܂Ƃ߂��\����
	struct CONSTANT_BUFFER {
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	//���_���
	struct VERTEX {
		XMVECTOR position;
	};

	//�}�e���A��
	struct MATERIAL {
		Texture* pTexture;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

public:
	Fbx();
	//�ǂݍ���
	HRESULT Load(std::string fileName);
	//�`��
	void    Draw(Transform& transform);
	//�J��
	void    Release();

private:
	//---------Initialize�֐�����Ă΂��֐�---------
	//���_�o�b�t�@����
	HRESULT InitVertex(fbxsdk::FbxMesh* mesh);

	//�C���f�b�N�X�o�b�t�@����
	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);

	//�R���X�^���g�o�b�t�@����
	HRESULT InitConstantBuffer();

	//�}�e���A������
	void InitMaterial(fbxsdk::FbxNode* pNode);

	//---------Draw�֐�����Ă΂��֐�---------
	void PassDataToCB(Transform transform);	//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();
};
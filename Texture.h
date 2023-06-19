#pragma once
#include <d3d11.h>
#include <string>
#include <wrl.h>

using namespace Microsoft::WRL;
using std::string;

class Texture {
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;

	size_t width_;		//����
	size_t height_;		//�c��
	size_t depth_;		//���s
public:
	Texture();
	~Texture();
	//�摜�̓ǂݍ���
	HRESULT Load(string fileName);
	//���
	void Release();
	//�T���v���[�̃Q�b�^�[
	ID3D11SamplerState* GetSampler() { return pSampler_; };
	//�V�F�[�_�[���\�[�X�r���[�̃Q�b�^�[
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; };

	//�����̃Q�b�^�[
	size_t GetWidth() { return width_; };
	//�c���̃Q�b�^�[
	size_t GetHeight() { return height_; };
	//���s�̃Q�b�^�[
	size_t GetDepth() { return depth_; };
};
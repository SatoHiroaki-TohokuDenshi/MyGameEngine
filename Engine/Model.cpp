#include "Model.h"
#include <vector>
#include "Direct3D.h"
#include "SafetyMacro.h"

using std::vector;

namespace Model {
	//�f�[�^���i�[����\����
	struct ModelData {
		Fbx* pFbx_;				//FBX�̃A�h���X
		Transform transform_;	//Transform�̏��
		string fileName_;		//�t�@�C���̖��O

		//�ϐ���������
		ModelData() :pFbx_(nullptr), transform_(Transform()), fileName_("") {};
	};

	vector<ModelData*> modelList_;

	int Load(string fileName) {
		ModelData* pData = new ModelData();
		for (auto& e : modelList_) {
			if (e->fileName_ == fileName) {
				pData->pFbx_ = e->pFbx_;
				break;
			}
		}

		if (pData->pFbx_ == nullptr) {
			//�t�@�C���̓ǂݍ���
			pData->pFbx_ = new Fbx();
			if (FAILED(pData->pFbx_->Load(fileName)))
				return -1;
			pData->fileName_ = fileName;
		}
		modelList_.push_back(pData);
		//���f���̃C���f�b�N�X�ԍ���Ԃ�
		return (int)modelList_.size() - 1;
	}

	void SetTransform(int hModel, Transform t) {
		modelList_.at(hModel)->transform_ = t;
	}

	void Draw(int hModel) {
		modelList_.at(hModel)->pFbx_->Draw(modelList_.at(hModel)->transform_);
	}

	void Release() {
		bool isRefferenced = false;	//�Q�Ƃ���Ă��邩
		for (int i = 0; i < modelList_.size(); i++) {
			for (int j = i + 1; j < modelList_.size(); j++) {
				if (modelList_.at(i)->pFbx_ == modelList_.at(j)->pFbx_) {
					isRefferenced = true;
					break;
				}
			}
			if (isRefferenced == false) {
				SAFE_DELETE(modelList_.at(i)->pFbx_);
			}
			SAFE_DELETE(modelList_.at(i));
		}
		modelList_.clear();
	}

	void RayCast(int hModel, RayCastData& data) {
		//���f���̈ʒu���v�Z
		modelList_.at(hModel)->transform_.Calclation();
		//���[���h�s��̋t�s��
		XMMATRIX invWorld = XMMatrixInverse(nullptr, modelList_.at(hModel)->transform_.GetWorldMatrix());

		//���C�̒ʉߓ_�𒲂ׂ�
		XMVECTOR vPass = {
			data.start.x + data.dir.x,
			data.start.y + data.dir.y,
			data.start.z + data.dir.z,
			data.start.w + data.dir.w
		};
		//data.start�����f����Ԃɕϊ�
		XMVECTOR vStart = XMLoadFloat4(&data.start);
		vStart = XMVector3TransformCoord(vStart, invWorld);
		//�ʉߓ_�Ƀ��[���h�s��̋t��������
		vPass = XMVector3TransformCoord(vPass, invWorld);
		//data.dir�Ƀ��C�̃x�N�g��������
		vPass = vPass - vStart;
		XMStoreFloat4(&data.dir, vPass);

		modelList_.at(hModel)->pFbx_->RayCast(data);
	}
}
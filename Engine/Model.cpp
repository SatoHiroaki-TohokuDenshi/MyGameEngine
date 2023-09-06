#include "Model.h"
#include <vector>
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
		modelList_.at(hModel)->pFbx_->RayCast(data);
	}
}
#include "Model.h"


namespace dbmanager {
	bool Model::IsValidModel()
	{
		for (auto& f : values) {
			if (f.second == true)
				return false;
		}

		return true;
	}
	void Model::SetValidation(std::string& colName) {
		if (newRow_->find(colName) != newRow_->end()) {
			delete (newRow_->at(colName));
			newRow_->erase(colName);
		}
	}
}
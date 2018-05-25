#include "Model.h"
#include <iostream>

namespace dbmanager {

	void Model::Save(const std::shared_ptr<Connection>& connection)
	{
		if (IsValidModel()) {
			try {
				if (isFirstTimeCreated_) {
					connection->AddRow(newRow_, ownRow_);
					isFirstTimeCreated_ = false;
				}
				else {
					connection->UpdateRow(newRow_, ownRow_);
				}
			}
			catch (const std::string&ex) {
				std::cout << ex << "\n";
			}
		}
		else {
			throw std::string("Some column is empty, cannot save object" + GetModelName());
		}
	}
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
#pragma once
#include "utils.h"
#include "DBTable.h"
#include "Connection.h"
#include <memory>

namespace dbmanager {
	class Model {
	public:
		Model() : isFirstTimeCreated_(true) {

		}
		virtual ~Model() = default;

		virtual Header GetHeader() = 0;
		virtual void Save() = 0;
		virtual bool Delete() = 0;
		virtual std::string GetModelName() = 0;
		virtual bool IsValidModel() = 0;
	protected:
		std::string modelName_;

		bool isFirstTimeCreated_;
		std::shared_ptr<Row> ownRow_;
		std::shared_ptr<Row> newRow_;
	};
}
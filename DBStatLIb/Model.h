#pragma once
#include "utils.h"
#include "DBTable.h"
#include "Connection.h"
#include <memory>

namespace dbmanager {
	class Model {
	public:
		Model() : isFirstTimeCreated_(true), isModelInited_(false) {}

		virtual ~Model() = default;

		virtual void Save() = 0;
		virtual bool Delete() = 0;
		virtual std::string GetModelName() = 0;
		virtual bool IsValidModel();
	protected:
		std::string modelName_;

		bool isModelInited_;
		bool isFirstTimeCreated_;
		std::shared_ptr<Row> ownRow_;
		std::shared_ptr<Row> newRow_;

		std::map<std::string, bool> values;

		virtual void SetValidation(std::string&);
	};
}
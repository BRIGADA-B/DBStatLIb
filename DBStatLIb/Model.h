#pragma once
#include "utils.h"
#include "DBTable.h"
#include "Connection.h"
#include <memory>

namespace dbmanager {
	class Model {
	public:
		Model() : isFirstTimeCreated_(true), isModelInited_(false) {
			newRow_ = std::make_shared<Row>();
			ownRow_ = std::make_shared<Row>();
		}

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
		virtual void Save(const std::shared_ptr<Connection>&);
		static bool IsColumnNameValid(const std::string& columnName);
	};

}
#pragma once
#include <memory>
#include "DBTable.h"

namespace dbmanager {

	class AbstractTableCreator {
	public:
		virtual ~AbstractTableCreator() = default;
		virtual DBTable* create() = 0;
	};

	template<class C>
	class TableCreator : public AbstractTableCreator {
	public:
		DBTable* create() override {
			return new C();
		}
	};

	class TableFactory {
	protected:
		using FactoryMap = std::map<std::string, AbstractTableCreator*>;
		FactoryMap factory_;

	public:
		TableFactory() = default;
		virtual ~TableFactory() = default;

		template <class C>
		void add(const std::string& id) {
			auto it = factory_.find(id);

			if (it == factory_.end()) {
				factory_[id] = new TableCreator<C>();
			}
		}

		DBTable* create(const std::string& id) {
			auto it = factory_.find(id);

			if (it != factory_.end())
				return it->second->create();
			return 0;
		}

	};
}
#pragma once
#include <string>
#include "sqlite3.h"
#include <functional>

class SqlTemplate
{
public:
	explicit SqlTemplate(sqlite3& conn);
	~SqlTemplate();

private:
	sqlite3& conn;

public:

	bool Query(const std::string& query
		, std::function<int(sqlite3_stmt&)> parmalMapper
		, std::function<void(sqlite3_stmt&)> executor) const;
};

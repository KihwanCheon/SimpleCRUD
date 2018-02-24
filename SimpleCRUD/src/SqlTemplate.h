#pragma once
#include <string>
#include "sqlite3.h"
#include <functional>

class SqlTemplate
{
private:
	SqlTemplate();
	~SqlTemplate();

public:

	static bool Query(sqlite3* conn, const std::string& query
		, std::function<int(sqlite3_stmt&)> parmalMapper
		, std::function<void(sqlite3_stmt&)> resutlMapper);
};

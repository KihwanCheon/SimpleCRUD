#pragma once
#include <string>
#include <cstring>
#include "sqlite3.h"
#include <functional>

class SqlTemplate
{
public:
	explicit SqlTemplate(sqlite3& conn);
	virtual ~SqlTemplate();
private:
	SqlTemplate(const SqlTemplate&);
	SqlTemplate operator=(const SqlTemplate&);

protected:
	sqlite3& conn;

public:
	bool Query(const std::string& query
		, const std::function<int(sqlite3_stmt&)>& parmalMapper
		, const std::function<void(sqlite3_stmt&)>& executor) const;

	bool Execute(const std::string& query
		, const std::function<int(sqlite3_stmt&)>& parmalMapper) const;

	class ScopedTran
	{
	public:
		ScopedTran(SqlTemplate& t);
		~ScopedTran();
	private:
		ScopedTran(const ScopedTran&);
		ScopedTran operator=(const ScopedTran&);

	private:
		SqlTemplate &t;
	public:
		bool hasError;
	};
}
;

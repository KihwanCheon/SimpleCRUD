#include  "SqlTemplate.h"

using namespace std;

SqlTemplate::SqlTemplate() = default;

SqlTemplate::~SqlTemplate() = default;

bool SqlTemplate::Query(sqlite3* conn, const std::string& query, 
	function<int(sqlite3_stmt&)> parmalMapper
	, function<void(sqlite3_stmt&)> resutlMapper)
{
	sqlite3_stmt* pstmt = nullptr;
	const char* tail = nullptr;
	const char* sql = query.c_str();
	const int prepareResult = sqlite3_prepare(conn, sql, static_cast<int>(strlen(sql)), &pstmt, &tail);
	if (prepareResult != SQLITE_OK)
	{
		fprintf(stderr, "failed prepare stmt");
		return false;
	}

	const int bindResult = parmalMapper(*pstmt);
	if (bindResult != SQLITE_OK)
	{
		fprintf(stderr, "bind text failed");
		return false;
	}

	while (sqlite3_step(pstmt) == SQLITE_ROW)
	{
		resutlMapper(*pstmt);
	}

	sqlite3_reset(pstmt);
	sqlite3_finalize(pstmt);

	return true;
}

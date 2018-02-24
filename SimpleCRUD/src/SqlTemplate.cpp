#include  "SqlTemplate.h"

using namespace std;

SqlTemplate::SqlTemplate(sqlite3& conn) : conn(conn)
{
};

SqlTemplate::~SqlTemplate()
{
};

bool SqlTemplate::Query(const std::string &query, 
	function<int(sqlite3_stmt&)> parmalMapper
	, function<void(sqlite3_stmt&)> executor) const
{
	sqlite3_stmt* pstmt = nullptr;
	const char* tail = nullptr;
	const char* sql = query.c_str();
	const int prepareResult = sqlite3_prepare(&conn, sql, strlen(sql), &pstmt, &tail);
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
	
	executor(*pstmt);
	
	sqlite3_reset(pstmt);
	sqlite3_finalize(pstmt);

	return true;
}

bool SqlTemplate::Execute(const std::string& query
	, std::function<int(sqlite3_stmt&)> parmalMapper) const
{
	sqlite3_stmt* pstmt = nullptr;
	const char* tail = nullptr;
	const char* sql = query.c_str();
	const int prepareResult = sqlite3_prepare(&conn, sql, static_cast<int>(strlen(sql)), &pstmt, &tail);
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

	const int stepResult = sqlite3_step(pstmt);
	if (stepResult != SQLITE_DONE)
	{
		fprintf(stderr, "failed execute stmt %s", sqlite3_errmsg(sqlite3_db_handle(pstmt)));
	}

	sqlite3_reset(pstmt);
	sqlite3_finalize(pstmt);

	return true;
}

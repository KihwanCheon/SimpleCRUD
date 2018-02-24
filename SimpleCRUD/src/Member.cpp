//
// Created by NHNEnt on 2018. 2. 17..
//

#include <iostream>
#include "Member.h"
#include "sqlite3.h"
#include "SqlTemplate.h"


namespace Member
{
	DAO::DAO(sqlite3 *&conn) :conn(conn) 
	{

	}

	DAO::~DAO()
	{

	}

	bool DAO::insert(Member &dto) 
	{
		return SqlTemplate::Query(conn,
			"insert into Member(name, age) values(?1, ?2)"
			, [&](sqlite3_stmt& pstmt)->int
			{
				int rtBindText = sqlite3_bind_text(&pstmt, 1, dto.name.c_str(), (int)strlen(dto.name.c_str()), SQLITE_STATIC);
				if (rtBindText != SQLITE_OK)
				{
					fprintf(stderr, "bind text failed");
					return rtBindText;
				}

				int rtBindInt = sqlite3_bind_int(&pstmt, 2, dto.age);
				if (rtBindInt != SQLITE_OK)
				{
					fprintf(stderr, "bind int failed");
					return rtBindText;
				}
				return rtBindInt;
			},
			[&](sqlite3_stmt& pstmt)->void
			{
				const int stepResult = sqlite3_step(&pstmt);
				if (stepResult != SQLITE_DONE)
				{
					fprintf(stderr, "failed insert stmt %s", sqlite3_errmsg(sqlite3_db_handle(&pstmt)));
				}
			}
		);
	}

	bool DAO::select(const char *name, Member &dto) {
		return SqlTemplate::Query(conn,
			"select rowid, name, age from Member where name = ?1 "
			, [&](sqlite3_stmt& pstmt)->int
			{
				return sqlite3_bind_text(&pstmt, 1, name, (int)strlen(name), SQLITE_STATIC);
			},
			[&](sqlite3_stmt& pstmt)->void
			{
				if (sqlite3_step(&pstmt) == SQLITE_ROW)
				{
					dto.id = sqlite3_column_int(&pstmt, 0);
					const unsigned char* dbName = sqlite3_column_text(&pstmt, 1);
					dto.name = std::string((char*)dbName);
					dto.age = sqlite3_column_int(&pstmt, 2);
				}
			}
		);
	}

	bool DAO::count(int &count) {
		sqlite3_stmt* pstmt = nullptr;
		const char* tail = nullptr;
		const char* sql = "select count(*) from Member";
		int rt2 = sqlite3_prepare(conn, sql, (int)strlen(sql), &pstmt, &tail);
		if (rt2 != SQLITE_OK)
		{
			fprintf(stderr, "failed prepare stmt");
			return false;
		}

		int rStep = sqlite3_step(pstmt);
		if (rStep == SQLITE_ERROR)
		{
			fprintf(stderr, "failed insert stmt %s", sqlite3_errmsg(sqlite3_db_handle(pstmt)));
			return false;
		}
		else if (rStep == SQLITE_ROW)
		{
			count = sqlite3_column_int(pstmt, 0);
		}

		sqlite3_reset(pstmt);
		sqlite3_finalize(pstmt);

		return true;
	}

}
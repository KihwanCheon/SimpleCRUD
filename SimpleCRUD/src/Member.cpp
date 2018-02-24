//
// Created by NHNEnt on 2018. 2. 17..
//

#include <iostream>
#include "Member.h"
#include "sqlite3.h"
#include "SqlTemplate.h"


namespace Member
{
	DAO::DAO(sqlite3* &conn) : SqlTemplate(*conn)
	{
		
	}

	DAO::~DAO()
	{
		
	}

	bool DAO::insert(Member &dto) 
	{
		return Execute(
			"insert into Member(name, age) values(?1, ?2)"
			, [&](sqlite3_stmt& pstmt)->int
			{
				int rtBindText = sqlite3_bind_text(&pstmt, 1, dto.name.c_str(), strlen(dto.name.c_str()), SQLITE_STATIC);
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
			}
		);
	}

	bool DAO::select(const char *name, Member &dto) {
		return Query(
			"select rowid, name, age from Member where name = ?1 "
			, [&](sqlite3_stmt& pstmt)->int
			{
				return sqlite3_bind_text(&pstmt, 1, name, strlen(name), SQLITE_STATIC);
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

	bool DAO::count(int &count) 
	{
		return Query(
			"select count(*) from Member"
			, [&](sqlite3_stmt& pstmt)->int
			{
				return SQLITE_OK;
			},
			[&](sqlite3_stmt& pstmt)->void
			{
				const int rStep = sqlite3_step(&pstmt);
				if (rStep == SQLITE_ERROR)
				{
					fprintf(stderr, "failed insert stmt %s", sqlite3_errmsg(sqlite3_db_handle(&pstmt)));
				}
				else if (rStep == SQLITE_ROW)
				{
					count = sqlite3_column_int(&pstmt, 0);
				}
			}
		);
	}
}
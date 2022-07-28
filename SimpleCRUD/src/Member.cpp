//
//

#include <iostream>
#include "Member.h"
#include "sqlite3.h"
#include "SqlTemplate.h"


namespace Member
{
	void Member::save()
	{
		SqlTemplate::ScopedTran st(dao);

		if (id > 0)
			dao.update(*this);
		else
			dao.insert(*this);
	}

	void Member::refresh()
	{
		Member m(dao);
		m.id = id;
		if (dao.selectById(m))
		{
			age = m.age;
			name = m.name;
		}
	}

	Member::Member(DAO& dao): dao(dao), id(0), age(0)
	{
	}

	Member::~Member()
	{
	}

	DAO::DAO(sqlite3* &conn) : SqlTemplate(*conn)
	{
	}

	DAO::~DAO()
	{
	}

	bool DAO::insert(Member &dto) 
	{
		const bool rt = Execute(
			"insert into Member(name, age) values(?1, ?2)"
			, [&](sqlite3_stmt& pstmt)->int
			{
				int rtBindText = sqlite3_bind_text(&pstmt, 1, dto.name.c_str(), static_cast<int>(strlen(dto.name.c_str())), SQLITE_STATIC);
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

		if (rt)
		{
			dto.id = static_cast<int>(sqlite3_last_insert_rowid(&conn));
		}
		
		return rt;
	}

	bool DAO::update(Member& dto)
	{
		return Execute(
			"update Member set name = ?1, age = ?2 where rowid = ?3"
			, [&](sqlite3_stmt& pstmt)->int
			{
				int bindNameResult = sqlite3_bind_text(&pstmt, 1, dto.name.c_str(), static_cast<int>(strlen(dto.name.c_str())), SQLITE_STATIC);
				if (bindNameResult != SQLITE_OK)
				{
					fprintf(stderr, "bind name failed");
					return bindNameResult;
				}

				int bindAgeResult = sqlite3_bind_int(&pstmt, 2, dto.age);
				if (bindAgeResult != SQLITE_OK)
				{
					fprintf(stderr, "bind age failed");
					return bindAgeResult;
				}

				int bindIdResult = sqlite3_bind_int(&pstmt, 3, dto.id);
				if (bindIdResult != SQLITE_OK)
				{
					fprintf(stderr, "bind id failed");
					return bindIdResult;
				}

				return bindIdResult;
			}
		);
	}

	bool DAO::select(const char *name, Member &dto) {
		return Query(
			"select rowid, name, age from Member where name = ?1 "
			, [&](sqlite3_stmt& pstmt)->int
			{
				return sqlite3_bind_text(&pstmt, 1, name, static_cast<int>(strlen(name)), SQLITE_STATIC);
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

    int DAO::selectById(Member& dto)
    {
        return Query(
                "select name, age from Member where rowid = ?1 "
                , [&](sqlite3_stmt& pstmt)->int
                {
                    return sqlite3_bind_int(&pstmt, 1, dto.id);
                },
                [&](sqlite3_stmt& pstmt)->void
                {
                    if (sqlite3_step(&pstmt) == SQLITE_ROW)
                    {
                        const unsigned char* dbName = sqlite3_column_text(&pstmt, 0);
                        dto.name = std::string((char*)dbName);
                        dto.age = sqlite3_column_int(&pstmt, 1);
                    }
                }
        );
    }

	bool DAO::deleteBy(int id)
	{
		return Execute("delete from Member where rowid = ?1 "
			, [&](sqlite3_stmt& pstmt)->int
			{
				return sqlite3_bind_int(&pstmt, 1, id);
			}
		);
	}
}

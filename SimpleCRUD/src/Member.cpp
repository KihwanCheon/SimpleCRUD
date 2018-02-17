//
// Created by NHNEnt on 2018. 2. 17..
//

#include <iostream>
#include "Member.h"
#include "sqlite3.h"


using namespace Member;


DAO::DAO(sqlite3* &conn) :conn(conn) {

}

DAO::~DAO()
{

}


bool DAO::insert(DTO &dto) {

    sqlite3_stmt* pstmt = nullptr;
    const char* tail = nullptr;
    const char* sql = "insert into Member(name, age) values(?1, ?2)";
    int rt2 = sqlite3_prepare(conn, sql, (int)strlen(sql), &pstmt, &tail);
    if (rt2 != SQLITE_OK)
    {
        fprintf(stderr, "failed prepare stmt");
        return false;
    }

    int rtBindText = sqlite3_bind_text(pstmt, 1, dto.name.c_str(), (int)strlen(dto.name.c_str()), SQLITE_STATIC);
    if (rtBindText != SQLITE_OK)
    {
        fprintf(stderr, "bind text failed");
        return false;
    }

    int rtBindInt = sqlite3_bind_int(pstmt, 2, dto.age);
    if (rtBindInt != SQLITE_OK)
    {
        fprintf(stderr, "bind int failed");
        return false;
    }

    int rStep = sqlite3_step(pstmt);
    if (rStep != SQLITE_DONE)
    {
        fprintf(stderr, "failed insert stmt %s", sqlite3_errmsg(sqlite3_db_handle(pstmt)));
        return false;
    }

    sqlite3_reset(pstmt);
    sqlite3_finalize(pstmt);

    return true;
}

bool DAO::select(const char *name, DTO &dto) {
    sqlite3_stmt* pstmt = nullptr;
    const char* tail = nullptr;
    const char* sql = "select * from Member where name = ?1 ";
    int rt2 = sqlite3_prepare(conn, sql, (int)strlen(sql), &pstmt, &tail);
    if (rt2 != SQLITE_OK)
    {
        fprintf(stderr, "failed prepare stmt");
        return false;
    }

    int rtBindText = sqlite3_bind_text(pstmt, 1, name, (int)strlen(name), SQLITE_STATIC);
    if (rtBindText != SQLITE_OK)
    {
        fprintf(stderr, "bind text failed");
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
        const unsigned char* dbName = sqlite3_column_text(pstmt, 0);
        dto.name = std::string((char*)dbName);
        dto.age = sqlite3_column_int(pstmt, 1);
    }

    sqlite3_reset(pstmt);
    sqlite3_finalize(pstmt);

    return true;
}
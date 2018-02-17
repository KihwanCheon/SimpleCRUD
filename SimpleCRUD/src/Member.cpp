//
// Created by NHNEnt on 2018. 2. 17..
//

#include <iostream>
#include "Member.h"
#include "sqlite3.h"

using namespace Member;


DAO::DAO(sqlite3& *conn) :conn(conn) {

}

DAO::~DAO()
{

}

static int callback_insert(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool DAO::insert(DTO &dto) {

    sqlite3 *conn = nullptr;
    sqlite3_open("local_sqlite.db", &conn);

    if (conn == nullptr) {
        std::cout << "fail open conn" << std::endl;
        return false;
    }

    char *errMsg = nullptr;
    int rt = sqlite3_exec(conn, "CREATE TABLE Member(name varchar(20), age int);", callback_insert, 0, &errMsg);

    if (rt != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    sqlite3_stmt* pstmt = nullptr;
    const char* tail = nullptr;
    const char* sql = "insert into Member(name, age) values(?1, ?2)";
    int rt2 = sqlite3_prepare(conn, sql, (int)strlen(sql), &pstmt, &tail);
    if (rt2 != SQLITE_OK)
    {
        fprintf(stderr, "failed prepare stmt");
        sqlite3_close(conn);
        return false;
    }

    int rtBindText = sqlite3_bind_text(pstmt, 1, dto.name.c_str(), (int)strlen(dto.name.c_str()), SQLITE_STATIC);
    if (rtBindText != SQLITE_OK)
    {
        fprintf(stderr, "bind text failed");
        sqlite3_close(conn);
        return false;
    }

    int rtBindInt = sqlite3_bind_int(pstmt, 2, dto.age);
    if (rtBindInt != SQLITE_OK)
    {
        fprintf(stderr, "bind int failed");
        sqlite3_close(conn);
        return false;
    }

    int rStep = sqlite3_step(pstmt);
    if (rStep != SQLITE_DONE)
    {
        fprintf(stderr, "failed insert stmt %s", sqlite3_errmsg(sqlite3_db_handle(pstmt)));
        sqlite3_close(conn);
        return false;
    }

    sqlite3_reset(pstmt);
    sqlite3_close(conn);

    return true;
}

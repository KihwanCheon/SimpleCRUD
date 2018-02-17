//
// Created by NHNEnt on 2018. 2. 17..
//
#include <gtest/gtest.h>
#include "Member.h"

namespace Member
{

    static int callback_insert(void *NotUsed, int argc, char **argv, char **azColName) {
        int i;
        for (i = 0; i < argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }

    TEST(MemberDTO, insert_test)
    {
        sqlite3 *conn = nullptr;
        sqlite3_open("local_sqlite.db", &conn);

        if (conn == nullptr) {
            std::cout << "fail open conn" << std::endl;

            ASSERT_TRUE(false);
        }

        char *errMsg = nullptr;
        int rt = sqlite3_exec(conn, "CREATE TABLE Member(name varchar(20), age int);", callback_insert, 0, &errMsg);

        if (rt != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            fprintf(stdout, "Table created successfully\n");
        }

        DAO dao(conn);
        DTO dto;
        dto.name  = "gujjy";
        dto.age = 30;
        bool success = dao.insert(dto);

        EXPECT_EQ(success, true);

        DTO rtDB;
        success = dao.select("gujjy", rtDB);

        if (success) {
            EXPECT_EQ(rtDB.age, 30);
            EXPECT_STREQ(rtDB.name.c_str(), "gujjy");
        }


        char *errDropMsg = nullptr;
        rt = sqlite3_exec(conn, "DROP TABLE Member", callback_insert, 0, &errDropMsg);

        if (rt != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            fprintf(stdout, "Table DROP successfully\n");
        }

        sqlite3_close(conn);
        printf("done!");
    }
}
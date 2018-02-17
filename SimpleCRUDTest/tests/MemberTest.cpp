//
// Created by NHNEnt on 2018. 2. 17..
//
#include <gtest/gtest.h>
#include "Member.h"

namespace Member
{
    class DAOTest: public testing::Test
    {
    public:
        DAOTest();
        virtual ~DAOTest();;

    public:
        sqlite3 *conn;

    public:
        virtual void SetUp()
        {
            sqlite3_open("local_sqlite.db", &conn);

            if (conn == nullptr) {
                std::cout << "fail open conn" << std::endl;
                assert(false);
            }

            char *errMsg = nullptr;
            int rt = sqlite3_exec(conn, "CREATE TABLE Member(name varchar(20), age int);", callback_insert, nullptr, &errMsg);

            if (rt != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                fprintf(stdout, "Table Member CREATED successfully\n");
            }
        }

        virtual void TearDown()
        {
            char *errDropMsg = nullptr;
            int rt = sqlite3_exec(conn, "DROP TABLE Member", callback_insert, nullptr, &errDropMsg);

            if (rt != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", errDropMsg);
                sqlite3_free(errDropMsg);
            } else {
                fprintf(stdout, "Table Member DROPPED successfully\n");
            }

            sqlite3_close(conn);
            printf("done! \n");
            conn = nullptr;
        }

        static int callback_insert(void *NotUsed, int argc, char **argv, char **azColName) {
            int i;
            for (i = 0; i < argc; i++) {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            }
            printf("\n");
            return 0;
        }
    };

    DAOTest::~DAOTest() {}

    DAOTest::DAOTest() :conn(nullptr) {}

    TEST_F(DAOTest, insert_test)
    {
        DAO dao(conn);

        //lbl_insert:
        {
            Member dto;
            dto.name = "gujjy";
            dto.age = 30;
            bool success = dao.insert(dto);

            EXPECT_EQ(success, true);
        }

        // lbl_update:
        {
            Member rtDB;
            bool success = dao.select("gujjy", rtDB);

            if (success) {
                EXPECT_EQ(rtDB.id, 1);
                EXPECT_EQ(rtDB.age, 30);
                EXPECT_STREQ(rtDB.name.c_str(), "gujjy");
            }
        }

        // lbl_count:
        {
            int count;
            bool success = dao.count(count);

            if (success) {
                EXPECT_EQ(count, 1);
            }
        }

        // lbl_delete:
        {
            bool success = dao.deleteBy(1);
            if (success) {
                int count;
                success = dao.count(count);

                if (success) {
                    EXPECT_EQ(count, 0);
                }
            } else
                EXPECT_TRUE(false);
        }
    }
}

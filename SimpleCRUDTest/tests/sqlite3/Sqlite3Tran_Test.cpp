//
// Created by NHNEnt on 2018. 2. 17..
//

#include <gtest/gtest.h>
#include "sqlite3.h"

namespace SqliteTranTest {

    class TRANTest : public testing::Test {
    public:
        explicit TRANTest();

        virtual ~TRANTest();

    protected:
        sqlite3 *conn;

    public:
        virtual void SetUp() {
            sqlite3_open("local_sqlite.db", &conn);
            if (conn == nullptr) {
                std::cout << "fail open conn" << std::endl;
                assert(false);
            }
        }

        virtual void TearDown() {
            sqlite3_close(conn);
            printf("done! \n");
            conn = nullptr;
        }

        static int callback_sqlite_exec(void *NotUsed, int argc, char **argv, char **azColName) {
            int i;
            for (i = 0; i < argc; i++) {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            }
            printf("\n");
            return 0;
        }
    };

    TRANTest::TRANTest() {}

    TRANTest::~TRANTest() {}

    TEST_F(TRANTest, check_autocommit_default_1) {
        int auto_commit_mode = sqlite3_get_autocommit(conn);
        EXPECT_EQ(auto_commit_mode, 1);

        char *errMsg;
        int rt = sqlite3_exec(conn, "BEGIN", callback_sqlite_exec, nullptr, &errMsg);

        if (rt != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            fprintf(stdout, "BEGIN transaction successfully\n");
        }

        auto_commit_mode = sqlite3_get_autocommit(conn);
        EXPECT_EQ(auto_commit_mode, 0);

        rt = sqlite3_exec(conn, "ROLLBACK", callback_sqlite_exec, nullptr, &errMsg);

        if (rt != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            fprintf(stdout, "ROLLBACK transaction successfully\n");
        }

        auto_commit_mode = sqlite3_get_autocommit(conn);
        EXPECT_EQ(auto_commit_mode, 1);
    }
}
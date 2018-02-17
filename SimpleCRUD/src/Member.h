//
// Created by NHNEnt on 2018. 2. 17..
//
#pragma once

#include <string>
#include <sqlite3.h>

namespace Member {

    struct DTO {
        std::string name;
        int age;
    };

    class DAO {
    public:
        DAO(sqlite3* &conn);
        ~DAO();
    private:
        sqlite3* conn;
    public:
        bool insert(DTO& dto);

        bool select(const char *name, DTO &dto);

        bool count(int &count);
    };
}

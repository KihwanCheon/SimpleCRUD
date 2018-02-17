//
// Created by NHNEnt on 2018. 2. 17..
//
#pragma once

#include <string>
#include <sqlite3.h>

namespace Member {

    struct Member {
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
        bool insert(Member& dto);

        bool select(const char *name, Member &dto);

        bool count(int &count);
    };
}

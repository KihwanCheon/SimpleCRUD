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
        bool insert(DTO& dto);
    };
}

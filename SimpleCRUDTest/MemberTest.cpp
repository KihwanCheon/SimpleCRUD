//
// Created by NHNEnt on 2018. 2. 17..
//
#include <gtest/gtest.h>
#include "Member.h"

namespace Member
{
    TEST(MemberDTO, insert_test)
    {
        DAO dao(NULL);
        DTO dto;
        dto.name  = "gujjy";
        dto.age = 30;
        bool success = dao.insert(dto);

        EXPECT_EQ(success, true);
    }
}

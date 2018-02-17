//
// Created by NHNEnt on 2018. 2. 16..
//
#include <iostream>
#include "gtest/gtest.h"


class MinimalistPrinter : public ::testing::EmptyTestEventListener {
    // Called before a test starts.
    virtual void OnTestStart(const ::testing::TestInfo &test_info) {
        printf("*** Test %s.%s starting.\n",
               test_info.test_case_name(), test_info.name());
    }

    // Called after a failed assertion or a SUCCEED() invocation.
    virtual void OnTestPartResult(
            const ::testing::TestPartResult &test_part_result) {
        printf("%s in %s:%d\n%s\n",
               test_part_result.failed() ? "*** Failure" : "Success",
               test_part_result.file_name(),
               test_part_result.line_number(),
               test_part_result.summary());
    }

    // Called after a test ends.
    virtual void OnTestEnd(const ::testing::TestInfo &test_info) {
        printf("*** Test %s.%s ending.\n",
               test_info.test_case_name(), test_info.name());
    }
};


int main(int argc, char **argv) {
    std::cout << "hihi" << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    // Gets hold of the event listener list.
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.  Google Test takes the ownership.
    listeners.Append(new MinimalistPrinter);
    return RUN_ALL_TESTS();

}

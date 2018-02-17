#include <iostream>
#include "sqlite3.h"

int main() {

    std::cout << "Hello, World!" << std::endl;
    std::cout << sqlite3_version << std::endl;
    return 0;
}
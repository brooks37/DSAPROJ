#include "Menu.hpp"
#include <iostream>

int main() {
    // Assume your test CSV file is named "testCases.csv"
    Menu menu("testCases.csv");
    menu.run();
    return 0;
}

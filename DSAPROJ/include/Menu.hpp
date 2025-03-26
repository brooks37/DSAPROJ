#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include "MultiSolutionTestRunner.hpp"

class Menu {
public:
    // Constructor takes the filename containing test cases.
    Menu(const std::string& testFile);
    // Display the menu and process user input.
    void run();
    
private:
    std::string testFile;
    // Functions to run tests for each solution individually.
    void runNaiveTests();
    void runDynamicTests();
    void runGreedyTests();
    // Function to run all tests and compare the results.
    void runAllTestsAndCompare();
};

#endif // MENU_HPP

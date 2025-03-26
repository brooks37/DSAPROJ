#include "Menu.hpp"
#include "NaiveSolution.hpp"
#include "DynamicSolution.hpp"
#include "GreedySolution.hpp"
#include <iostream>
#include <functional>
#include <iomanip>
#include <vector>
#include <fstream>

// Constructor
Menu::Menu(const std::string& testFile) : testFile(testFile) {}

// Display the menu options.
void Menu::run() {
    int choice;
    do {
        std::cout << "\n--- Benchmark Menu ---\n";
        std::cout << "1. Run Naive Tests\n";
        std::cout << "2. Run Dynamic Tests\n";
        std::cout << "3. Run Greedy Tests\n";
        std::cout << "4. Run All Tests and Compare Results\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                runNaiveTests();
                break;
            case 2:
                runDynamicTests();
                break;
            case 3:
                runGreedyTests();
                break;
            case 4:
                runAllTestsAndCompare();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (choice != 5);
}

// Run tests only for the Naive solution.
void Menu::runNaiveTests() {
    MultiSolutionTestRunner runner;
    NaiveSolution naive;
    std::function<int(const std::vector<int>&)> naiveFunc = [&naive](const std::vector<int>& arr) {
        return naive.findWater(arr);
    };
    std::cout << "\n--- Running Naive Tests ---\n";
    std::vector<TestResult> results = runner.runSingleTests(testFile, naiveFunc, "Naive");

    // Optionally, print each test result.
    for (const auto& tr : results) {
        std::cout << "Test " << tr.testCase << " (size " << tr.inputSize << "): " 
                  << tr.naiveTime << " ms, result: " << tr.naiveResult 
                  << (tr.naivePassed ? " (PASS)" : " (FAIL)") << "\n";
    }
}

// Run tests only for the Dynamic solution.
void Menu::runDynamicTests() {
    MultiSolutionTestRunner runner;
    DynamicSolution dynamic;
    std::function<int(const std::vector<int>&)> dynamicFunc = [&dynamic](const std::vector<int>& arr) {
        return dynamic.findWater(arr);
    };
    std::cout << "\n--- Running Dynamic Tests ---\n";
    std::vector<TestResult> results = runner.runSingleTests(testFile, dynamicFunc, "Dynamic");

    for (const auto& tr : results) {
        std::cout << "Test " << tr.testCase << " (size " << tr.inputSize << "): " 
                  << tr.dynamicTime << " ms, result: " << tr.dynamicResult 
                  << (tr.dynamicPassed ? " (PASS)" : " (FAIL)") << "\n";
    }
}

// Run tests only for the Greedy solution.
void Menu::runGreedyTests() {
    MultiSolutionTestRunner runner;
    GreedySolution greedy;
    std::function<int(const std::vector<int>&)> greedyFunc = [&greedy](const std::vector<int>& arr) {
        return greedy.findWater(arr);
    };
    std::cout << "\n--- Running Greedy Tests ---\n";
    std::vector<TestResult> results = runner.runSingleTests(testFile, greedyFunc, "Greedy");

    for (const auto& tr : results) {
        std::cout << "Test " << tr.testCase << " (size " << tr.inputSize << "): " 
                  << tr.greedyTime << " ms, result: " << tr.greedyResult 
                  << (tr.greedyPassed ? " (PASS)" : " (FAIL)") << "\n";
    }
}

// Run all tests for all solutions and output a comparison table.
void Menu::runAllTestsAndCompare() {
    MultiSolutionTestRunner runner;
    NaiveSolution naive;
    DynamicSolution dynamic;
    GreedySolution greedy;
    std::function<int(const std::vector<int>&)> naiveFunc = [&naive](const std::vector<int>& arr) {
        return naive.findWater(arr);
    };
    std::function<int(const std::vector<int>&)> dynamicFunc = [&dynamic](const std::vector<int>& arr) {
        return dynamic.findWater(arr);
    };
    std::function<int(const std::vector<int>&)> greedyFunc = [&greedy](const std::vector<int>& arr) {
        return greedy.findWater(arr);
    };

    std::cout << "\n--- Running All Tests and Comparing ---\n";
    std::vector<TestResult> results = runner.runTests(testFile, naiveFunc, dynamicFunc, greedyFunc);

    // Print a nicely formatted comparison table.
    std::cout << "\nComparison Table:\n";
    std::cout << std::left 
              << std::setw(8) << "Test" 
              << std::setw(12) << "InputSize" 
              << std::setw(20) << "NaiveTime(ms)" 
              << std::setw(20) << "DynamicTime(ms)" 
              << std::setw(20) << "GreedyTime(ms)" 
              << std::endl;
    
    // Print a separator line.
    std::cout << std::string(8+12+20+20+20, '-') << std::endl;
    
    // Print each test result with fixed precision.
    for (const auto& tr : results) {
        std::cout << std::left 
                  << std::setw(8) << tr.testCase 
                  << std::setw(12) << tr.inputSize
                  << std::setw(20) << std::fixed << std::setprecision(6) << tr.naiveTime
                  << std::setw(20) << std::fixed << std::setprecision(6) << tr.dynamicTime
                  << std::setw(20) << std::fixed << std::setprecision(6) << tr.greedyTime
                  << std::endl;
    }
}


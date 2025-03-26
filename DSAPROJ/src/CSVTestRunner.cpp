#include "CSVTestRunner.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

// Helper function to parse a line of comma-separated integers into a vector.
std::vector<int> parseArrayLine(const std::string& line) {
    std::vector<int> result;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        // Trim whitespace.
        token.erase(0, token.find_first_not_of(" \t\n\r"));
        token.erase(token.find_last_not_of(" \t\n\r") + 1);
        if (!token.empty()) {
            result.push_back(std::stoi(token));
        }
    }
    return result;
}

// Helper function to parse the expected output line into an integer.
int parseExpectedLine(const std::string& line) {
    std::stringstream ss(line);
    int value;
    ss >> value;
    return value;
}

bool CSVTestRunner::runTests(const std::string& filename,
                             const std::function<int(const std::vector<int>&)>& customFunction) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
        return false;
    }
    
    // Clear previous elapsed times.
    elapsedTimes_.clear();
    
    std::string inputLine;
    std::string expectedLine;
    int testCase = 1;
    int totalTests = 0;
    int passedTests = 0;
    
    while (std::getline(infile, inputLine)) {
        // Skip empty lines.
        if (inputLine.empty())
            continue;
        
        // Read the expected output line.
        if (!std::getline(infile, expectedLine)) {
            std::cerr << "Error: Expected output missing for test case " << testCase << std::endl;
            break;
        }
        
        totalTests++;
        // Start timing for this test case.
        auto startTime = std::chrono::steady_clock::now();
        
        // Parse the input array and expected output.
        std::vector<int> inputArray = parseArrayLine(inputLine);
        int expectedOutput = parseExpectedLine(expectedLine);
        
        // Call the custom function on the input.
        int actualOutput = customFunction(inputArray);
        
        // Stop timing.
        auto endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> testDuration = endTime - startTime;
        elapsedTimes_.push_back(testDuration.count());
        
        if (actualOutput == expectedOutput) {
            passedTests++;
        }
        
        testCase++;
    }
    
    infile.close();
    
    // Calculate percentage of tests passed.
    double percentPassed = (totalTests > 0) ? (static_cast<double>(passedTests) / totalTests) * 100.0 : 0.0;
    std::cout << "\nTest Summary:" << std::endl;
    std::cout << "Total test cases: " << totalTests << std::endl;
    std::cout << "Passed: " << passedTests << std::endl;
    std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
    std::cout << "Percentage passed: " << percentPassed << "%" << std::endl;
    
    return (passedTests == totalTests);
}

const std::vector<double>& CSVTestRunner::getElapsedTimes() const {
    return elapsedTimes_;
}

#include "MultiSolutionTestRunner.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iomanip> // For std::fixed and std::setprecision

// Increase the number of iterations to get a measurable total time.
static const int ITERATIONS = 50;

// Helper function: parse a comma-separated line into a vector of ints.
static std::vector<int> parseArrayLine(const std::string& line) {
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

// Helper function: parse expected output from a line.
static int parseExpectedLine(const std::string& line) {
    std::stringstream ss(line);
    int value;
    ss >> value;
    return value;
}

// Updated helper function to run a test function with timeout.
// It runs the function ITERATIONS times using std::chrono::high_resolution_clock,
// averages the elapsed times (measured in microseconds, then converted to ms),
// and returns a pair: {result, averageElapsedTime in ms}.
// A volatile temporary variable is used to prevent compiler optimization.
template <typename Func>
static std::pair<int, double> runWithTimeout(const Func& func, const std::vector<int>& inputArray, int expectedOutput, double timeoutSec) {
    double totalTime = 0.0;
    int result = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        volatile int tmp_result = func(inputArray);  // Prevent compiler optimization.
        result = tmp_result;
        auto end = std::chrono::high_resolution_clock::now();
        // Measure in microseconds, then convert to milliseconds.
        double elapsedTime = std::chrono::duration<double, std::micro>(end - start).count() / 1000.0;
        totalTime += elapsedTime;
        // If any iteration exceeds the timeout, report a timeout immediately.
        if (elapsedTime >= timeoutSec * 1000.0) {
            std::cerr << "Timeout occurred after " << timeoutSec << " seconds in iteration " << i + 1 << std::endl;
            return { -1, totalTime / (i + 1) };
        }
    }
    double avgTime = totalTime / ITERATIONS;
    // If the average is very low, output in microseconds.
    if (avgTime < 1.0) {
        std::cout << std::fixed << std::setprecision(7)
                  << "Average elapsed time: " << avgTime * 1000.0 << " us" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision(6)
                  << "Average elapsed time: " << avgTime << " ms" << std::endl;
    }
    return { result, avgTime };
}

std::vector<TestResult> MultiSolutionTestRunner::runTests(
    const std::string& filename,
    const std::function<int(const std::vector<int>&)>& naiveFunc,
    const std::function<int(const std::vector<int>&)>& dynamicFunc,
    const std::function<int(const std::vector<int>&)>& greedyFunc) {
    
    std::vector<TestResult> results;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
        return results;
    }
    
    // Clear previous elapsed times.
    elapsedTimesNaive_.clear();
    elapsedTimesDynamic_.clear();
    elapsedTimesGreedy_.clear();
    
    std::string inputLine;
    std::string expectedLine;
    int testCase = 1;
    int totalTests = 0;
    int naivePassed = 0;
    int dynamicPassed = 0;
    int greedyPassed = 0;
    
    while (std::getline(infile, inputLine)) {
        if (inputLine.empty())
            continue;
        if (!std::getline(infile, expectedLine)) {
            std::cerr << "Error: Expected output missing for test case " << testCase << std::endl;
            break;
        }
        
        totalTests++;
        std::vector<int> inputArray = parseArrayLine(inputLine);
        int expectedOutput = parseExpectedLine(expectedLine);
        
        TestResult tr;
        tr.testCase = testCase;
        tr.inputSize = static_cast<int>(inputArray.size());
        tr.expected = expectedOutput;
        
        // Run naive solution with timeout.
        auto naiveResultPair = runWithTimeout(naiveFunc, inputArray, expectedOutput, 3.0);
        tr.naiveTime = naiveResultPair.second;
        if (naiveResultPair.first == -1) {
            tr.naiveResult = -1;
            tr.naivePassed = false;
        } else {
            tr.naiveResult = naiveResultPair.first;
            tr.naivePassed = (naiveResultPair.first == expectedOutput);
            if (tr.naivePassed)
                naivePassed++;
        }
        elapsedTimesNaive_.push_back(tr.naiveTime);
        
        // Run dynamic solution with timeout.
        auto dynamicResultPair = runWithTimeout(dynamicFunc, inputArray, expectedOutput, 3.0);
        tr.dynamicTime = dynamicResultPair.second;
        if (dynamicResultPair.first == -1) {
            tr.dynamicResult = -1;
            tr.dynamicPassed = false;
        } else {
            tr.dynamicResult = dynamicResultPair.first;
            tr.dynamicPassed = (dynamicResultPair.first == expectedOutput);
            if (tr.dynamicPassed)
                dynamicPassed++;
        }
        elapsedTimesDynamic_.push_back(tr.dynamicTime);
        
        // Run greedy solution with timeout.
        auto greedyResultPair = runWithTimeout(greedyFunc, inputArray, expectedOutput, 3.0);
        tr.greedyTime = greedyResultPair.second;
        if (greedyResultPair.first == -1) {
            tr.greedyResult = -1;
            tr.greedyPassed = false;
        } else {
            tr.greedyResult = greedyResultPair.first;
            tr.greedyPassed = (greedyResultPair.first == expectedOutput);
            if (tr.greedyPassed)
                greedyPassed++;
        }
        elapsedTimesGreedy_.push_back(tr.greedyTime);
        
        results.push_back(tr);
        testCase++;
    }
    
    infile.close();
    
    double naivePercent = (totalTests > 0) ? (naivePassed * 100.0 / totalTests) : 0.0;
    double dynamicPercent = (totalTests > 0) ? (dynamicPassed * 100.0 / totalTests) : 0.0;
    double greedyPercent = (totalTests > 0) ? (greedyPassed * 100.0 / totalTests) : 0.0;
    
    std::cout << "\nTest Summary (All Solutions):" << std::endl;
    std::cout << "Total test cases: " << totalTests << std::endl;
    std::cout << "Naive passed: " << naivePassed << " (" << naivePercent << "%)" << std::endl;
    std::cout << "Dynamic passed: " << dynamicPassed << " (" << dynamicPercent << "%)" << std::endl;
    std::cout << "Greedy passed: " << greedyPassed << " (" << greedyPercent << "%)" << std::endl;
    
    return results;
}

std::vector<TestResult> MultiSolutionTestRunner::runSingleTests(
    const std::string& filename,
    const std::function<int(const std::vector<int>&)>& solutionFunc,
    const std::string& label) {
    
    std::vector<TestResult> results;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
        return results;
    }
    
    std::string inputLine;
    std::string expectedLine;
    int testCase = 1;
    int totalTests = 0;
    int passedCount = 0;
    
    while (std::getline(infile, inputLine)) {
        if (inputLine.empty())
            continue;
        if (!std::getline(infile, expectedLine)) {
            std::cerr << "Error: Expected output missing for test case " << testCase << std::endl;
            break;
        }
        
        totalTests++;
        std::vector<int> inputArray = parseArrayLine(inputLine);
        int expectedOutput = parseExpectedLine(expectedLine);
        
        TestResult tr;
        tr.testCase = testCase;
        tr.inputSize = static_cast<int>(inputArray.size());
        tr.expected = expectedOutput;
        
        auto resultPair = runWithTimeout(solutionFunc, inputArray, expectedOutput, 5.0);
        
        if (label == "Naive") {
            tr.naiveTime = resultPair.second;
            if (resultPair.first == -1) {
                tr.naiveResult = -1;
                tr.naivePassed = false;
            } else {
                tr.naiveResult = resultPair.first;
                tr.naivePassed = (resultPair.first == expectedOutput);
                if (tr.naivePassed)
                    passedCount++;
            }
        } else if (label == "Dynamic") {
            tr.dynamicTime = resultPair.second;
            if (resultPair.first == -1) {
                tr.dynamicResult = -1;
                tr.dynamicPassed = false;
            } else {
                tr.dynamicResult = resultPair.first;
                tr.dynamicPassed = (resultPair.first == expectedOutput);
                if (tr.dynamicPassed)
                    passedCount++;
            }
        } else if (label == "Greedy") {
            tr.greedyTime = resultPair.second;
            if (resultPair.first == -1) {
                tr.greedyResult = -1;
                tr.greedyPassed = false;
            } else {
                tr.greedyResult = resultPair.first;
                tr.greedyPassed = (resultPair.first == expectedOutput);
                if (tr.greedyPassed)
                    passedCount++;
            }
        }
        
        results.push_back(tr);
        testCase++;
    }
    
    infile.close();
    
    double percentPassed = (totalTests > 0) ? (passedCount * 100.0 / totalTests) : 0.0;
    std::cout << "\nTest Summary (" << label << "):" << std::endl;
    std::cout << "Total test cases: " << totalTests << std::endl;
    std::cout << "Passed: " << passedCount << " (" << percentPassed << "%)" << std::endl;
    
    return results;
}

const std::vector<double>& MultiSolutionTestRunner::getElapsedTimesNaive() const {
    return elapsedTimesNaive_;
}

const std::vector<double>& MultiSolutionTestRunner::getElapsedTimesDynamic() const {
    return elapsedTimesDynamic_;
}

const std::vector<double>& MultiSolutionTestRunner::getElapsedTimesGreedy() const {
    return elapsedTimesGreedy_;
}

#ifndef MULTISOLUTIONTESTRUNNER_HPP
#define MULTISOLUTIONTESTRUNNER_HPP

#include <string>
#include <vector>
#include <functional>

/**
 * @brief Structure to hold the result of a single test case.
 */
struct TestResult {
    int testCase;
    int inputSize;
    int expected;
    int naiveResult;
    int dynamicResult;
    int greedyResult;
    double naiveTime;    // in milliseconds
    double dynamicTime;  // in milliseconds
    double greedyTime;   // in milliseconds
    bool naivePassed;
    bool dynamicPassed;
    bool greedyPassed;
};

/**
 * @brief A class to run test cases from a CSV file for multiple solution functions.
 *
 * Each test case in the CSV file consists of two consecutive lines:
 *   - The first line is a comma-separated list representing an array.
 *   - The second line is the expected output.
 *
 * This class will run three solution functions (naive, dynamic, greedy) on each test case,
 * record the results, elapsed times, and pass/fail status, print a summary, and provide
 * getter functions for the elapsed time vectors.
 */
class MultiSolutionTestRunner {
public:
    /**
     * @brief Runs test cases from a CSV file for all three solution functions.
     *
     * @param filename The CSV file containing the test cases.
     * @param naiveFunc A function that takes a const std::vector<int>& and returns an int (naive solution).
     * @param dynamicFunc A function that takes a const std::vector<int>& and returns an int (dynamic solution).
     * @param greedyFunc A function that takes a const std::vector<int>& and returns an int (greedy solution).
     * @return A vector of TestResult containing details for each test case.
     */
    std::vector<TestResult> runTests(const std::string& filename,
                                     const std::function<int(const std::vector<int>&)>& naiveFunc,
                                     const std::function<int(const std::vector<int>&)>& dynamicFunc,
                                     const std::function<int(const std::vector<int>&)>& greedyFunc);
    
    /**
     * @brief Runs test cases for a single solution function.
     *
     * @param filename The CSV file containing the test cases.
     * @param solutionFunc A function that takes a const std::vector<int>& and returns an int.
     * @param label A label for the solution (e.g., "Naive", "Dynamic", "Greedy").
     * @return A vector of TestResult where only the relevant fields (result, time, pass status) are filled.
     */
    std::vector<TestResult> runSingleTests(const std::string& filename,
                                           const std::function<int(const std::vector<int>&)>& solutionFunc,
                                           const std::string& label);
    
    /**
     * @brief Returns the vector of elapsed times (in ms) for the naive solution.
     */
    const std::vector<double>& getElapsedTimesNaive() const;
    
    /**
     * @brief Returns the vector of elapsed times (in ms) for the dynamic solution.
     */
    const std::vector<double>& getElapsedTimesDynamic() const;
    
    /**
     * @brief Returns the vector of elapsed times (in ms) for the greedy solution.
     */
    const std::vector<double>& getElapsedTimesGreedy() const;
    
private:
    std::vector<double> elapsedTimesNaive_;
    std::vector<double> elapsedTimesDynamic_;
    std::vector<double> elapsedTimesGreedy_;
};

#endif // MULTISOLUTIONTESTRUNNER_HPP

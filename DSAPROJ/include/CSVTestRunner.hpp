#ifndef CSVTESTRUNNER_HPP
#define CSVTESTRUNNER_HPP

#include <string>
#include <vector>
#include <functional>

/**
 * @brief A class for running test cases from a CSV file.
 *
 * Each test case in the CSV file consists of two consecutive lines:
 *   - The first line is a comma-separated list representing the input array.
 *   - The second line is a single value representing the expected output.
 *
 * After running the tests, the class stores the elapsed time (in milliseconds)
 * for each test case. Use getElapsedTimes() to retrieve the time vector.
 */
class CSVTestRunner {
public:
    /**
     * @brief Reads test cases from a CSV file and runs a custom function on each input.
     *
     * For each test case, the custom function is invoked with the input array.
     * The function's return value is compared with the expected output.
     * This function prints only the percentage of tests passed.
     *
     * @param filename The path to the CSV file containing the test cases.
     * @param customFunction A function that takes a const std::vector<int>& and returns an int.
     * @return true if all test cases pass; false otherwise.
     */
    bool runTests(const std::string& filename,
                  const std::function<int(const std::vector<int>&)>& customFunction);
    
    /**
     * @brief Returns the vector of elapsed times (in milliseconds) for each test case.
     *
     * @return A const reference to the vector of elapsed times.
     */
    const std::vector<double>& getElapsedTimes() const;

private:
    std::vector<double> elapsedTimes_;
};

#endif // CSVTESTRUNNER_HPP

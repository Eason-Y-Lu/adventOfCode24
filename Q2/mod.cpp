#include <oneapi/tbb.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <atomic>

int main()
{
    std::ifstream inputFile("input.txt");
    tbb::concurrent_vector<std::vector<int>> reportList;
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::vector<int> report;
        std::string number;
        line += ' ';
        for (char c : line)
        {
            if (c == ' ')
            {
                report.push_back(std::stoi(number));
                number.clear();
            }
            else
            {
                number += c;
            }
        }
        reportList.push_back(report);
    }
    inputFile.close();
    enum direction
    {
        INCREASING,
        DECREASING
    };
    tbb::concurrent_vector<bool> results;
    results.reserve(reportList.size());
    tbb::parallel_for_each(reportList.begin(), reportList.end(), [&](const std::vector<int> &report)
                           {
    std::vector<std::vector<int>> reportMinusOne;
    for (size_t i = 0; i < report.size(); ++i)
    {
        std::vector<int> reportCopy(report);
        reportCopy.erase(reportCopy.begin() + i);
        reportMinusOne.push_back(reportCopy);
    }
    reportMinusOne.push_back(report);
    std::vector<bool> intemediateResults(reportMinusOne.size());
    for (const auto &report : reportMinusOne){
        bool isValid = true;
        direction dir;
        if (report[1] - report[0] >=1 && 3 >= report[1] - report[0]){
            dir = INCREASING;
        }else if (report[1] - report[0] <= -1 && -3 <= report[1] - report[0]){
            dir = DECREASING; 
        }else{
            isValid = false;
            goto endloop;
        }
        for (size_t i = 1; i < report.size(); ++i){
            int diff = report[i] - report[i - 1];
            if (dir == INCREASING){
                if (diff < 1 || diff > 3)
                {
                    isValid = false;
                    break;
                }
            }
            else if (dir == DECREASING)
            {
                if (diff > -1 || diff < -3)
                {
                    isValid = false;
                    break;
                }
            }
        }
    endloop:
        intemediateResults.push_back(isValid);
    }
    int validCount = std::count(intemediateResults.begin(), intemediateResults.end(), true);
    if (validCount > 0) {
        results.push_back(true);
    } else {
        results.push_back(false);
    } });
    int validCount = std::count(results.begin(), results.end(), true);
    std::cout << "Number of valid reports: " << validCount << std::endl;
    return 0;
}

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::ifstream inputFile("input.txt");
    std::vector<int> listA;
    std::vector<int> listB;
    std::string line;
    int numberA;
    int numberB;
    while (std::getline(inputFile, line))
    {
        numberA = std::stoi(line.substr(0, 5));
        numberB = std::stoi(line.substr(8, 5));
        listA.push_back(numberA);
        listB.push_back(numberB);
    }
    inputFile.close();
    std::sort(listA.begin(), listA.end());
    std::sort(listB.begin(), listB.end());
    int difference = 0;
    for (size_t i = 0; i < listA.size(); ++i)
    {
        difference += std::abs(listA[i] - listB[i]);
    }
   std::cout << "The total difference is: " << difference << std::endl;
    return 0;
}
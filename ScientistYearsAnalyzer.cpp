//
// Max Base
// 06/24/2023
// https://github.com/BaseMax/ScientistYearsAnalyzer
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Scientist {
    std::string name;
    int birth;
    int death;
};

std::string findScientistsIn(int startYear, int endYear, const std::vector<Scientist>& scientists) {
    std::vector<std::string> scientistsInBestYears;
    for (const auto& scientist : scientists) {
        if (scientist.birth > endYear) continue;
        else if (scientist.death < startYear) continue;
        scientistsInBestYears.push_back(scientist.name);
    }

    // Sort the scientists' list based on their names
    std::sort(scientistsInBestYears.begin(), scientistsInBestYears.end());

    // Create the output string with scientists' names separated by newlines
    std::string output;
    for (const auto& scientist : scientistsInBestYears) {
        output += scientist + "\n";
    }

    return output;
}


std::string findBestYears(int numScientists, const std::vector<Scientist>& scientists) {
    std::unordered_map<int, int> yearCounts;

    // Count the number of scientists for each year
    for (const auto& scientist : scientists) {
        for (int year = scientist.birth; year <= scientist.death; ++year) {
            yearCounts[year]++;
        }
    }

    // Find the year(s) with the maximum count
    int maxCount = 0;
    for (const auto& entry : yearCounts) {
        maxCount = std::max(maxCount, entry.second);
    }

    std::vector<int> bestYears;
    for (const auto& entry : yearCounts) {
        if (entry.second == maxCount) {
            bestYears.push_back(entry.first);
        }
    }

    std::sort(bestYears.begin(), bestYears.end());

    // Get the oldest range among the best years
    int oldestStartYear = *bestYears.begin();
    int oldestEndYear = *bestYears.rbegin();

    // Check if there is a gap between the best years
    for (auto it = bestYears.begin(); it != bestYears.end() - 1; ++it) {
        if (*std::next(it) - *it > 1) {
            oldestEndYear = *it;
            break;
        }
    }

    // Create the output string
    std::string output = std::to_string(oldestStartYear) + "-" + std::to_string(oldestEndYear) + "\n";
    output += findScientistsIn(oldestStartYear, oldestEndYear, scientists);

    return output;
}

int main() {
    // Test 1
    int numScientists1 = 5;
    std::vector<Scientist> scientists1 {
        {"Alfred", 1884, 1923},
        {"Robert", 1733, 1892},
        {"Sarah", 1901, 1958},
        {"Richard", 1999, 2013},
        {"Harry", 1794, 1899}
    };
    std::string output1 = findBestYears(numScientists1, scientists1);
    std::cout << "Test 1 Output:\n" << output1 << "\n";

    // Test 2
    int numScientists2 = 4;
    std::vector<Scientist> scientists2 {
        {"Angela", 1488, 1560},
        {"Andre", 1497, 1594},
        {"Pitter", 1577, 1602},
        {"Ahmad", 1599, 1612}
    };
    std::string output2 = findBestYears(numScientists2, scientists2);
    std::cout << "Test 2 Output:\n" << output2 << "\n";
    
    return 0;
}

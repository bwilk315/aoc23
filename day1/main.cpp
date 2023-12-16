
#include <iostream>
#include <fstream>
#include <string>
#include <map>

static const std::string DIGIT_NAMES[10] {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

/* Finds digits in both numeric and textual form, returns a mapping of their
 * beginning indices (in the provided string context) to their integer representation. */
std::map<int, int>  extractDigits(std::string str) {
    auto digits = std::map<int, int>();
    // You can comment the loop below to get answer for the part 1
    // Search for textual digits
    for(int d = 1; d != 10; d++) {
        int beg = -1;
        while(true) {
            std::string name = DIGIT_NAMES[d];
            beg = str.find(name, beg + 1); // Next digit beginning
            if(beg == std::string::npos) break;
            else digits.insert(std::pair<int, int>(beg, d));
        }
    }
    // Search for numeric digits
    for(int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if(ch >= '0' && ch <= '9')
            // Convert char to integer and register the digit
            digits.insert(std::pair<int, int>(i, ch - '0'));
    }
    return digits;
}

int main() {
    std::ifstream file("input.txt");
    if(!file.good()) {
        std::cout << "No data file called \"input.txt\" found!\n";
        return 1;
    }

    std::string line;
    int sum = 0;
    while(std::getline(file, line)) {
        auto digits = extractDigits(line);
        int lowest = 999999;
        int greatest = 0;
        // Find the leftest and the rightest digits based on their indices
        for(const auto& pair : digits) {
            int index = pair.first;
            if(index < lowest) lowest = index;
            if(index > greatest) greatest = index;
        }
        sum += digits.at(lowest) * 10 + digits.at(greatest);
    }
    std::cout << "Answer: " << sum << std::endl;
    return 0;
}

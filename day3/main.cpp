
#include <iostream>
#include <fstream>
#include <string>
#include <map>

static const int ES_COUNT = 11;
static const char ENGINE_SYMBOLS[ES_COUNT] = {
    '@', '#', '$', '%', '&', '*', '/', '+', '-', '='
};

bool isEngineSymbol(const char& ch) {
    for(int s = 0; s < ES_COUNT; s++)
        if(ch == ENGINE_SYMBOLS[s])
            return true;
    return false;
}

bool isDigit(const char& ch) {
    return ch >= '0' && ch <= '9';
}

int main() {
    std::ifstream file("input.txt");
    if(!file.good()) {
        std::cout << "No file called \"input.txt\" found!\n";
        return 1;
    }

    std::string line;
    // Mappings of 2D array position to its content at that position
    auto symbols = std::map<std::pair<int, int>, char>();
    auto numbers = std::map<std::pair<int, int>, std::string>();
    int row = -1;
    while(std::getline(file, line)) {
        row++;
        for(int col = 0; col < line.length(); col++) {
            char ch = line[col];
            // Save symbol or number position and value
            if(isEngineSymbol(ch)) {
                symbols.insert(
                    std::pair<std::pair<int, int>, char>(std::pair<int, int>(col, row), ch)
                );
            } else if(isDigit(ch)) {
                // Load the digit textual form
                int pos = col;
                std::string num = "";
                while(isDigit(line[pos])) num += line[pos++];
                numbers.insert(
                    std::pair<std::pair<int, int>, std::string>(std::pair<int, int>(col, row), num)
                );
                col = pos - 1; // Set the column to the one after the number
            }
        }
    }
    // Check for adjacency of the collected numbers to the collected symbols
    int partSum = 0;
    int gearRatioSum = 0;
    for(const auto& s : symbols) {
        int adjNumsCount = 0;
        int adjNums[8];
        int symCol = s.first.first;
        int symRow = s.first.second;
        char symVal = s.second;
        
        for(const auto& n : numbers) {
            int numCol = n.first.first;
            int numRow = n.first.second;
            std::string numVal = n.second;
            int numLen = numVal.length();

            // Check if some digit of a number is adjacent to some engine symbol
            for(int si = 0; si < numLen; si++) {
                int newCol = numCol + si;
                if((newCol == symCol + 0 && numRow == symRow + 1) ||
                (newCol == symCol + 1 && numRow == symRow + 1) ||
                (newCol == symCol + 1 && numRow == symRow + 0) ||
                (newCol == symCol + 1 && numRow == symRow - 1) ||
                (newCol == symCol + 0 && numRow == symRow - 1) ||
                (newCol == symCol - 1 && numRow == symRow - 1) ||
                (newCol == symCol - 1 && numRow == symRow + 0) ||
                (newCol == symCol - 1 && numRow == symRow + 1)) {
                    int numInt = std::stoi(numVal);
                    adjNums[adjNumsCount++] = numInt; // Collect the number for part 2
                    partSum += numInt; // Add the number for part 1
                    break; // Do not check others because only one digit is needed
                }
            }
        }
        // For part 2
        if(symVal == '*' && adjNumsCount == 2) {
            gearRatioSum += adjNums[0] * adjNums[1];
        }
    }

    std::cout << "Answer 1: " << partSum << std::endl;
    std::cout << "Answer 2: " << gearRatioSum << std::endl;
    
    file.close();
    return 0;
}

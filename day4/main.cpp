
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// For part 2
static int totalCards = 0;
static auto cardMatches = std::vector<int>();

/* One call to this function simulates a process of winning copies of
 * cards below the give one, it is done using recursion. */
static void runCard(int cardIndex) {
    int matches = cardMatches.at(cardIndex);
    totalCards++;
    while(matches)
        runCard(cardIndex + matches--);
}

int main() {
    std::ifstream file("input.txt");
    if(!file.good()) {
        std::cout << "No file called \"input.txt\" found!\n";
        return 1;
    }
    
    std::string line;
    int totalPoints = 0; // Part 1
    // Matches for card being an index + 1, for part 2
    while(std::getline(file, line)) {
        int start = 0;
        while(line[start++] != ':');
        start++; // To start at the number
        // Collect both winning and already-got numbers
        int pos = start;
        bool areWinNumsOver = false;
        auto winNums = std::vector<int>();
        auto gotNums = std::vector<int>();
        while(pos < line.length() - 1) {
            // If a bar is encountered, destination of found numbers is switched
            if(line[pos] == '|') {
                areWinNumsOver = true;
                pos += 2;
                continue;
            }
            // Compute the number
            char tens = line[pos];
            char unities = line[pos + 1];
            if(tens == ' ') tens = '0'; // Space as zero
            int number = (tens - '0') * 10 + (unities - '0');
            // Add it to appropriate container
            if(areWinNumsOver)
                gotNums.push_back(number);
            else
                winNums.push_back(number);
            pos += 3;
        }
        // Find how many matches there are
        int matches = 0;
        for(const int& got : gotNums)
            for(const int& win : winNums)
                if(got == win) matches++;
        // For part 1
        totalPoints += matches == 0 ? 0 : std::pow(2, matches - 1);
        // For part 2
        cardMatches.push_back(matches);
    }
    // Find out how many cards do we have, having applied new rules (part 2).
    // It is done by creating a recursive tree for every card with any amount of matches
    for(int i = 0; i < cardMatches.size(); i++)
        runCard(i);

    std::cout << "Answer 1: " << totalPoints << std::endl;
    std::cout << "Answer 2: " << totalCards << std::endl;

    file.close();
    return 0;
}

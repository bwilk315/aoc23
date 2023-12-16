
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static const int RED_BALLS = 12;
static const int GREEN_BALLS = 13;
static const int BLUE_BALLS = 14;

/* Breaks the given string into parts using specified delimeter. */
std::vector<std::string> split(const std::string& str, char delim) {
    auto parts = std::vector<std::string>();
    std::string current;
    for(const char& ch : str) {
        if(ch == delim) {
            parts.push_back(current);
            current = "";
        } else {
            current += ch;
        }
    }
    parts.push_back(current); // Include the last one
    return parts;
}

/* Returns a string containing only alphabet letters of the original. */
std::string filter(const std::string& str) {
    std::string out = "";
    for(const char& ch : str)
        if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            out += ch;
    return out;
}

int maximum(const std::vector<int>& arr) {
    int max = 0;
    for(const int& n : arr)
        if(n > max) max = n;
    return max;
}

int main() {
    std::ifstream file("input.txt");
    if(!file.good()) {
        std::cout << "No file called \"input.txt\" found!\n";
        return 1;
    }
    
    std::string line;
    int gameId = 0;
    int idSum = 0; // Part 1 answer
    int powerSum = 0; // Part 2 answer
    while(std::getline(file, line)) {
        gameId++;
        auto parts = split(line, ' ');
        // Collect amounts of balls for every grab in the current game
        int amount;
        bool isPossible = true;
        // Containers for storing amounts of balls
        std::vector<int> redAm;
        std::vector<int> greenAm;
        std::vector<int> blueAm;
        for(int i = 2; i < (int)parts.size(); i++) {
            std::string part = parts.at(i);
            if(i % 2 == 0) {
                amount = std::stoi(part);
            } else {
                std::string color = filter(part);
                // Additionally check for game possibility (part 1)
                if(color == "red") {
                    redAm.push_back(amount);
                    if(amount > RED_BALLS) isPossible = false;
                }
                else if(color == "green") {
                    greenAm.push_back(amount);
                    if(amount > GREEN_BALLS) isPossible = false;
                }
                else if(color == "blue") {
                    blueAm.push_back(amount);
                    if(amount > BLUE_BALLS) isPossible = false;
                }
            }
        }
        // Part 1
        if(isPossible) idSum += gameId;
        // Multiply the fewest number of balls of every type for part 2
        powerSum += maximum(redAm) * maximum(greenAm) * maximum(blueAm);
    }
    std::cout << "Answer 1: " << idSum << std::endl;
    std::cout << "Answer 2: " << powerSum << std::endl;
    
    file.close();
    return 0;
}

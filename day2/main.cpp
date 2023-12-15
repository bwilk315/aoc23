
// NEEDS REFACTORING

#include <iostream>
#include <vector>
#include <fstream>

int strsplit(const std::string& str, std::string* buffer) {
    int sLen = str.length();
    int cursor = 0;
    std::string part = "";
    for(int i = 0; i < sLen; i++) {
        if(str[i] == ' ') {
            buffer[cursor++] = part;
            part = ""; 
        } else {
            part += str[i];
        }
    }
    buffer[cursor++] = part;
    return cursor;
}

void strbreak(const std::string& str, int n, std::string pair[2]) {
    pair[0] = "";
    pair[1] = "";
    for(int i = 0; i < str.length(); i++) {
        if(i < n) pair[0] += str[i];
        else pair[1] += str[i];
    }
}

int maximum(std::vector<int> arr) {
    int max = 0;
    for(auto sus : arr)
        if(sus > max)
            max = sus;
    return max;
}

int main() {
    std::ifstream file("input.txt");

    std::string line;
    int index = 0;
    int idSum = 0;
    while(index++ != 100) {
        std::getline(file, line);
        std::string parts[64];
        int count = strsplit(line, parts);

        bool possible = true;
        int amount;
        // Transform vectors into normal ints to get part 1
        std::vector<int> reds;
        std::vector<int> greens;
        std::vector<int> blues;
        for(int i = 2; i < count; i++) {
            std::string part = parts[i];
            if(i % 2 == 0) {
                amount = atoi(part.c_str());
            } else {
                std::string pair[2];
                if(i == count - 1) {
                    pair[0] = part;
                    pair[1] = ";";
                } else {
                    strbreak(part, part.length() - 1, pair);
                }

                if(pair[0] == "red") {
                    reds.push_back(amount);
                } else if(pair[0] == "green") {
                    greens.push_back(amount);
                } else if(pair[0] == "blue") {
                    blues.push_back(amount);
                }
                if(pair[1] == ";") {
                    //std::cout << red << " " << green << " " << blue << std::endl;
                    // if(red > 12 || green > 13 || blue > 14) {
                    //     possible = false;
                    //     break;
                    // }
                    // red = 0;
                    // green = 0;
                    // blue = 0;
                }
            }
        }
        if(possible) {
            //printf("%s\n", line.c_str());
            //printf("Posible[%i]\n", index);
            // for(auto sus : reds) {
            //     printf("red %i\n", sus);
            // }
            // for(auto sus : greens) {
            //     printf("green %i\n", sus);
            // }
            // for(auto sus : blues) {
            //     printf("blue %i\n", sus);
            // }
            int maxRed = maximum(reds);
            int maxGreen = maximum(greens);
            int maxBlue = maximum(blues);
            int power = maxRed * maxGreen * maxBlue;
            //printf("At least %i %i %i\n", maximum(reds), maximum(greens), maximum(blues));
            printf("%s\n", line.c_str());
            //printf("%i\n", index);
            idSum += power;
        }
        //break;
    }
    printf("%i\n", idSum);

    file.close();
}

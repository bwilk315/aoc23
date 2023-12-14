
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

static const char* DIGIT_NAMES[10] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

struct DataPoint {
    int position, value;
};

/* Returns first index of a character starting the <match> string contained inside <string>,
   only the <n>-th occurence is taken into account. If nothing is found -1 is returned. */
int strfind(const char* match, const char* string, int n = 0) {
    int mLen = strlen(match);
    int sLen = strlen(string);
    char buffer[mLen + 1];
    buffer[mLen] = '\0';
    for(int i = 0; i < mLen; i++) buffer[i] = string[i];
    // One more iteration is used for comparing the last time
    for(int i = mLen - 1; i <= sLen; i++) {
        // Shift the buffer to the left and add new character to the right
        if(i != mLen - 1 && i != sLen) {
            for(int j = 0; j != mLen - 1; j++) {
                buffer[j] = buffer[j + 1];
            }
            buffer[mLen - 1] = string[i];
        }
        // Check for match
        if(strcmp(buffer, match) == 0) {
            if(n-- == 0) return i - mLen + 1;
        }
    }
    return -1;
}

/* Saves digits found in string <str> in both text and numeric form, as data points
   to the output buffer <buff>. */
int exctractDigits(const char* str, DataPoint* buff) {
    int sLen = strlen(str);
    // position=start index of the digit in any form, value=actual digit
    auto digits = std::vector<DataPoint>();
    // Search for text digits
    int range = 0;
    while(true) {
        int controlSum = 0; // To check if any digit name is still left
        for(int d = 0; d < 10; d++) {
            int ind = strfind(DIGIT_NAMES[d], str, range);
            controlSum += ind + 1;
            if(ind != -1)
                digits.push_back({ ind, d });
        }
        if(controlSum == 0) break;
        else range++;
    }
    // Search for numeric digits
    for(int i = 0; i < sLen; i++) {
        char ch = str[i];
        if(ch >= 48 && ch <= 57)
            digits.push_back({ i, ch - 48 });
    }
    // Copy found contents into the buffer array provided
    for(int i = 0; i < digits.size(); i++) {
        buff[i] = digits.at(i);
    }
    return digits.size();
}

int main() {
    std::ifstream file("input.txt");
    char buff[128];
    int sum = 0;
    int iter = 0;
    while(file >> buff) {
        // Get all digits (in text and numeric form) and find those nearest and farest
        // based on their indices inside the parent string.
        DataPoint points[64];
        int count = exctractDigits(buff, points);
        DataPoint max = { -1, 0 };
        DataPoint min = { 999999999, 0 };
        for(int i = 0; i < count; i++) {
            DataPoint dp = points[i];
            if(dp.position > max.position) {
                max.position = dp.position;
                max.value = dp.value;
            }
            if(dp.position < min.position) {
                min.position = dp.position;
                min.value = dp.value;
            }
        }
        int calibValue = min.value * 10 + max.value;
        //printf("Test %i: { answer=%i, input=%s }\n", iter++, calibValue, buff);
        sum += calibValue;
    }
    printf("Advent of Code, day 1: %i\n", sum);
    file.close();
}

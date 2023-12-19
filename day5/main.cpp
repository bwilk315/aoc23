
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <limits>

typedef unsigned long long heavy;

struct IncreasingFunction {
	heavy domainStart;
	heavy domainEnd;
	heavy startValue;
};

bool isDigit(const char& ch) {
    return ch >= '0' && ch <= '9';
}

/* Searches for numeric numbers in the given string */
int extractNumbers(const std::string& str, heavy* buff) {
	int index = 0;
	bool started = false;
    buff[index] = 0;
	std::string numStr = "";
    for(const char& ch : str) {
        if(isDigit(ch)) {
            numStr += ch;
            started = true;
        } else if(started) {
            buff[index++] = std::stoull(numStr);
            numStr = "";
            started = false;
        }
    }
	if(!numStr.empty()) {
		buff[index++] = std::stoull(numStr); // Include the last one
	}
	return index;
}

int main() {
    std::ifstream file("input.txt");
    if(!file.good()) {
        std::cout << "No file called \"input.txt\" found!\n";
        return 1;
    }

   	// Load the initial data in form of increasing functions
	std::string line;
    std::getline(file, line);
    heavy rawData[24];
	int rawLength = extractNumbers(line, rawData);
	int scLength = rawLength / 2;
	IncreasingFunction seedsComplexity[scLength];
	for(int i = 0; i < rawLength; i += 2) {
		seedsComplexity[i / 2] = {
			.domainStart = rawData[i],
			.domainEnd 	 = rawData[i] + rawData[i + 1] - 1,
			.startValue  = rawData[i]
		};
	}
	std::getline(file, line);
	std::getline(file, line);

	// Build a mapping process, which will be used to map every seed id to its location fast
	std::vector<IncreasingFunction> complexFunction; // Set of mapping functions (used temporarily)
	std::vector<decltype(complexFunction)> mappingProcess; // Set of complex mapping functions
	while(std::getline(file, line)) {
		// When building a complex mapping function is done, save it and prepare for another one
		if(line == "") {
			mappingProcess.push_back(complexFunction);
			complexFunction.clear();
			std::getline(file, line); // Skip the title
			continue;
		}
		// Save information about another new mapping function
		heavy nums[3];
		extractNumbers(line, nums);
		complexFunction.push_back({
			.domainStart = nums[1],
			.domainEnd 	 = nums[1] + nums[2] - 1,
			.startValue  = nums[0]
		});
	}

	// Use collected information to map every seed to its location, and yes it is done one by one
	heavy minimum = -1;
	const heavy argInterval = 1000000;
	for(int a = 0; a < scLength; a++) {
		IncreasingFunction seedsFunction = seedsComplexity[a];

		std::cout << "Processing the range <" << seedsFunction.domainStart << "; " << seedsFunction.domainEnd << ">\n";
		heavy counter = 0;
		for(heavy b = seedsFunction.domainStart; b <= seedsFunction.domainEnd; b++) {
			heavy argument = b;
			for(const auto& complexFunction : mappingProcess) {
				for(const auto& function : complexFunction) {
					if(argument >= function.domainStart && argument <= function.domainEnd) {
						argument = function.startValue + (argument - function.domainStart);
						break;
					}
				}
			}
			// Compare location to the minimum found
			if(argument < minimum) minimum = argument;

			if(b % argInterval == 0) {
				counter += argInterval;
				std::cout << "[Complexity " << a+1 << "/" << scLength << "] processed " << counter << "/" << (seedsFunction.domainEnd - seedsFunction.domainStart) << " seeds\n";
			}
		}
	}

	std::cout << "Answer 2: " << minimum << std::endl;

    file.close();
	return 0;
}

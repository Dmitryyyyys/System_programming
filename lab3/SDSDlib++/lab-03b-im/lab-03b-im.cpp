#include "DLib.h"
#include <iostream>
#include <cstdlib>
#include<string>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Ne ykazana function!" << std::endl;
        return 1;
    }

    generateArray();
    std::cout << "first 10 nums" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << data[i] << " ";

    }
    std::cout << std::endl;
    std::string functionName = argv[1];
    int target = (argc > 2) ? std::stoi(argv[2]) : 0;

    if (argc == 2) {
        std::cout << "Input num for search: ";
        std::cin >> target;
    }

    int result = -1;
    if (functionName == "iterative") {
        result = iterativeBinarySearch(data, 1024, target);
    }
    else if (functionName == "recursive") {
        result = recursiveBinarySearch(data, 0, 1023, target);
    }
    else {
        std::cerr << "Not available func: " << functionName << std::endl;
        return 1;
    }

    if (result == -1) {
        std::cout << functionName << ": Num not find!" << std::endl;
    }
    else {
        std::cout << functionName << ": Num " << target << " find in pos " << result << "!" << std::endl;
    }

    return 0;
}

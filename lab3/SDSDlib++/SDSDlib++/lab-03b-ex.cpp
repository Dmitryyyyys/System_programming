#include <iostream> 
#include <windows.h>
#include <string>

typedef int (*BinarySearchFunc)(int*, int, int);

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "ne ykazana biblioteka!" << std::endl;
        return 1;
    }

    if (argc < 3) {
        std::cerr << "ne ykazana function!" << std::endl;
        return 1;
    }

    const char* libraryName = argv[1];
    const char* functionName = argv[2];

    HMODULE hLib = LoadLibraryA(libraryName);
    if (!hLib) {
        std::cerr << "tvoya biblioteka ne naidena!" << std::endl;
        return 1;
    }

    BinarySearchFunc binarySearch = (BinarySearchFunc)GetProcAddress(hLib, functionName);
    if (!binarySearch) {
        std::cerr << "Funcntion " << functionName << " not found in biblioteka " << libraryName << "!" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    int data[1024];
    for (int i = 0; i < 1024; i++) data[i] = i * 2;

    std::cout << "First 10 numbers in array: ";
    for (int i = 0; i < 10; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    
    int target;
    std::cout << "Input num: ";
    std::cin >> target;

    int result = binarySearch(data, 1024, target);

    if (result == -1) {
        std::cout << functionName << ": Your num not find !" << std::endl;
    }
    else {
        std::cout << functionName << ": Num " << target << " find on pos " << result << "!" << std::endl;
    }

    FreeLibrary(hLib);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define FILE_SIZE (512 * 1024 * 1024) 
#define VIEW_SIZE (128 * 1024 * 1024) 

void create_file(const char* filename) {
   
    HANDLE hFile = CreateFileA(
        filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to create file. Error: %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    LARGE_INTEGER fileSize;
    fileSize.QuadPart = FILE_SIZE;

   
    if (!SetFilePointerEx(hFile, fileSize, NULL, FILE_BEGIN)) {
        printf("Failed to set file pointer. Error: %lu\n", GetLastError());
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    if (!SetEndOfFile(hFile)) {
        printf("Failed to set end of file. Error: %lu\n", GetLastError());
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    CloseHandle(hFile);
}

int main() {
    
    const char* filename = "mapped_file.txt";

    
    printf("Create file 512 MiB...\n");
    create_file(filename);
    printf("File Create...\n");
    getchar();

    
    HANDLE hFile = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to open file. Error: %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (hMapFile == NULL) {
        printf("Failed to create file mapping. Error: %lu\n", GetLastError());
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    
    printf("Otobrajaem file v pamyat...\n");
    char* mapped = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, FILE_SIZE);
    if (mapped == NULL) {
        printf("Failed to map view of file. Error: %lu\n", GetLastError());
        CloseHandle(hMapFile);
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    printf("File succesfully ptpbrajen v pamyat press Enter to continue...\n");
    getchar();

    
    printf("Predstavlenie na chast 128 MiB...\n");
    for (size_t i = 0; i < VIEW_SIZE; i++) {
        mapped[i] = 'A' + (i % 26);  
    }

    for (size_t i = 0; i < VIEW_SIZE; i++) {
        putchar(mapped[i]);
    }

    printf("\nSome part of file out.Press Enter to continue...\n");
    getchar();

    if (!UnmapViewOfFile(mapped)) {
        printf("Failed to unmap view of file. Error: %lu\n", GetLastError());
    }
    CloseHandle(hMapFile);
    CloseHandle(hFile);

    printf("Resources cleaned. \n");

    return 0;
}

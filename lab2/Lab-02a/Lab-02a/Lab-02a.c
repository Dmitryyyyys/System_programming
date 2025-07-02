#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef UNICODE
#include <windows.h>

#define FILE_NAME "mappedfile.txt"
#define FILE_SIZE 1024
#define VIEW_OFFSET 100
#define VIEW_SIZE 50
void checkMappingFile(void* p){
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery(p, &mbi, sizeof(mbi))) {
        if (mbi.Type == MEM_MAPPED)
        {
            printf("Otobrajen \n");
        }
        else
        {
            printf("Ne otobrajen \n");

        }
    }

}
void create_file() {

    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < FILE_SIZE; i++) {
        fputc('A' + (i % 26), file);
    }
    fclose(file);
}

int main() {
    int x = 24;
    printf("My program, %d\n", x);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hFile, hMap;
    LPVOID pBase, pViewRead, pViewWrite;

    create_file();

    hFile = CreateFile(FILE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        printf("Program end with error %lu\n", error);
        return EXIT_FAILURE;
    }

    hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (!hMap) {
        perror("CreateFileMapping");
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }

    pBase = MapViewOfFile(hMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if (!pBase) {
        perror("MapViewOfFile");
        CloseHandle(hMap);
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }
    checkMappingFile(pBase);
    pViewRead = (LPVOID)((char*)pBase + VIEW_OFFSET);
    printf("File s otstypom  %d razmerom %d:\n", VIEW_OFFSET, VIEW_SIZE);
    fwrite(pViewRead, 1, VIEW_SIZE, stdout);
    printf("\n\n");

    pViewWrite = (LPVOID)((char*)pBase + VIEW_OFFSET + VIEW_SIZE);
    memset(pViewWrite, '\0', VIEW_SIZE);
    if (!FlushViewOfFile(pViewWrite, VIEW_SIZE)) {
        perror("FlushViewOfFile");
    }
    getchar();

    UnmapViewOfFile(pBase);
    CloseHandle(hMap);
    CloseHandle(hFile);
    

    printf("Modification in file will be saved , check %s.\n", FILE_NAME);
    getchar();

    return 0;
    
}

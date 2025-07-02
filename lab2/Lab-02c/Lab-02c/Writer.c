#include <stdio.h>
#include<stdlib.h>
#include<windows.h>

#define MAPPING_NAME "Lab-02"
#define FILE_SIZE (64*1024)
#define TOTAL_ITERATIONS 10

int main()
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, "Global\\Lab02_Mutex");
	if (hMutex == NULL) {
		printf("Err mutex: %lu\n", GetLastError());
		return 1;
	}
	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, FILE_SIZE, MAPPING_NAME);
	int* pData = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, FILE_SIZE);
	for (int i = 0; i < TOTAL_ITERATIONS; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		printf("Pishem dannye na iteracii %d...\n", i + 1);
		for (int j = 0; j < FILE_SIZE / sizeof(int); j++)
		{
			pData[j] = i * FILE_SIZE + j;
		}
		ReleaseMutex(hMutex);
		getchar();
	}
	UnmapViewOfFile(pData);
	CloseHandle(hMapFile);
	CloseHandle(hMutex);

	printf("Program 1 end. \n");
	return 0;
}
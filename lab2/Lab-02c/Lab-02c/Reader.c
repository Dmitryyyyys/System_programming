#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAPPING_NAME "Lab-02"
#define FILE_SIZE (64*1024)
#define TOTAL_ITERATIONS 10

int main() {
	HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, "Global\\Lab02_Mutex");
	if (hMutex == NULL) {
		printf("Error open mutex: %lu\n", GetLastError());
		return 1;
	}
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, MAPPING_NAME);
	int* pData = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, FILE_SIZE);

	for (int i = 0; i < TOTAL_ITERATIONS; i++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		printf("Read data on iteration %d...\n", i + 1);
		for (int j = 0; j < FILE_SIZE / sizeof(int); j++)
		{
			printf("%d", pData[j]);
		}
		printf("\n");
		ReleaseMutex(hMutex);
		getchar();
	}
	UnmapViewOfFile(pData);
	CloseHandle(hMapFile);
	CloseHandle(hMutex);
	printf("Program close. \n");
	return 0;

}
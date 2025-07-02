#include "SDS.H"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int data[1024];

void generateArray() {
	srand(time(NULL));
	for (int i = 0; i < 1024; ++i) data[i] = rand() % 10000;
}

int iterativeBinarySearch(int arr[], int size, int target) {
	int left = 0, right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == target) return mid;
		if (arr[mid] < target) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

int recursiveBinarySearch(int arr[], int left, int right, int target) {
	if (left > right) return -1;
	int mid = left + (right - left) / 2;
	if (arr[mid] == target) return mid;
	if (arr[mid] < target) recursiveBinarySearch(arr, mid + 1, right, target);
	return recursiveBinarySearch(arr, left, mid - 1, target);
}
#ifdef _WIN32
#include <windows.h>
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
FILE *log = fopen("C:/labs/ÑÏ/lab3/log.txt","a");
if (!log) return FALSE;
switch (ul_reason_for_call)
{
case DLL_PROCESS_ATTACH: fprintf(log, "DLL Loaded\n"); break;
case DLL_PROCESS_DETACH: fprintf(log, "DLL Unloaded\n"); break;
}
fclose(log);
return TRUE;
}
#endif
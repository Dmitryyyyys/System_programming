#ifndef SDS_H
#define SDS_H
#ifdef _WIN32
#define		EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern EXPORT int data[1024];
EXPORT void generateArray();
EXPORT int iterativeBinarySearch(int arr[], int size, int target);
EXPORT int recursiveBinarySearch(int arr[], int left, int right, int target);


#endif
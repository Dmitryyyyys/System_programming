#ifdef DLIB_H
#define DLIB_H
#ifdef DLIB_EXPORTS
#define DLIB_API __declspec(dllexport)
#else
#define DLIB_API __declspec(dllimport)
#endif

#include <fstream>

extern "C" DLIB_API extern int data[1024];

extern "C" DLIB_API void generateArray();
DLIB_API int iterativeBinarySearch(int arr[], int size, int target);
DLIB_API int recursiveBinarySearch(int arr[], int left, int right, int target);

#endif
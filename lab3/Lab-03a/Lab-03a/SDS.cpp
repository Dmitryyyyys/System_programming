// SDS.cpp : Определяет функции для статической библиотеки.
//

#include <algorithm>
#include <cstdlib>
#include<ctime>
#include"SDS.h"

int data[1024];

void fnSDS()
{
}

void generateArray() {
	std::srand(std::time(nullptr));
	for (int i = 0; i < 1024; ++i) data[i] = std::rand() % 10000;
	std::sort(data, data + 1024);
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
	if (arr[mid] < target) return recursiveBinarySearch(arr, mid + 1, right, target);
	return recursiveBinarySearch(arr, left, mid - 1, target);


}
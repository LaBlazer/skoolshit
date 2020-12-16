#ifndef __PROGTEST__ 
#define pause system("pause"); 
#else
#define pause; 
#endif

#include <iostream>
#include <ctime>
#include <random>

//template <size_t size>
//void bubble_sort(int(&arr)[size]) {
//	bool cont_flag = true;
//	for (int i = 0; i < (size - 1) && cont_flag == true; i++) {
//		if (arr[j] > arr[j + 1]) {
//			std::swap(arr[j], arr[i + j]);
//			cont_flag = true;
//		}
//		else {
//			cont_flag = false;
//		}
//	}
//}

//template <size_t size>
//void print_array(int(&arr)[size]) {
//	for (int i = 0; i < size; i++) {
//		std::cout << arr[i] << ", ";
//	}
//	std::cout << std::endl;
//}

void fill_array(int *arr, const int N, const int max = 100) {
	for (int i = 0; i < N; i++)
		arr[i] = std::rand() % max;
}

void print_array(const int *arr, const int N) {
	for (int i = 0; i < N; i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

void bubble_sort(int *arr, const int N) {
	bool cont_flag = true;
	while(cont_flag){
		cont_flag = false;
		for (int j = 0; j < (N - 1); j++) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				cont_flag = true;
			}
		}
	}
}

void selection_sort(int *arr, const int N) {
	for (int i = 0; i < N; i++) {
		//find the smallest value and swap it if needed
		int *smallest = &arr[i];
		for (int j = i + 1; j < N; j++)
			if (arr[j] < *smallest)
				smallest = &arr[j];

		std::swap(*smallest, arr[i]);
	}
}

int main(){
	const int N = 25;
	int *arr = new int[N];

	std::srand((unsigned int)std::time(0));

	std::cout << "Array:" << std::endl;
	fill_array(arr, N);
	print_array(arr, N);
	std::cout << "Bubble sort:" << std::endl;
	bubble_sort(arr, N);
	print_array(arr, N);

	std::cout << std::endl;

	std::cout << "Array:" << std::endl;
	fill_array(arr, N);
	print_array(arr, N);
	std::cout << "Selection sort:" << std::endl;
	selection_sort(arr, N);
	print_array(arr, N);

	delete[] arr;
	arr = nullptr;
	pause;
	return 0;
}
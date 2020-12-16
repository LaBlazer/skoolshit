#include <iostream>

template <size_t size>
int find(int(&arr)[size], int val, int start = 0, int end = size) {
	if ((end - start) == 1)
		return -1;
	
	int mid = (start + end) / 2;
	if (arr[mid] > val)
		return find(arr, val, start, mid - 1);
	else if (arr[mid] < val)
		return find(arr, val, mid + 1, end);
	else
		return mid;
}

int main() {
	int data[] = {2, 6, 8, 17, 57, 63, 77, 85, 88, 99};

	int tofind = 63;
	std::cout << tofind << " found on index " << find(data, tofind) << std::endl;

	return 0;
}
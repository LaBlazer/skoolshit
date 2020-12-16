#include <iostream>

template <size_t size>
long sum_arr(int(&arr)[size], unsigned int i = 0) {
	if(i < size)
		return arr[i] + sum_arr(arr, i + 1);
	return 0;
}

int main()
{
	int arr[] = {1, 5, 8, 6, 7, 6, 7, 8};
	std::cout << "Vysledok: " << sum_arr(arr) << std::endl;
	system("pause");
}

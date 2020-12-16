#include <iostream>
#include <ctime>

int find(int *arr, int N, int val) {
	int i = 0;
	for (int i = 0; i < N; i++)
		if (arr[i] == val)
			return i;
	return -1;
}

int main() {
	srand(time(0));
	int N = 5;
	int R = 15;
	int *p = new int[N];
	int **used = new int*[R];

	for (int i = 0; i < R; i++)
		used[i] = nullptr;

	for (int i = 0; i < N; i++) {
		int n = rand() % R;

		if (used[n] == nullptr) {
			p[i] = n;
			used[n] = &p[i];
		}
		else {
			i--;
		}
	}

	for (int i = 0; i < N; i++)
		std::cout << p[i] << "\t";
	
	std::cout << std::endl;

	std::cout << "2 found on: "<< find(p, N, 2) << "\t";

	std::cout << std::endl;

	delete[] used;
	delete[] p;

	return 0;
}
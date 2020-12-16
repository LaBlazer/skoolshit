#include <iostream>

void poly(double *p, int pn, double *q, int qn, double *r) {
	for (; pn >= 0; pn--)
		for (int i = qn; i >= 0; i--) r[pn + i] += p[pn] * q[i];
}

int main() {
	double p[] = { 5, -1, 3 };
	double q[] = { -1, 7, 0, 1 };
	double r[] = { 0, 0, 0, 0, 0, 0 };

	poly(p, 2, q, 3, r);

	std::cout << "Koeficienty: ";
	for(int i : r)
		std::cout << i << " ";
	std::cout << std::endl;

	system("pause");
	return 0;
}
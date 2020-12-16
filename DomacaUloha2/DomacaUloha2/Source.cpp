#include <iostream>
#include <string>
#include <memory>

bool isBinary(char &c) {
	return (c == '0' || c == '1');
}

int main() {
	std::string as, bs;
	std::cout << "Zadejte dve binarni cisla:" << std::endl;
	std::cin >> as >> bs;
	//std::string in
	//std::getline(std::cin, in);
	//int delimeter = in.find(' ');
	//as = in.substr(0, delimeter);
	//bs = in.substr(delimeter + 1, in.size());

	std::string *larger, *smaller;
	unsigned int smallerSize, largerSize, offset;

	if (as.size() > bs.size()) {
		larger = &as;
		largerSize = as.size();
		smaller = &bs;
		smallerSize = bs.size();
	}
	else {
		larger = &bs;
		largerSize = bs.size();
		smaller = &as;
		smallerSize = as.size();
	}

	char *out = new char[largerSize + 2];
	char *stripped = nullptr;
	out[largerSize + 1] = '\0';

	bool carry = false;
	offset = largerSize - smallerSize;

	//loop from the end and add numbers
	for (int i = largerSize - 1; i >= 0; i--) {
		bool a, b;
		if (isBinary(larger->at(i))) {
			b = (larger->at(i) - '0');
			a = false;
			if ((i - (int)offset) >= 0) {
				if (isBinary(smaller->at(i - offset)))
					a = (smaller->at(i - offset) - '0');
				else {
					std::cout << "Nespravny vstup." << std::endl;
					goto exit;
				}
			}

			out[i + 1] = (carry ^ (a^b)) ? '1' : '0';
			carry = ((a || b) && carry) || ((a && b) && !carry);
		}
		else {
			std::cout << "Nespravny vstup." << std::endl;
			goto exit;
		}
	}
	//add the last (or first, depending on how you look at it) number
	out[0] = '0' + carry;

	//now strip the leading 0s
	stripped = out;
	for (unsigned int i = 0; (i < largerSize) && (stripped[0] != '1'); i++)
		stripped += 1;

	std::cout << "Soucet: " << stripped << std::endl;
	
	exit:
	//free the array
	stripped = nullptr;
	delete[] out;
	out = nullptr;
	return 0;
}
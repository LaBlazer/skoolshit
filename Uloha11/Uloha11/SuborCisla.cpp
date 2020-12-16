#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#ifndef __PROGTEST__
#include <iostream>
#include <cstdlib>
#endif

#include <vector>
#include <fstream>
#include <string>

int evenOdd(const char * srcFileName, const char * dstFileName)
{
	std::ifstream ifs(srcFileName);
	if (!ifs.good())
		return 0;

	std::ofstream ofs(dstFileName);
	if (!ofs.good())
		return 0;

	std::vector<int> odd;
	for (std::string row; std::getline(ifs, row);) {
		int i;
		try {
			i = std::stoi(row);
		}
		catch(std::exception e){
			//conversion could not be performed
			return 0;
		}

		if (i % 2 == 0)
			ofs << i << std::endl;
		else
			odd.push_back(i);
	}

	ifs.close();

	for (auto i : odd)
		ofs << i << std::endl;

	ofs.close();
	return 1;
}

#ifndef __PROGTEST__
int main(int argc, char * argv[])
{
	std::cout << evenOdd("0000_in.txt", "out0.txt") << std::endl;
	std::cout << evenOdd("0001_in.txt", "out1.txt") << std::endl;
	std::cout << evenOdd("0002_in.txt", "out2.txt") << std::endl;
	pause();
	return 0;
}
#endif 
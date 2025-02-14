#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>

struct Node {
	bool WalkedRight;
	bool WalkedDown;

	Node() {
		WalkedRight = false;
		WalkedDown = false;
	}
};

enum Dir {
	Up,
	Right,
	Down,
	Left
};

static unsigned int totalPaths = 0;
static auto startTime = std::chrono::steady_clock::now();

template <size_t rows, size_t cols>
void walkPath(Node(&n)[rows][cols], int curX, int curY, float sum, Dir d, std::vector<std::pair<int, int>> steps) {
	switch (d) {
	case Up:
		// /2
		sum /= 2.f;
		curY--;
		n[curY][curX].WalkedDown = true;
		break;
	case Right:
		// +2
		sum += 2.f;
		n[curY][curX].WalkedRight = true;
		curX++;
		break;
	case Down:
		// *2
		sum *= 2.f;
		n[curY][curX].WalkedDown = true;
		curY++;
		break;
	case Left:
		// -2
		sum -= 2.f;
		curX--;
		n[curY][curX].WalkedRight = true;
		break;
	}

	//add current step
	steps.push_back(std::pair<int, int>(curX, curY));
	//std::cout << "Currently at: X" << curX << ", Y" << curY << std::endl;

	if (curX == 4 && curY == 4) {
		//std::cout << "Finished path with value: " << sum << ", steps: " << steps.size() << std::endl;
		totalPaths++;

		if (sum == 0.f) {
			std::cout << "Found valid path with end value: " << sum 
				<< ", steps: " << steps.size() << ", elapsed time: "
				<< std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTime).count()
				<< "s" << std::endl;
			
			for(std::pair<int, int> s : steps) {
				std::cout << "X" << s.first << " Y" << s.second << "|";
			}

			std::cout << std::endl;
			//std::getchar();
		}
	}

	Node nt[5][5];
	std::vector<std::pair<int, int>> st;

	//recurse
	//check if we can go up
	if ((curY - 1) >= 0 && !n[curY - 1][curX].WalkedDown) {
		copyArray(n, nt);
		st = steps;
		walkPath(nt, curX, curY, sum, Dir::Up, st);
	}

	//check if we can go left
	if ((curX - 1) >= 0 && !n[curY][curX - 1].WalkedRight) {
		copyArray(n, nt);
		st = steps;
		walkPath(nt, curX, curY, sum, Dir::Left, st);
	}

	//check if we can go down
	if ((curY + 1) <= 4 && !n[curY][curX].WalkedDown) {
		copyArray(n, nt);
		st = steps;
		walkPath(nt, curX, curY, sum, Dir::Down, st);
	}

	//check if we can go right
	if ((curX + 1) <= 4 && !n[curY][curX].WalkedRight) {
		copyArray(n, nt);
		st = steps;
		walkPath(nt, curX, curY, sum, Dir::Right, st);
	}
}

template <size_t rows, size_t cols>
void copyArray(Node(&in)[rows][cols], Node(&out)[rows][cols]) {
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			out[y][x] = in[y][x];
		}
	}
}

int main()
{
	Node n[5][5];
	std::vector<std::pair<int, int>> steps;

	//populate nodes
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			n[x][y] = Node();
		}
	}

	//walk right 2 times
	int curX = 2;
	int curY = 0;
	float sum = 4.f;
	n[0][0].WalkedRight = true;
	n[0][1].WalkedRight = true;
	steps.push_back(std::pair<int, int>(1, 0));
	steps.push_back(std::pair<int, int>(2, 0));

	std::cout << "Searching for valid paths..." << std::endl;

	//check all other possible combinations
	Node nt[5][5];
	std::vector<std::pair<int, int>> st;

	st = steps;
	copyArray(n, nt);
	walkPath(nt, curX, curY, sum, Dir::Down, st);

	st = steps;
	copyArray(n, nt);
	walkPath(nt, curX, curY, sum, Dir::Right, st);

	std::cout << "Finished searching, total paths: " << totalPaths << ", elapsed time: "
		<< std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTime).count() 
		<< "s" << std::endl;

	std::getchar();
}
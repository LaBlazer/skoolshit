#include <iostream>
#include <vector>

const std::pair<int, int> POSSIBLE_MOVES[8] = { {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2} };
const unsigned int POSSIBLE_MOVES_AMOUNT = sizeof(POSSIBLE_MOVES) / sizeof(POSSIBLE_MOVES[0]);

template <size_t rows, size_t cols>
void copyArray(bool(&in)[rows][cols], bool(&out)[rows][cols]) {
	for (unsigned int x = 0; x < rows; x++)
		for (unsigned int y = 0; y < cols; y++)
			out[x][y] = in[x][y];
}

template <size_t rows, size_t cols>
void walkPath(int curX, int curY, bool(&visited)[rows][cols], std::vector<std::pair<int, int>> steps) {
	const unsigned int FIELD_COUNT = rows * cols;
	//add current step
	steps.push_back({ curX, curY });
	//set current field to visited
	visited[curX][curY] = true;
	//std::cout << "Currently at: X" << curX << ", Y" << curY << ", step: " << steps.size() << std::endl;

	if (steps.size() >= FIELD_COUNT) {
		std::cout << "Found valid path with, steps: " << steps.size() << std::endl;

		for (std::pair<int, int> s : steps)
			std::cout << "X" << s.first << " Y" << s.second << "|";
		std::cout << std::endl;
	}

	bool tempVisited[rows][cols];

	//recurse
	for (unsigned int i = 0; i < POSSIBLE_MOVES_AMOUNT; i++) {
		int nextX = curX + POSSIBLE_MOVES[i].first, nextY = curY + POSSIBLE_MOVES[i].second;
		if (nextX < (int)rows && nextX >= 0 && nextY < (int)cols && nextY >= 0 && visited[nextX][nextY] == false) {
			copyArray(visited, tempVisited);
			walkPath(nextX, nextY, tempVisited, steps);
		}
	}
}

int main()
{
	const unsigned int rows = 4, cols = 3;

	bool visited[rows][cols];
	std::vector<std::pair<int, int>> steps;

	//populate nodes
	for (unsigned int x = 0; x < rows; x++)
		for (unsigned int y = 0; y < cols; y++)
			visited[x][y] = false;

	std::cout << "Searching for valid paths..." << std::endl;

	//check all other possible combinations
	walkPath(3, 2, visited, steps);

	std::cout << "Finished searching..." << std::endl;
}
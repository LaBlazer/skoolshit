#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define IS_VALID(v, x, y) allowed_values[x][y] == allowed_bitfield[v] 

typedef struct SudokuPosition {
	unsigned short possible_number_count = 0;
	unsigned short x;
	unsigned short y;
	SudokuPosition():x(0), y(0), possible_number_count(0) {};
	SudokuPosition(unsigned short x, unsigned short y, unsigned short val):x(x), y(y), possible_number_count(val) {};
} SudokuPosition;

short grid[16][16];
short *rows[16][16];
short *cols[16][16];
short *cells[16][16];
bool completed = false;

unsigned short allowed_values[16][16];
const unsigned short allowed_bitfield[16] = {
	1,
	1 << 1,
	1 << 2,
	1 << 3,
	1 << 4,
	1 << 5,
	1 << 6,
	1 << 7,
	1 << 8,
	1 << 9,
	1 << 10,
	1 << 11,
	1 << 12,
	1 << 13,
	1 << 14,
	1 << 15
};

std::vector<SudokuPosition> best_candidates;

template <size_t rows, size_t cols>
void print_grid(short*(&arr)[rows][cols]) {
	for (unsigned int x = 0; x < rows; x++) {
		for (unsigned int y = 0; y < cols; y++)
			std::cout << (char)(*arr[x][y] != -1 ? ('a' + *arr[x][y]) : ' ') << " | ";
		std::cout << std::endl;
	}
}

template <size_t size>
short find(short*(&arr)[size], short value) {
	for (unsigned short i = 0; i < size; i++)
		if (*arr[i] == value)
			return i;
	return -1;
}

template <typename T, size_t rows, size_t cols>
void copy_array(T(&in)[rows][cols], T(&out)[rows][cols]) {
	for (unsigned int x = 0; x < rows; x++)
		for (unsigned int y = 0; y < cols; y++)
			out[y][x] = in[y][x];
}

void fill_field(unsigned int index) {
	//completed = true;
	//print_grid(rows);
	int x = best_candidates[index].x;
	int y = best_candidates[index].y;

	//if (grid[row][col] == -1) {
		for (int i = 0; i < 16; i++) {
			if ((allowed_values[x][y] & allowed_bitfield[i]) != 0) {
				unsigned short cellnum = ((x / 4) * 4) + (y / 4);
				if (find(cells[cellnum], i) == -1 && find(rows[x], i) == -1 && find(cols[y], i) == -1) {
					grid[x][y] = i;

					//try to fill next field
					if (index < (best_candidates.size() - 1)) {

						fill_field(index + 1);
					}
					else {
						print_grid(rows);
						std::cout << "aaaaaaaaaaaaaaaaa" << std::endl;
					}
				}
			}
		}
		grid[x][y] = -1;
	//}
	//else {
	//	//try to fill next field
	//	if (index < best_candidates.size())
	//		fill_field(index + 1);
	//	else
	//		print_grid(rows);
	//}
}

int main() {

	std::cout << "Zadejte hexadoku:" << std::endl;

	//fill the grid
	std::string row;
	for (int y = 0; y < 16; y++) {
		std::getline(std::cin, row); //ignore the decorative characters row
		std::getline(std::cin, row);
		row.erase(0, 2); //remove the first two chars

		//iterate over all the data and group them into cells, coll and rows		
		for (int x = 0; x < 16; x++) {
			grid[y][x] = row[x * 4] == ' ' ? -1 : row[x * 4] - 'a';

			rows[x][y] = &grid[x][y];
			cols[x][y] = &grid[y][x];

			short cellnum = ((y / 4) * 4) + (x / 4);
			short cellpos = ((y * 4) % 16) + x % 4;
			cells[cellnum][cellpos] = &grid[y][x];
		}
	}
	std::cin.ignore(33, '\n'); //ignore the decorative characters row

	//apply rules and fill the allowed_values field
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			if (grid[x][y] == -1) {
				unsigned short cellnum = ((x / 4) * 4) + (y / 4);
				unsigned short possible_number_count = 0;
				for (int i = 0; i < 16; i++) {
					//weed out numbers occuring multiple times in rows, cols and cells
					if (find(cells[cellnum], i) == -1 && find(rows[x], i) == -1 && find(cols[y], i) == -1) {
						allowed_values[x][y] |= 1 << i;
						possible_number_count++;
					}
				}

				//add our candidate
				best_candidates.push_back(SudokuPosition(x, y, possible_number_count));
			}
		}
	}
	
	for (const auto &c : best_candidates) {
		//if we are certain there is only one possibility
		if (c.possible_number_count == 1) {
			//weed out the possible number from row, col and cell
			int v = 0;
			for (; v < 16; v++) {
				if ((allowed_values[c.x][c.y] & allowed_bitfield[v]) != 0) {
					std::cout << v << std::endl;
					break;
				}
			}

			for (int i = 0; i < 16; i++) {
				if (i != c.x)
					allowed_values[i][c.y] &= ~allowed_bitfield[v];
				if (i != c.y)
					allowed_values[c.x][i] &= ~allowed_bitfield[v];
			}
		}
	}

	//sort the candidates by least possible numbers
	std::sort(best_candidates.begin(), best_candidates.end(), [](SudokuPosition a, SudokuPosition b){
		return a.possible_number_count < b.possible_number_count;
	});

	fill_field(0);

	pause();
	return 0;
}
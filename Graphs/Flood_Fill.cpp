#include<iostream>
#include<vector>
#include<queue>

/*
Flood Fill Algorithm
https://www.techiedelight.com/flood-fill-algorithm/
*/

using Mat_2D_Char = std::vector<std::vector<char>>;
using X_Coordinates = int;
using Y_Coordinates = int;
using Data_t = std::pair<X_Coordinates, Y_Coordinates>;

void flood_fill(Mat_2D_Char& mat, Data_t coordiantes, char replacement_Char) {
	               /* N,  NS, E, SE, S, SW, W, NW*/
	int row_dir[] = { -1, -1, 0,  1, 1,  1,  0,  -1 };
	int col_dir[] = { 0,  1,  1,  1, 0, -1,  -1, -1 };
	std::queue<Data_t> q;
	q.emplace(coordiantes);
	const char targeted_Color = mat[coordiantes.first][coordiantes.second];
	while (!q.empty()) {
		Data_t temp = q.front();
		q.pop();

		for (int i = 0; i < 8; i++) {
			const X_Coordinates xC = temp.first + row_dir[i];
			const Y_Coordinates yC = temp.second + col_dir[i];
			if ((xC > -1 && xC < mat.size()) && 
				(yC > -1 && yC < mat[0].size())) {
				if (mat[xC][yC] == targeted_Color) {
					mat[xC][yC] = replacement_Char;
					q.emplace(Data_t{ xC, yC });
				}
			}
		}
	}
	return;
}

int main() {
	Mat_2D_Char mat = {
		{ 'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G' },
		{ 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X' },
		{ 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X' },
		{ 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X' },
		{ 'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X' },
		{ 'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X' },
		{ 'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X' },
		{ 'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X' },
		{ 'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X' },
		{ 'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
	};

	Data_t start_Coordinates{ 3, 9 };
	flood_fill(mat, start_Coordinates, 'C');
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			_ASSERT(mat[i][j] != 'X');
			std::cout << mat[i][j] << " ";
		}
		std::cout << "\n";
	}
	return 0;
}
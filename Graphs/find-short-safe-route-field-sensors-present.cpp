#include<iostream>
#include<vector>
#include<queue>
#include<bitset>
#include<tuple>

/*
Find shortest safe route in a field with sensors present
https://www.techiedelight.com/find-shortest-safe-route-field-sensors-present/
*/

using Mat_2D_Int = std::vector<std::vector<int>>;
using X_Coordiantes = int;
using Y_Coordinates = int;
using Distance = int;
using Data_t = std::tuple< X_Coordiantes, Y_Coordinates, Distance>;

void display_Mat(Mat_2D_Int& mat) {
	for (size_t i = 0; i < mat.size(); i++) {
		for (size_t j = 0; j < mat[0].size(); j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << "\n";
	}

}

int BFS(Mat_2D_Int& mat) {
	int row_dir[] = {-1,  0, 0, 1};
	int col_dir[] = { 0, -1, 1, 0};
	std::vector<std::bitset<10>> visited(10, std::bitset<10>());
	std::queue<Data_t> q;
	for (size_t i = 0; i < mat.size(); i++) {
		if (mat[i][0]) {
			q.emplace(Data_t{i, 0, 0});
			visited[i].set(0);
		}
	}

	while (!q.empty()) {
		X_Coordiantes x = std::get<0>(q.front());
		Y_Coordinates y = std::get<1>(q.front());
		Distance      d = std::get<2>(q.front());
		q.pop();
		if (y == mat.size() - 1) {
			return d;
		}

		for (int i = 0; i < 4; i++) {
			X_Coordiantes xC = x + row_dir[i];
			X_Coordiantes yC = y + col_dir[i];
			if ((xC > -1 && xC < mat.size()) &&
				(yC > -1 && yC < mat[0].size())) {
				if (mat[xC][yC] && !visited[xC].test(yC)) {
					visited[xC].set(yC);
					q.emplace(Data_t{xC, yC, d+1});
				}
			}

		}
		
	}
	return std::numeric_limits<int>::max();
}

int shortestDistance(Mat_2D_Int &mat) {
	                 //N, NE, E, SE, S, SW, W, NW
	int row_dir[] = { -1, -1, 0, 1,  1, 1, 0, -1 };
	int col_dir[] = {  0, 1,  1, 1,  0, -1, -1, -1};

	const int max_Row = mat.size();
	const int max_Col = mat[0].size();

	std::vector<std::bitset<10>> visited(max_Row, std::bitset<10>());
	for (int i = 0; i < max_Row; i++) {
		for (int j = 0; j < max_Col; j++) {
			if (!mat[i][j] && !visited[i].test(j)) {
				visited[i].set(j);
				for (int k = 0; k < 8; k++) {
					const int xC = i + row_dir[k];
					const int yC = j + col_dir[k];
					if ((xC > -1 && xC < max_Row) &&
						(yC > -1 && yC < max_Col) && 
						!visited[xC].test(yC)) {
						mat[xC][yC] = 0;
						visited[xC].set(yC);
					}
				}
			}
		}
	}

	display_Mat(mat);
	return BFS(mat);
}

int main() {
	Mat_2D_Int mat = {
		{ 0, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	std::cout << shortestDistance(mat) <<"\n";
	return 0;
}
#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<tuple>
#include<bitset>


/*
Shortest Path in a Maze | Lee Algorithm
https://www.techiedelight.com/lee-algorithm-shortest-path-in-a-maze/
*/

using X_Coordinates  = int;
using Y_Coordinates = int;
using XY_Coordinates = std::pair<X_Coordinates, Y_Coordinates>;
using Distance = int;
using Data_t = std::tuple< X_Coordinates, Y_Coordinates, Distance>;
using Mat_2D_Int = std::vector<std::vector<int>>;

int BFS_Shortest_Path(Mat_2D_Int& mat, Mat_2D_Int& res, XY_Coordinates& src, XY_Coordinates& dest) {
	std::queue<Data_t> q;
	std::vector<std::bitset<10>> visited(mat.size(), std::bitset<10>());

	int row_dir[] = { -1, 0, 1,  0 };
	int col_dir[] = { 0, 1, 0, -1 };
	
	q.emplace(Data_t{ src.first, src.second, 0 });
	res[src.first][src.second] = 0;
	visited[src.first].set(src.second);
	
	while (!q.empty()) {
		X_Coordinates x = std::get<0>(q.front());
		Y_Coordinates y = std::get<1>(q.front());
		Distance      d = std::get<2>(q.front());
		q.pop();
		if (x == dest.first && y == dest.second) {
			return d;
		}

		for (int i = 0; i < 4; i++) {
			X_Coordinates xC = x + row_dir[i];
			Y_Coordinates yC = y + col_dir[i];
			if ((xC > -1 && xC < mat.size()) &&
				(yC > -1 && yC < mat[0].size()) &&
				(mat[xC][yC] && !visited[xC].test(yC))) {
				res[xC][yC] = d + 1;
				visited[xC].set(yC);
				q.emplace(Data_t{xC, yC, d+1});
			}

		}
	}

	return std::numeric_limits<int>::min();
}

int main() {
	Mat_2D_Int mat = {
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
	};
	Mat_2D_Int res(mat.size(), std::vector<int>(mat[0].size(), 0));
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[0].size(); j++) {
			if (!mat[i][j]) {
				res[i][j] = -1;
			}
		}
	}

	XY_Coordinates src(0, 0);
	XY_Coordinates dest(9, 9);
	std::cout << "Shortest_Distance: " << BFS_Shortest_Path(mat, res, src, dest) << "\n";

	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[0].size(); j++) {
			std::cout << std::setw(3) << res[i][j] << " ";
		}
		std::cout << "\n";
	}

	return 0;
}
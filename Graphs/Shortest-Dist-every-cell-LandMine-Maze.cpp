#include<iostream>
#include<vector>
#include<tuple>
#include<queue>

/*
Find shortest distance of every cell from landmine in a Maze.
*/

//https://www.techiedelight.com/find-shortest-distance-every-cell-landmine-maze/


using X_Coorodinates = int;
using Y_Coorodinates = int;
using Distance = int;
using Data_t = std::tuple< X_Coorodinates, Y_Coorodinates, Distance>;
using Mat_2D_Char = std::vector<std::vector<char>>;
using Mat_2D_Int  = std::vector<std::vector<int>>;

bool is_Valid_Coordinates(X_Coorodinates x, Y_Coorodinates y, X_Coorodinates max_Row, Y_Coorodinates max_Col) {
	return ((x > -1 && x < max_Row) && (y > -1 && y < max_Col));
}

bool is_Safe(Mat_2D_Char& maze, Mat_2D_Int& res, X_Coorodinates x, Y_Coorodinates y) {
	return (maze[x][y] == 'O' && res[x][y] == -1);
}


void find_Short_Dist(Mat_2D_Char& maze, Mat_2D_Int& res) {
	int row_Dir[] = { -1, 1,  0, 0 };
	int col_Dir[] = { 0,  0, -1, 1 };
	
	const X_Coorodinates row_Max = maze.size();
	const Y_Coorodinates col_Max = maze[0].size();
	std::queue<Data_t> q;
	for (X_Coorodinates x = 0; x < row_Max; x++) {
		for (Y_Coorodinates y = 0; y < col_Max; y++) {
			if (maze[x][y] == 'M') {
				q.emplace(Data_t{x, y, 0});
				res[x][y] = 0;
			}
			else {
				res[x][y] = -1;
			}
		}
	}

	while (!q.empty()) {
		X_Coorodinates x = std::get<0>(q.front());
		Y_Coorodinates y = std::get<1>(q.front());
		Distance d = std::get<2>(q.front());
		q.pop();

		for (int i = 0; i < 4; i++) {
			const X_Coorodinates computed_X = x + row_Dir[i];
			const Y_Coorodinates computed_Y = y + col_Dir[i];
			if (is_Valid_Coordinates(computed_X, computed_Y, row_Max, col_Max)) {
				if (is_Safe(maze, res, computed_X, computed_Y)) {
					q.emplace(Data_t{ computed_X, computed_Y, d + 1 });
					res[computed_X][computed_Y] = d + 1;
				}
			}
		}
	}
	return;
}

int main() {
	Mat_2D_Char maze = {
		{'O', 'M', 'O', 'O', 'X'},
		{'O', 'X', 'X', 'O', 'M'},
		{'O', 'O', 'O', 'O', 'O'},
		{'O', 'X', 'X', 'X', 'O'},
		{'O', 'O', 'M', 'O', 'O'},
		{'O', 'X', 'X', 'M', 'O'}
	};

	Mat_2D_Int res(maze.size(), std::vector<int>(maze[0].size(), 0));
	find_Short_Dist(maze, res);
	for (X_Coorodinates x = 0; x < res.size(); x++) {
		for (Y_Coorodinates y = 0; y < res[0].size(); y++) {
			std::cout << res[x][y] << " ";
		}
		std::cout << "\n";
	}
	return 0;
}

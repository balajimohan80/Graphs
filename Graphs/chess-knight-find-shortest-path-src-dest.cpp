#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<bitset>
#include<tuple>

using X_Coordinates = int;
using Y_Coordinates = int;
using Distance      = int;
using Data_t = std::tuple< X_Coordinates, Y_Coordinates, Distance>;
using XY_Coordinates = std::pair< X_Coordinates, Y_Coordinates>;

/* Board size is input to the program*/
const size_t board_Size = 8;

int find_Shortest_Path_Src_To_Dest(XY_Coordinates& src, XY_Coordinates& dest) {
	// Below arrays details all 8 possible movements
	// for a knight
	const int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
	const int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

	std::vector<std::bitset<board_Size>> visited(board_Size, std::bitset< board_Size>());
	std::queue<Data_t> q;
	q.emplace(Data_t(src.first,src.second,0));
	visited[src.first].set(src.second);
	while (!q.empty()) {
		X_Coordinates x = std::get<0>(q.front());
		Y_Coordinates y = std::get<1>(q.front());
		Distance dist   = std::get<2>(q.front());
		q.pop();

		if (x == dest.first && y == dest.second) {
			return dist;
		}
		
		for (int i = 0; i < 8; i++) {
			const X_Coordinates xC = x + row[i];
			const Y_Coordinates yC = y + col[i];
			if ((xC > -1 && xC < board_Size) &&
				(yC > -1 && yC < board_Size) &&
				!visited[xC].test(yC)) {
				visited[xC].set(yC);
				q.emplace(Data_t{xC, yC, dist+1});
			}

		}
	}
	return std::numeric_limits<int>::min();
}

int main() {
	XY_Coordinates src{3,3};
	XY_Coordinates dest{3,3};
	std::cout << "Kinight Shortest Path: " << find_Shortest_Path_Src_To_Dest(src, dest) << "\n";
	return 0;
}


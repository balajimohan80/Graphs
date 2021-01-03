#include<iostream>
#include<vector>
#include<queue>
#include<bitset>
#include<tuple>
/*
Find shortest path from source to destination in a matrix that satisfies given constraints
https://www.techiedelight.com/find-shortest-path-source-destination-matrix-satisfies-given-constraints/

We can move to location:
1. M[i + M[i][j]][j]
2. M[i - M[i][j]][j]
3. M[i][j + M[i][j]]
4. M[i][j - M[i][j]]
*/


using XY_Cord = std::pair<int, int>;
using Data_t = std::tuple<int, int, int, std::vector<XY_Cord>>;
using Mat_2D = std::vector<std::vector<int>>;

int find_Shortest_Src_To_Dest(Mat_2D& mat, XY_Cord& src, XY_Cord& dest) {
	std::vector<std::bitset<10>> visited(mat.size(), std::bitset<10>(0));
	std::queue<Data_t> q;
	q.emplace(Data_t{ src.first, src.second, 0, std::vector<XY_Cord>{src}});
	visited[src.first].set(src.second);
	int min_Dist = std::numeric_limits<int>::max();
	const int row_Max = mat.size();
	const int col_Max = mat[0].size();
	while (!q.empty()) {
		Data_t temp = q.front();
		int x = std::get<0>(temp);
		int y = std::get<1>(temp);
		int d = std::get<2>(temp);
		std::vector<XY_Cord> vec = std::get<3>(temp);
		q.pop();

		if (dest.first == x && dest.second == y) {
			for (auto& val : vec) {
				std::cout << "(" << val.first << ", " << val.second << ") ";
			}
			std::cout << "\n";
			min_Dist = d;
			break;
		}
		const int first_Constraint  = x + mat[x][y];
		const int second_Constraint = x - mat[x][y];
		const int third_Constraint  = y + mat[x][y];
		const int fourth_Constraint = y - mat[x][y];
		if (first_Constraint > -1 && first_Constraint < col_Max && !visited[first_Constraint].test(y)) {
			std::vector<XY_Cord> temp = vec;
			vec.emplace_back(XY_Cord{ first_Constraint,y });
			q.emplace(Data_t{ first_Constraint,y, d+1, temp});
			visited[first_Constraint].set(y);
		}
		if (second_Constraint > -1 && second_Constraint < col_Max && !visited[second_Constraint].test(y)) {
			std::vector<XY_Cord> temp = vec;
			vec.emplace_back(XY_Cord{ second_Constraint,y });

			q.emplace(Data_t{ second_Constraint,y, d + 1, temp });
			visited[second_Constraint].set(y);
		}
		if (third_Constraint > -1 && third_Constraint < col_Max && !visited[x].test(third_Constraint)) {
			std::vector<XY_Cord> temp = vec;
			vec.emplace_back(XY_Cord{ x,third_Constraint });

			q.emplace(Data_t{ x,third_Constraint, d + 1, temp });
			visited[x].set(third_Constraint);
		}
		if (fourth_Constraint > -1 && fourth_Constraint < col_Max && !visited[x].test(fourth_Constraint)) {
			std::vector<XY_Cord> temp = vec;
			vec.emplace_back(XY_Cord{x,fourth_Constraint});

			q.emplace(Data_t{ x,fourth_Constraint, d + 1, temp });
			visited[x].set(fourth_Constraint);
		}
		
	}

	return min_Dist;
}


int main() {
#if 0
	Mat_2D mat = {
		{ 4, 4, 6, 5, 5, 1, 1, 1, 7, 4 },
		{ 3, 6, 2, 4, 6, 5, 7, 2, 6, 6 },
		{ 1, 3, 6, 1, 1, 1, 7, 1, 4, 5 },
		{ 7, 5, 6, 3, 1, 3, 3, 1, 1, 7 },
		{ 3, 4, 6, 4, 7, 2, 6, 5, 4, 4 },
		{ 3, 2, 5, 1, 2, 5, 1, 2, 3, 4 },
		{ 4, 2, 2, 2, 5, 2, 3, 7, 7, 3 },
		{ 7, 2, 4, 3, 5, 2, 2, 3, 6, 3 },
		{ 5, 1, 4, 2, 6, 4, 6, 7, 3, 7 },
		{ 1, 4, 1, 7, 5, 3, 6, 5, 3, 4 }
	};
#else
	Mat_2D mat = {
		{ 7, 1, 3, 5, 3, 6, 1, 1, 7, 5 },
		{ 2, 3, 6, 1, 1, 6, 6, 6, 1, 2 },
		{ 6, 1, 7, 2, 1, 4, 7, 6, 6, 2 },
		{ 6, 6, 7, 1, 3, 3, 5, 1, 3, 4 },
		{ 5, 5, 6, 1, 5, 4, 6, 1, 7, 4 },
		{ 3, 5, 5, 2, 7, 5, 3, 4, 3, 6 },
		{ 4, 1, 4, 3, 6, 4, 5, 3, 2, 6 },
		{ 4, 4, 1, 7, 4, 3, 3, 1, 4, 2 },
		{ 4, 4, 5, 1, 5, 2, 3, 5, 3, 5 },
		{ 3, 6, 3, 5, 2, 2, 6, 4, 2, 1 }
	};
#endif
	XY_Cord src{ 0,0 };
	XY_Cord dest{ 9,9 };
	std::cout << "Shortest_Path: " << find_Shortest_Src_To_Dest(mat, src, dest) << "\n";
	return 0;
}
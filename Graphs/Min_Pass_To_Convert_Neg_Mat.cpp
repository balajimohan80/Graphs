#include<iostream>
#include<vector>
#include<queue>

/*
Find minimum passes required to convert all negative values in the matrix.
https://www.techiedelight.com/find-minimum-passes-required-convert-negative-values-matrix/
*/

bool is_it_Valid_Mat_Index(const int row_Index, const int col_Index, const int row_Max, const int col_Max) {
	return (row_Index >= 0 && row_Index < row_Max) && (col_Index >= 0 && col_Index < col_Max);
}

int Convert_all_Negative_Val(std::vector<std::vector<int>>& Mat) {
	int col = Mat[0].size();
	int row = Mat.size();
						/*Left, top,  right,  down */
	int adj_Row_Mat[] = {  0,   -1,     0,     1 };
	int adj_Col_Mat[] = { -1,    0,     1,     0};

	using Data_t = std::pair<int, int>;
	std::queue<Data_t> Q;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (Mat[i][j] > 0) {
				Q.emplace(Data_t{ i, j });
			}
		}
	}
	int passes = 0;
	while (!Q.empty()) {
		std::queue<Data_t> q;
		std::swap(Q, q);

		while (!q.empty()) {
			Data_t d = q.front();
			q.pop();
			int row_Index = d.first;
			int col_Index = d.second;
			for (int i = 0; i < 4; i++) {
				if (is_it_Valid_Mat_Index(row_Index + adj_Row_Mat[i], col_Index + adj_Col_Mat[i], row, col) &&
					Mat[row_Index + adj_Row_Mat[i]][col_Index + adj_Col_Mat[i]] < 0) {
					Mat[row_Index + adj_Row_Mat[i]][col_Index + adj_Col_Mat[i]] *= -1;
					Q.emplace(Data_t{ row_Index + adj_Row_Mat[i], col_Index + adj_Col_Mat[i] });
				}
			}

		}
		++passes;
	}
	return passes;
}


int main() {
	std::vector<std::vector<int>> Mat = {
		{ -1, -9,  0, -1,  0 },
		{ -8, -3, -2,  9, -7 },
		{  2,  0,  0, -6,  0 },
		{  0, -7, -3,  5, -4 }
	};

	int min_Pass = Convert_all_Negative_Val(Mat);
	std::cout << "Min_Pass: " << min_Pass << "\n";
	int row = Mat.size();
	int col = Mat[0].size();
#if 1
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < col; j++) {
			std::cout << Mat[i][j] << " ";
		}
		std::cout << "\n";
	}
#endif
	return 0;
}
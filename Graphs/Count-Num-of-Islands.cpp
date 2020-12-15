#include<iostream>
#include<vector>
#include<bitset>
#include<queue>

using Mat_2D_Int = std::vector<std::vector<int>>;

using X_Coordinates = int;
using Y_Coordinates = int;
using Data_t = std::pair<X_Coordinates, Y_Coordinates>;

//Direction travels:               N,  NE, E, SE, S, SW,  W, NW
X_Coordinates row_direction[] = { -1, -1, 0,  1, 1,  1,  0, -1 };
Y_Coordinates col_direction[] = {  0,  1, 1,  1, 0, -1, -1, -1 };


bool is_Safe(X_Coordinates x, Y_Coordinates y, X_Coordinates max_X, Y_Coordinates max_Y) {
    return (x > -1 && x < max_X) && (y > -1 && y < max_Y);
}


void travel_adjacent_Islands(Mat_2D_Int& mat, std::vector<std::bitset<10>>& visited, Mat_2D_Int &res, int isLand_No, Data_t co_ordinates) {
    std::queue<Data_t> q;
    q.emplace(co_ordinates);
    const X_Coordinates x_Max = mat.size();
    const Y_Coordinates y_Max = mat[0].size();
    res[co_ordinates.first][co_ordinates.second] = isLand_No;
    while (!q.empty()) {
        Data_t temp = q.front();
        q.pop();
        for (int i = 0; i < 8; i++) {
            X_Coordinates x = temp.first  + row_direction[i];
            Y_Coordinates y = temp.second + col_direction[i];
            if (is_Safe(x, y, x_Max, y_Max)) {
                if (!visited[x].test(y) && mat[x][y]) {
                    visited[x].set(y);
                    q.emplace(Data_t{ x, y });
                    res[x][y] = isLand_No;
                }
            }
        }
    }
}

int main() {
    Mat_2D_Int mat = {
        { 1, 0, 1, 0, 0, 0, 1, 1, 1, 1 },
        { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 1, 0, 0, 0 },
        { 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 1, 1, 1 },
        { 0, 1, 0, 1, 0, 0, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 1, 1, 1, 0 },
        { 1, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 1, 1, 1 }
    };
    Mat_2D_Int res(mat.size(), std::vector<int>(mat[0].size(), 0));
    const int row_Size = mat.size();
    const int col_Size = mat[0].size();


    std::vector<std::bitset<10>> processed(row_Size);
    int isLandNo = 0;

    for (int x = 0; x < mat.size(); x++) {
        for (int y = 0; y < mat[0].size(); y++) {
            if (mat[x][y] && !processed[x].test(y)) {
                travel_adjacent_Islands(mat, processed, res, ++isLandNo, Data_t{ x,y });
            }
        }
    }
    std::cout << "Total IsLand: " << isLandNo << "\n";
    for (int x = 0; x < mat.size(); x++) {
        for (int y = 0; y < mat[0].size(); y++) {
            std::cout << res[x][y] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
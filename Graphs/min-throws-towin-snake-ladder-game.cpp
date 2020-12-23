#include<iostream>
#include<iomanip>
#include<vector>
#include<unordered_map>
#include<bitset>
#include<queue>

using Data_t = std::pair<int, int>;
const int Max_Moves = 100;
int BFS(std::vector<std::vector<int>>& moves, int src, int dest) {
    std::queue<Data_t> q;
    std::bitset<Max_Moves+1> visited;
    q.emplace(Data_t{ src, 0 });
    int ret = std::numeric_limits<int>::min();
    visited.set(src);
    while (!q.empty()) {
        Data_t temp = q.front();
        q.pop();
        if (temp.first == dest) {
            ret = temp.second;
            break;
        }
        for (auto& pos : moves[temp.first]) {
            if (!visited[pos]) {
                visited.set(pos);
                q.push(Data_t{ pos, temp.second + 1 });
            }
        }

    }
    return ret;
}


int main() {
    const std::unordered_map<int, int> ladder = {
        {1,  38},
        {4,  14},
        {9,  31},
        {21, 42},
        {28, 84},
        {51, 67},
        {72, 91},
        {80, 99},
	};

    const std::unordered_map<int, int> snake = {
        {17,   7},
        {54,  34},
        {62,  19},
        {64,  60},
        {87,  36},
        {93,  73},
        {95,  75},
        {98,  79},
    };

    std::vector<std::vector<int>> moves(Max_Moves);

    int i = 0;
    for (auto& vec : moves) {
        int j = i;
        int k = 1;
        while (k < 7 && k + j < 101) {
            auto it_ladder = ladder.find(k+j);
            auto it_snake = snake.find(k+j);
            vec.push_back(it_ladder != ladder.end() ? it_ladder->second : it_snake != snake.end() ? it_snake->second : k+j);
            k++;
        }
        ++i;
    }

    std::cout << "Min number of Throws:  " << BFS(moves, 0, Max_Moves) << "\n";
    return 0;
}
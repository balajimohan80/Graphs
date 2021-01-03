#include<iostream>
#include<iomanip>
#include<vector>
#include<unordered_map>
#include<bitset>
#include<queue>
#include<tuple>

using Move_Index = int;
using Dist = int;
using Data_t = std::tuple<Move_Index, Dist, std::vector<int>>;

#if 1
const int Max_Moves = 100;
#else
const int Max_Moves = 30;
#endif

int BFS(std::vector<std::vector<int>>& moves, int src, int dest) {
    std::queue<Data_t> q;
    std::bitset<Max_Moves+1> visited;
    q.emplace(Data_t{ src, 0, std::vector<int>{} });
    int ret = std::numeric_limits<int>::min();
    visited.set(src);
    while (!q.empty()) {
        Data_t temp = q.front();
        Move_Index index = std::get<0>(temp);
        Dist d = std::get<1>(temp);
        std::vector<int>& route = std::get<2>(temp); 
        q.pop();
        if (index == dest) {
            std::cout << "Routes: ";
            for (auto val : route) {
                std::cout << val << " ";
            }
            std::cout << "\n";
            ret = d;
            break;
        }
        int curr_Index = index;
        for (int& pos : moves[index]) {
             
            if (!visited[pos]) {
                std::vector<int> save_Route = route;
                visited.set(pos);
                if (pos > curr_Index) {
                    save_Route.push_back(pos);
                    curr_Index = pos;
                }

                q.push(Data_t{ pos, d + 1, save_Route });
            }
        }

    }
    return ret;
}


int main() {
#if 1
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
#else
    const std::unordered_map<int, int> ladder = {
        {2,  21},
        {4,  7},
        {10, 25},
        {19, 28},
    };

    const std::unordered_map<int, int> snake = {
        {26,  1},
        {20,  8},
        {16,  3},
        {18,  6},
    };
#endif
    std::vector<std::vector<int>> moves(Max_Moves);

    int i = 0;
    for (auto& vec : moves) {
        int j = i;
        int k = 1;
        while (k < 7 && k + j < Max_Moves+1) {
            std::unordered_map<int, int>::const_iterator it_ladder = ladder.find(k+j);
            auto it_snake = snake.find(k+j);
            vec.push_back(it_ladder != ladder.end() ? it_ladder->second : it_snake != snake.end() ? it_snake->second : k+j);
            k++;

        }
        ++i;
    }

    std::cout << "Min number of Throws:  " << BFS(moves, 0, Max_Moves) << "\n";
    return 0;
}
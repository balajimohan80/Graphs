#include<iostream>
#include<vector>
#include<bitset>
#include<queue>
#include<bitset>
#include<tuple>
/*
Find the path between given vertices in a directed graph
https://www.techiedelight.com/find-path-between-vertices-directed-graph/
*/

const int Max_Nodes = 8;

using Node = std::pair<int, int>;
using Mat_2D_Int = std::vector<std::vector<int>>;
using Data_t = std::tuple<int, std::vector<int>, std::bitset<Max_Nodes>>;

Mat_2D_Int find_no_of_Path_Between_Src_Dest(std::vector<Node>& nodes, int src, int dest) {
	Mat_2D_Int graph(Max_Nodes);
	for (size_t i = 0; i < nodes.size(); i++) {
		graph[nodes[i].first].emplace_back(nodes[i].second);
	}

	Mat_2D_Int no_of_Paths;
	std::queue<Data_t> q;
	std::bitset<Max_Nodes> bits;
	bits.test(src);
	q.emplace(Data_t{ src, std::vector<int>{src}, bits });
	while (!q.empty()) {
		Data_t temp = q.front();
		int node_no = std::get<0>(temp);
		std::vector<int>& vec = std::get<1>(temp);
		std::bitset<Max_Nodes>& node_Visited = std::get<2>(temp);
		q.pop();
		if (node_no == dest) {
			no_of_Paths.emplace_back(vec);
		}
		else {
			for (auto& val : graph[node_no]) {
				if (!node_Visited.test(val)) {
					std::bitset<Max_Nodes> visited = node_Visited;
					std::vector<int> n = vec;
					visited.set(val);
					n.emplace_back(val);
					q.emplace(Data_t{val, n, visited});
				}
			}
		}
	}

	return no_of_Paths;
}




int main() {
	std::vector<Node> nodes = {
		{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 7}, {3, 4},
		{3, 5}, {4, 3}, {4, 6}, {5, 6}, {6, 7}, {0, 1},
	};

	int src_Node  = 0;
	int dest_Node = 7;
	std::cout << "No of routes between " << src_Node << " & " << dest_Node << ": \n";
	Mat_2D_Int paths = find_no_of_Path_Between_Src_Dest(nodes, src_Node, dest_Node);
	size_t i = 1;
	for (auto& vec : paths) {
		std::cout << i++ << ": ";
		for (auto& val : vec) {
			std::cout << val << " ";
		}
		std::cout << "\n";
	}
	return 0;
}
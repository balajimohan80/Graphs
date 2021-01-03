#include<iostream>
#include<vector>
#include<bitset>
#include<queue>
#include<tuple>

/*
Least cost path in given digraph from given source to destination having exactly m edges
https://www.techiedelight.com/least-cost-path-digraph-source-destination-m-edges/
*/
const int Max_Node = 8;

using Dest_Node = int;
using Src_Node  = int;
using Weight    = int;
using Node_With_Weight = std::pair< Dest_Node, Weight>;
using Edges = std::tuple<Src_Node, Dest_Node, Weight>;
using Q_Data_t = std::tuple<Src_Node, Weight, std::vector<int>, std::bitset<Max_Node>>;

std::vector<int> find_Least_Cost_Path(std::vector<Edges>& edges, Src_Node src, Dest_Node dest) {
	std::vector<std::vector<Node_With_Weight>> graphs(Max_Node);

	for (size_t i = 0; i < edges.size(); i++) {
		graphs[std::get<0>(edges[i])].emplace_back(Node_With_Weight{ std::get<1>(edges[i]) , std::get<2>(edges[i]) });
	}

	std::queue<Q_Data_t> q;
	std::bitset<Max_Node> b(0);
	b.set(src);
	q.emplace(Q_Data_t{ src, 0, std::vector<int>{src},b});

	std::vector<std::pair<Weight, std::vector<int>>> least_Paths;
	while (!q.empty()) {
		Q_Data_t temp = q.front();
		q.pop();
		int &node = std::get<0>(temp);
		int& curr_Weight = std::get<1>(temp);
		std::vector<int>& nodes = std::get<2>(temp);
		std::bitset<Max_Node>& visited_Node = std::get<3>(temp);
		if (node == dest) {
			least_Paths.emplace_back(std::pair<int, std::vector<int>>{curr_Weight, std::move(nodes)});
		}  
		else {
			for (auto& val : graphs[node]) {
				if (!visited_Node.test(val.first)) {
					std::bitset<Max_Node> mark_has_Visited_Node = visited_Node;
					mark_has_Visited_Node.set(val.first);
					std::vector<int> store_node = nodes;
					store_node.emplace_back(val.first);
					q.emplace(Q_Data_t{val.first, curr_Weight + val.second, store_node, mark_has_Visited_Node});
				}
			}
		}
	}

	std::vector<int> ret;
	int min_Cost = std::numeric_limits<int>::max();
	size_t Str_Index = 0;

	for (size_t i = 0; i < least_Paths.size();i++) {
		std::pair<int, std::vector<int>>& val = least_Paths[i];
		std::cout << "Cost: " << val.first << " Routes: ";
		for (auto& n : val.second) {
			std::cout << n << " ";
		}
		std::cout << "\n";
		if (min_Cost > val.first) {
			min_Cost = val.first;
			Str_Index = i;
		}
	}
	std::cout << "Min_Cost: " << min_Cost << "\n";
	return std::move(least_Paths[Str_Index].second);
}

int main() {
	std::vector<Edges> edges = {
		{0, 6, -1}, {0, 1, 5}, {1, 6, 3}, {1, 5, 5}, {1, 2, 7},
		{2, 3, 8}, {3, 4, 10}, {5, 2, -1}, {5, 3, 9}, {5, 4, 1},
		{6, 5, 2}, {7, 6, 9}, {7, 1, 6}
	};

	std::vector<int> routes = find_Least_Cost_Path(edges, 0, 3);
	std::cout << "Min_Cost Routes: ";
	for (auto& val : routes) {
		std::cout << val << " ";
	}
	std::cout << "\n";
	return 0;
}
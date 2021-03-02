#include<iostream>
#include<vector>
#include<unordered_map>

using Disc_Val = int;
using Low_Val = int;
using Disc_Low = std::pair<Disc_Val, Low_Val>;
using DL = std::unordered_map<int, Disc_Low>;
using Adj_List = std::unordered_map<int, std::vector<int>>;
using Visited = std::unordered_map<int, bool>;
using Bridges = std::vector<int>;

int ct = 0;
void find_Bridges_DFS(Adj_List& graph, DL& dl, Visited& v, Bridges &bridge, int curr_Id, int parent_Id) {
	v[curr_Id] = true;
	dl[curr_Id] = Disc_Low{ ct, ct };
	ct++;
	auto& vec = graph[curr_Id];
	for (auto child_node : vec) {
		if (child_node == parent_Id) {
			continue;
		}
		if (v[child_node]) {
			dl[curr_Id].second = std::min(dl[child_node].first, dl[curr_Id].second);
		}
		else {
			find_Bridges_DFS(graph, dl, v, bridge, child_node, curr_Id);
			dl[curr_Id].second = std::min(dl[child_node].second, dl[curr_Id].second);
			if (dl[curr_Id].first < dl[child_node].second) {
				bridge.emplace_back(curr_Id);
				bridge.emplace_back(child_node);
			}
		}
	}
}


int main() {
#if 0
	Adj_List graph = {
		{0, {1,2}},
		{1, {0,2}},
		{2, {0,1,3,5}},
		{3, {2,4}},
		{4, {3}},
		{5, {2,6,8}},
		{6, {5,7}},
		{7, {6,8}},
		{8, {5,7}},
	};
#elif 0
	Adj_List graph = {
		{0, {1,2}},
		{1, {0,2}},
		{2, {0,1,3,4}},
		{3, {2,4}},
		{4, {2,3}},
	};
#elif 0
	Adj_List graph = {
		{0,{1}},
		{1,{0,2,5}},
		{2,{1,3}},
		{3,{2,4,5}},
		{4,{3}},
		{5,{1,3}},
	};
#elif 1
	Adj_List graph = {
		{0, {1,2}},
		{1, {0,2,3,4,6}},
		{2, {0,1}},
		{3, {1,5}},
		{4, {1,5}},
		{5, {3,4}},
		{6, {1}},
	};
#elif 0
	Adj_List graph = {
		{0, {1}},
		{1, {0,2}},
		{2, {1,3}},
		{3, {2}},
	};
#else
	Adj_List graph = {
		{0, {1,2,3}},
		{1, {0,2}},
		{2, {0,1}},
		{3, {0,4}},
		{4, {3}},
	};
#endif
	Visited v;
	DL dl;

	for (auto it = graph.begin(); it != graph.end(); it++) {
		v[it->first] = false;
		dl[it->first] = Disc_Low{ 0, 0 };
	}
	Bridges bridges;
	find_Bridges_DFS(graph, dl, v, bridges, 0, -1);
	std::cout << "Bridges: ";
	for (auto& val : bridges) {
		std::cout << val << " ";
	}
	std::cout << "\n";
	return 0;
}
#include<iostream>
#include<vector>

using Adj_List = std::vector<std::vector<int>>;

//https://leetcode.com/discuss/interview-question/436073/
//https://leetcode.com/problems/critical-connections-in-a-network/

class Articulation_Point {

private:
	const int n;
	Adj_List& graph;
	std::vector<bool> visited;
	std::vector<int> disc;
	std::vector<int> low;
	std::vector<bool> art;
	int outEdge_Count;
	int count;
	void dfs(const int root, int id, int par_id) {
		if (root == par_id) ++outEdge_Count;
		visited[id] = true;
		disc[id] = low[id] = count++;
		auto& vec = graph[id];
		for (int neighbor : vec) {
			if (!visited[neighbor]) {
				dfs(root, neighbor, id);
				low[id] = std::min(low[id], low[neighbor]);
				if (low[neighbor] >= disc[id]) {
					art[id] = true;
				}
			}
			else if (neighbor != par_id) {
				low[id] = std::min(low[id], disc[neighbor]);
			}
		}
	}

public:
	Articulation_Point(const int size, Adj_List& g) :n(size), graph(g),
		visited(n, false), disc(n, -1), low(n, -1), art(n, false), outEdge_Count(0),
		count(0) {

	}

	std::vector<int> find_Articulation() {
		std::vector<int> ret;
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				outEdge_Count = 0;
				dfs(i, i, -1);
				art[i] = (outEdge_Count > 1);
 			}
		}

		for (int i = 0; i < n; i++) {
			if (art[i]) {
				ret.emplace_back(i);
			}
		}
		return ret;
	}
};
using Edge = std::pair<int, int>;
int main() {
#if 0
	const int n = 7;
	std::vector<Edge> edges = {
		{0, 1},
		{0, 2},
		{1, 3},
		{2, 3},
		{2, 5},
		{5, 6},
		{3, 4},
	};
#elif 0
	const int n = 4;
	std::vector<Edge> edges = {
			{0,1},
			{1,2},
			{2,0},
			{1,3},
	};
#elif 0
	const int n = 10;
	//https://leetcode.com/submissions/detail/461816205/
	std::vector<Edge> edges = {
		{1,0},{2,0},{3,0},{4,1},{5,3},{6,1},{7,2},{8,1},{9,6},{9,3},{3,2},{4,2},{7,4},{6,2},{8,3},{4,0},{8,6},{6,5},{6,3},{7,5},
		{8,0},{8,5},{5,4},{2,1},{9,5},{9,7},{9,4},{4,3},
	};
#elif 0
	const int n = 4;
	std::vector<Edge> edges = {
		{0,1},
		{1,2},
		{1,3},
		{0,2}
	};
#elif 1
	const int n = 6;
	std::vector<Edge> edges = {
		{0,1},{1,2},{2,0},{1,3},
		{3,4},{4,5},{5,3},
	};
#endif
	Adj_List graph(n, std::vector<int>{});
	for (int i = 0; i < edges.size(); i++) {
		graph[edges[i].first].emplace_back(edges[i].second);
		graph[edges[i].second].emplace_back(edges[i].first);
	}
	Articulation_Point art_Pt(n, graph);
	std::vector<int> ap = art_Pt.find_Articulation();
	std::cout << "Critical networks: ";
	for (auto val : ap) {
		std::cout << val << " ";
	}
	std::cout << "\n";
	return 0;
}

#include<iostream>
#include<vector>

/*
Articulation Points:
An articulation point is any vertex that after
removal increases the number of connected 
components of the resulting graph.
*/
using Adj_List = std::vector<std::vector<int>>;

int ct = 0;
int outEdgeCount = 0;
void dfs_Articulation_Pt(int root, int id, int par, Adj_List& graph, std::vector<bool>& visited,
	std::vector<int>& disc, std::vector<int>& low, std::vector<bool>& art) {
	if (par == root) {
		++outEdgeCount;
	}
	visited[id] = true;
	disc[id] = low[id] = ct++;
	auto& vec = graph[id];
	for (auto neighbor : vec) {
		if (!visited[neighbor]) {
			dfs_Articulation_Pt(root, neighbor, id, graph, visited, disc,
				low, art);
			low[id] = std::min(low[id], low[neighbor]);
			//We can define "low[neighbor] >= disc[id]", for the sake of clarity
			//we split, articulation point can be found via bridge and cycle
			//Articulation point found via bridge
			if (low[neighbor] > disc[id]) {
				art[id] = true;
			}
			//Articulatio poing found via cycle
			if (low[neighbor] == disc[id]) {
				art[id] = true;
			}
		}
		else if (neighbor != par) {
			low[id] = std::min(low[id], disc[neighbor]);
		}
	}
}
//For Graph figure, please refer:
//https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
int main() {
#if 0
	const int n = 6;
	Adj_List graph = {
		{1},
		{2},
		{3},
		{4},
		{5},
		{0},
	};
#elif 0
	const int n = 5;
	Adj_List graph =
	{
		std::vector<int>{1,2,3},
		std::vector<int>{0,2},
		std::vector<int>{0,1},
		std::vector<int>{0,4},
		std::vector<int>{3}
	};
#elif 1
	const int n = 7;
	Adj_List graph = {
		{1,2},
		{0,2,3,4,6,},
		{0,1},
		{1,5},
		{1,5},
		{3,4},
		{1},
	};
#endif
	std::vector<bool> visited(n, false);
	std::vector<int> disc(n, -1);
	std::vector<int> low(n, -1);
	std::vector<bool> art(n, false);
	for (int i = 0; i < graph.size(); i++) {
		if (!visited[i]) {
			outEdgeCount = 0;
			dfs_Articulation_Pt(i, i, -1, graph, visited, disc, low, art);
			art[i] = (outEdgeCount > 1);
		}
	}
	std::cout << "Articulation pt: ";
	for (int i = 0; i < art.size(); i++) {
		if (art[i]) {
			std::cout << i << " ";
		}
	}
	std::cout << "\n";

	return 0;
}
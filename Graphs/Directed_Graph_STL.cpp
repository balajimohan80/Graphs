#include<iostream>
#include<vector>

struct Edge {
	int src;
	int destination;
};

class Graph {
private:

public:
	std::vector<std::vector<int>> head;
	Graph(std::vector<Edge>& edge, size_t no_of_Vertices) :head(no_of_Vertices) {
		for (size_t i = 0; i < edge.size(); i++) {
			head[edge[i].src].emplace_back(edge[i].destination);
		}
	}
};

int main() {
	std::vector<Edge> edges = { {0, 1}, { 1, 2 }, { 2, 0 }, { 2, 1 },
	{ 3, 2 }, { 4, 5 }, { 5, 4 } };
	Graph graph(edges, 6);
	for (size_t i = 0; i < graph.head.size(); i++) {
		std::cout << i << "---";
		std::vector<int>& val = graph.head[i];
		for (size_t j = 0; j < val.size(); j++) {
			std::cout << val[j] << "->";
		}
		std::cout << "\n";
	}
	return 0;
}
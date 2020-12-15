#include<iostream>
#include<vector>
#include<bitset>
#include<queue>

struct Edge {
	int src;
	int destination;
};

class Graph {
public:
	std::vector<std::vector<int>> heads;

	Graph(std::vector<Edge>& edges, size_t no_Of_Vertices):heads(no_Of_Vertices) {
		
		for (Edge& edge : edges) {
			heads[edge.src].emplace_back(edge.destination);
		}
	}
};

// Number of nodes in the graph
const size_t N = 14;
void BFS_Traversal(Graph& graph, size_t vertices, std::bitset<N>& discovered) {
	std::queue<int> q;
	q.emplace(vertices);
	discovered[vertices] = true;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		std::cout << node << " ";
		auto& edges = graph.heads[node];
		for (int edge_Val : edges) {
			if (!discovered[edge_Val]) {
				discovered[edge_Val] = true;
				q.emplace(edge_Val);
			}
		}
	}
}


int main() {
	// vector of graph edges as per above diagram
	std::vector<Edge> edges = {
		{1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {5, 9},
		{5, 10}, {4, 7}, {4, 8}, {7, 11}, {7, 12}
		// vertex 0, 13 and 14 are single nodes
	};

	

	Graph graph(edges, N);
	
	//Stores vertex is disconvered or not
	std::bitset<N> discovered(false);
	for (size_t i = 0; i < N; i++) {
		if (!discovered[i]) {
			BFS_Traversal(graph, i, discovered);
		}
	}
	std::cout << "\n";
	return 0;
}
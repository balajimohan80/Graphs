#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<tuple>
/*
https://leetcode.com/problems/cheapest-flights-within-k-stops/
Solve using Dijstra's problem
*/

using Edge = std::pair<char, int>;
using Adj_List = std::unordered_map<char, std::vector<Edge>>;
using PQ_Struct = std::tuple<char, int, int>;
using Dist = std::unordered_map<char, int>;
using Flights = std::tuple<char, char, int>;

struct Comp {
	bool operator()(const PQ_Struct& a, const PQ_Struct& b) {
		return std::get<2>(a) > std::get<2>(b);
	}
};

int dijkstras_Algo(Adj_List &graph, char src, char dst, int K) {
	Dist dist;
	for (auto it = graph.begin(); it != graph.end(); it++) {
		dist[it->first] = std::numeric_limits<int>::max();
	}
	auto comp = [&](const PQ_Struct& a, const PQ_Struct& b)->bool {
		return std::get<2>(a) > std::get<2>(b);
	};

	std::priority_queue <PQ_Struct, std::vector<PQ_Struct>, Comp> pq;
	pq.emplace(PQ_Struct{ src, 0, 0 });
	dist[src] = 0;
	while (!pq.empty()) {
		PQ_Struct temp = pq.top();
		pq.pop();
		if (std::get<0>(temp) == dst) return std::get<2>(temp);
		if (std::get<1>(temp) > K) continue;
		std::vector<Edge>& vec = graph[std::get<0>(temp)];
		for (Edge& edge : vec) {
			const int compute_Dist = edge.second + std::get<2>(temp);
			if (std::get<1>(temp)+1 <= K+1) {
				dist[edge.first] = compute_Dist;
				pq.emplace(PQ_Struct{ edge.first, std::get<1>(temp) + 1, compute_Dist });
			}
		}
	}

	return -1;
}

int findCheapestPrice(int n, std::vector<Flights>& flights, char src, char dst, int K) {
	Adj_List graph;
	for (int i = 0; i < n; i++) {
		graph[std::get<0>(flights[i])] = std::vector<Edge>{};
	}

	for (int i = 0; i < flights.size(); i++) {
		graph[std::get<0>(flights[i])].emplace_back(Edge{ std::get<1>(flights[i]), std::get<2>(flights[i]) });
	}

	return dijkstras_Algo(graph, src, dst, K);
}

#include<functional>
#include<algorithm>
int main() {
#if 0
	std::vector<Flights> flights{
		{'A', 'B', 10},
		{'A', 'D', 5 },
		{'B', 'C', 1},
		{'B', 'D', 2},
		{'D', 'B', 3},
		{'D', 'C', 9},
		{'D', 'E', 2},
		{'C', 'E', 4},
		{'E', 'A', 7},
		{'E', 'C', 3},
	};
	int n = 5;
	char src = 'A';
	char dst = 'C';
	int  K = 1;
#elif 0
	std::vector<Flights> flights{
		{'A', 'B', 1},
		{'A', 'C', 5 },
		{'B', 'C', 1},
		{'C', 'D', 1},
	};
	int n = 4;
	char src = 'A';
	char dst = 'D';
	int  K = 1;
#else
	std::vector<std::vector<int>> In = { 
		{3, 4, 4}, {2, 5, 6}, {4, 7, 10}, {9, 6, 5}, {7, 4, 4}, {6, 2, 10},
		{6, 8, 6}, {7, 9, 4}, {1, 5, 4}, {1, 0, 4}, {9, 7, 3}, {7, 0, 5},
		{6, 5, 8}, {1, 7, 6}, {4, 0, 9}, {5, 9, 1}, {8, 7, 3}, {1, 2, 6},
		{4, 1, 5}, {5, 2, 4}, {1, 9, 1}, {7, 8, 10}, {0, 4, 2}, {7, 2, 8} 
	};
	std::unordered_map<int, char> u_Map{
		{0, 'A'},{1, 'B'},{2, 'C'},{3, 'D'},
		{4, 'E'},{5, 'F'},{6, 'G'},{7, 'H'},
		{8, 'I'},{9, 'J'},{10, 'K'},{11, 'L'},
		{12, 'M'},{13, 'N'},{14, 'O'},
	};

	std::vector<Flights> flights(In.size());
	for (size_t i = 0; i < In.size(); i++) {
		flights[i] = Flights{ u_Map[In[i][0]],u_Map[In[i][1]], In[i][2] };
	}
	int n = 10;
	const char src = u_Map[6];
	const char dst = u_Map[0];
	int K = 7;
#endif
	std::cout << "Cheapest price: " << findCheapestPrice(n, flights, src, dst, K) << "\n";

	return 0;
}

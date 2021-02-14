#include<iostream>
#include<unordered_map>
#include<vector>

using Edge = std::pair<int, int>;
using Adj_List = std::unordered_map<char, std::vector<Edge>>;
using Dist = std::unordered_map<char, int>;

Dist BellMan_Ford_Algo(const Adj_List& graph, char start_Node) {
	Dist dist;
	for (auto it = graph.begin(); it != graph.end(); it++) {
		dist[it->first] = std::numeric_limits<int>::max();
	}
	dist[start_Node] = 0;
	for (int i = 0; i < graph.size(); i++) {
		for (auto it = graph.begin(); it != graph.end(); it++) {
			for (auto edge : it->second) {
				if (dist[it->first] + edge.second < dist[edge.first]) {
					dist[edge.first] = dist[it->first] + edge.second;
				}
			}
		}
	}
	
	for (int i = 0; i < graph.size(); i++) {
		for (auto it = graph.begin(); it != graph.end(); it++) {
			for (auto edge : it->second) {
				if (dist[it->first] + edge.second < dist[edge.first]) {
					dist[edge.first] = std::numeric_limits<int>::min();
				}
			}
		}
	}
 	return dist;
}

int main() {
#if 0
	Adj_List graph = {
		{'0', std::vector<Edge>{ {'1',5}}},
		{'1', std::vector<Edge>{ {'2',20}, {'5', 30}, {'6',60}}},
		{'2', std::vector<Edge>{ {'3',10}, {'4', 75}}},
		{'3', std::vector<Edge>{ {'2',-15}}},
		{'4', std::vector<Edge>{ {'9', 100}}},
		{'5', std::vector<Edge>{ {'4',25}, {'6', 5}, {'8',50}}},
		{'6', std::vector<Edge>{ {'7',-50}}},
		{'7', std::vector<Edge>{ {'8',-10}}},
		{'8', std::vector<Edge>{}},
		{'9', std::vector<Edge>{}},
	};
#else
	Adj_List graph = {
		{'0', std::vector<Edge>{ {'1', 1}}},
		{'1', std::vector<Edge>{ {'2', 1},{'5',4},{'6',4}}},
		{'2', std::vector<Edge>{ {'4', 1}}},
		{'3', std::vector<Edge>{ {'2', 1}}},
		{'4', std::vector<Edge>{ {'3', -3}}},
		{'5', std::vector<Edge>{ {'6', 5},{'7',3}}},
		{'6', std::vector<Edge>{ {'7', 4}}},
		{'7', std::vector<Edge>{ }},
		{'8', std::vector<Edge>{ }},
	};
#endif
	BellMan_Ford_Algo(graph, '0');
	return 0;
}
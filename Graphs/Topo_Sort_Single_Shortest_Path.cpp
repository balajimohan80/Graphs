#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>

using Weight = int;
using Edge   = unsigned char;
using Vertice = std::pair<Edge, Weight>;
using Adj_List = std::unordered_map<char, std::vector<Vertice>>;

std::vector<char> Topological_Sort(Adj_List& graph, char start) {
	std::vector<char> order(graph.size(), '\0');
	std::unordered_map<char, int> degree;

	degree[start] = 0;
	for (auto it = graph.begin(); it != graph.end(); it++) {
		for (auto& vertice : it->second) {
			++degree[vertice.first];
		}
	}

	std::queue<char> q;
	for (auto it = degree.begin(); it != degree.end(); it++) {
		if (!it->second) {
			q.emplace(it->first);
		}
	}

	int index = 0;
	while (!q.empty()) {
		char node = q.front();
		q.pop();
		order[index++] = node;
		auto& vec = graph[node];
		for (auto& val : vec) {
			--degree[val.first];
			if (!degree[val.first]) {
				q.emplace(val.first);
			}
		}
	}

	return index == graph.size() ? order : std::vector<char>{};
}

std::vector<char> Single_Shortest_Path(std::vector<char>& ordering, Adj_List& graph, char start) {
	std::unordered_map<char, int> dist;
	for (auto& node : ordering) {
		dist[node] = std::numeric_limits<int>::max();
	}
	
	dist[start] = 0;
	int index = 0;
	while (index < ordering.size()) {
		auto& val = graph[ordering[index]];

		for (auto& vertice : val) {
			const int computed_Weight = dist[ordering[index]] + vertice.second;
			dist[vertice.first] = computed_Weight < dist[vertice.first] ? computed_Weight : dist[vertice.first];
		}
		++index;
	}
	return std::vector<char>{};
}


int main() {
	  Adj_List graph = {
		{'A', std::vector<Vertice>{ {'B',3}, {'C',6}}} ,
		{'B', std::vector<Vertice>{ {'C',4}, {'D',4}, {'E', 11}}},
		{'C', std::vector<Vertice>{ {'D',8}, {'G',11}}},
		{'D', std::vector<Vertice>{ {'E',-4}, {'F',5}, {'G',2}}},
		{'E', std::vector<Vertice>{ {'H',9}}},
		{'F', std::vector<Vertice>{ {'H',1}}},
		{'G', std::vector<Vertice>{ {'H',2}}},
		{'H', std::vector<Vertice>{ }},
	};

	  std::vector<char> order = Topological_Sort(graph, 'A');
	  std::cout << "Topological Sort: ";
	  for (auto val : order) {
		  std::cout << val << " ";
	  }
	  std::cout << "\n";
	  Single_Shortest_Path(order, graph, 'A');

	  return 0;
}


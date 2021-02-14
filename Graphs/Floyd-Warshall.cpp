#include<iostream>
#include<vector>
#include<tuple>
#include<unordered_map>

using Adj_Matrix = std::vector<std::vector<int>>;
using Edges = std::tuple<char, char, int>;

/*
To Better understand Floyd Warshall Theory, 
Please refer: https://www.youtube.com/watch?v=oNI0rf2P9gE&ab_channel=AbdulBari
https://www.udemy.com/course/graph-theory-algorithms/learn/lecture/10794148#overview
*/

//Finding All Pair Shortest Path(APSP) 
//graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])
//Floyd Warshall used a Dynamic Programming approach 
Adj_Matrix floyd_Warshall_APSP(Adj_Matrix& graph, const int n) {
	constexpr int INF = std::numeric_limits<int>::max();
	//next matrix for path reconstruction
	Adj_Matrix next(n, std::vector<int>(n, INF));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] != INF) {
				next[i][j] = j;
			}
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				/* In Adjaceny Matrix or graph, We have added a infinite number where path does not exist between 2 nodes.
				   But during artihmetic operation with infinite number, value of inifnite will change.
				   But we want: INF + anynumber = INF
				   Using conditional operator to maintain infnite value.
				*/
				//graph[i][k] + graph[k][j]
				const int num = graph[i][k] == INF ? INF : graph[k][j] == INF ? INF : graph[i][k] + graph[k][j];
				//graph[i][j] = graph[i][j] < num ? graph[i][j] : num;
				if (num < graph[i][j]) {
					graph[i][j] = num;
					//Store Intermediate nodes
					next[i][j] = next[i][k];
				}
			}
		}
	}
	return next;
}

std::string path_travel(int src, int dest, std::unordered_map<int, char>& Id_Char, Adj_Matrix& reconstructed_Path) {
	std::string ret;
	ret += Id_Char[src];
	while (src != dest) {
		src = reconstructed_Path[src][dest];
		ret += Id_Char[src];
	}
	return ret;
}

int main() {
	std::vector<Edges> Input = {
		{ 'a','b',3 },
		{ 'a','d',7 },
		{ 'b','c',2 },
		{ 'b','a',8 },
		{ 'c','a',5 },
		{ 'c','d',1 },
		{ 'd','a',2 },
	};

	std::unordered_map<char, int> Id_Map = { {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}};
	std::unordered_map<int, char> Id_Char = { {0,'a'}, {1, 'b'}, {2,'c'}, {3, 'd'} };
	const int n = Id_Map.size();
	Adj_Matrix graph(n, std::vector<int>(n, std::numeric_limits<int>::max()));
	for (Edges& e : Input) {
		graph[Id_Map[std::get<0>(e)]][Id_Map[std::get<1>(e)]] = std::get<2>(e);
	}
	for (size_t i = 0; i < n; i++) {
		graph[i][i] = 0;
	}
	Adj_Matrix reconstructed_Path = floyd_Warshall_APSP(graph, n);
	
	int i = 0;
	//(n(n+1)) / 2
	while (i < n) {
		for (int j = i+1; j < n; j++) {
			std::cout << path_travel(i, j, Id_Char, reconstructed_Path) << "\n";
			std::cout << path_travel(j, i, Id_Char, reconstructed_Path) << "\n";
		}
		std::cout << "----------------------\n";
		i++;
	}
	return 0;
}
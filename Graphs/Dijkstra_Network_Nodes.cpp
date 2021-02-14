#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
/*
https://leetcode.com/problems/network-delay-time/
You are given a network of n nodes, labeled from 1 to n. You are also given times, 
a list of travel times as directed edges times[i] = (ui, vi, wi), 
where: 
ui is the source node. 
vi is the target node. 
wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. 
Return the time it takes for all the n nodes to receive the signal. 
If it is impossible for all the n nodes to receive the signal, return -1.
*/


using Node   = int;
using Weight = int;
using Edge   = std::pair<Node, Weight>;
using Adj_List = std::unordered_map<int, std::vector<Edge>>;

template<typename T, typename Compare>
class B_Indexed_PQ {
private:
	const int max_Q_Size;
	int curr_Q_Size;
	std::vector<int> parent;
	std::vector<int> child;
	std::vector<int> im;
	std::vector<int> pm;
	std::vector<T> vals;
	Compare predicate;
	inline bool less(int i, int j) const {
		return predicate(static_cast<const T&>(vals[im[i]]), static_cast<const T&>(vals[im[j]]));
	}

	void swap(int i, int j) {
		pm[im[i]] = j;
		pm[im[j]] = i;
		int tmp = im[i];
		im[i] = im[j];
		im[j] = tmp;
	}

	void swim(int index) {
		while (parent[index] > -1 && less(index, parent[index])) {
			swap(index, parent[index]);
			index = parent[index];
		}
	}

	void sink(int index) {
		do {
			int from = child[index];
			int to = curr_Q_Size > from + 2 ? from + 2 : curr_Q_Size;
			int smaller = index;
			while (from < to) {
				if (less(from, smaller)) {
					smaller = from;
				}
				++from;
			}
			if (smaller != index) {
				swap(smaller, index);
				index = smaller;
			}
			else {
				break;
			}
		} while (1);
	}

	void delete_Obj(int index) {
		--curr_Q_Size;
		swap(index, curr_Q_Size);
		sink(index);
		swim(index);
		//vals[im[curr_Q_Size]] = 0;
		pm[im[curr_Q_Size]] = -1;
		im[curr_Q_Size] = -1;
	}


public:
	B_Indexed_PQ(const int max_Q) :max_Q_Size(max_Q), curr_Q_Size(0),
		parent(max_Q), child(max_Q), im(max_Q), pm(max_Q),
		vals(max_Q) {
		for (int i = 0; i < max_Q_Size; i++) {
			parent[i] = (i - 1) / 2;
			child[i] = (2 * i) + 1;
			im[i] = -1;
			pm[i] = -1;
			//vals[i] = 0;
		}
	}

	void insert(int key_Index, T& val) {
		pm[key_Index]   = curr_Q_Size;
		im[curr_Q_Size] = key_Index;
		vals[key_Index] = val;
		swim(curr_Q_Size++);
	}

	bool empty() {
		return curr_Q_Size == 0;
	}

	T front() {
		T t;
		if (curr_Q_Size) {
			return vals[im[0]];
		}
		return t;
	}
 
	void pop() {
		if (curr_Q_Size) {
			return delete_Obj(0);
		}
	}

	void update(int key_Index, T& val) {
		int index = pm[key_Index];
		vals[key_Index] = val;
		sink(index);
		swim(index);
	}

	void decrease_Key(int key_Index, T& val) {
		if (predicate(static_cast<const T&>(val) , static_cast<const T&>(vals[key_Index]))) {
			vals[key_Index] = val;
			swim(pm[key_Index]);
		}
	}

	void increase_Key(int key_Index, T& val) {
		if (predicate(static_cast<const T&>(vals[key_Index]) , static_cast<const T&>(val))) {
			vals[key_Index] = val;
			sink(pm[key_Index]);
		}
	}
};

#if 1
class Comp {
public:
	bool operator()(const Edge& a, const Edge& b) const {
		return (a.second > b.second);
	}
};


using Distance   = std::unordered_map<int, int>;
using Short_Path = std::unordered_map<int, int>;
Short_Path  Dijkstra_Shortest_Path_Lazy(Adj_List& graph, int start) {
	//B_Indexed_PQ<Ed ge, Comp> pq(graph.size());
	std::priority_queue<Edge, std::vector<Edge>, Comp> pq;
	Distance dist;
	Short_Path s_Path;
	//Initialized Distance 
	for (auto it = graph.begin(); it != graph.end(); it++) {
		dist[it->first] = std::numeric_limits<int>::max();
	}

	dist[start] = 0;
	pq.emplace(Edge{ start, 0 });
//	node_Shortest_Path[start] = 0;
	while (!pq.empty()) {
		Edge edge = pq.top();
		pq.pop();
		if (edge.second > dist[edge.first]) continue;
		for (auto node : graph[edge.first]) {
			const int calc_Dist = node.second + edge.second;
			if (calc_Dist < dist[node.first]) {
				dist[node.first] = calc_Dist;
				pq.emplace(Edge{node.first, calc_Dist});
				s_Path[node.first] = edge.first;
				std::cout << "node: " << node.first << " Seq: " << edge.first << "\n";
			}
		}
	}

	return s_Path;
}

std::vector<int> find_Shortest_Path(Adj_List &graph, int start, int end) {
	Short_Path path = Dijkstra_Shortest_Path_Lazy(graph, start);
	if (path.find(end) == path.end()) {
		return std::vector<int>{};
	}
	else {
		std::vector<int> ret;
		ret.emplace_back(end);
		while (end != start) {
			end = path[end];
			ret.emplace_back(end);
		}
		return ret;
	}
}

 int main() {
#if 0
	 std::vector<std::vector<int>> times = {
		 {2,1,1},
		 {2,3,1},
		 {3,4,1}
	};
	int n = 4; //nodes
	int k = 2; //start node
#else
	 std::vector<std::vector<int>> times = {
		 {1,2,10},{1,3,4}, {1,6,20},
		 {2,4,2},{2,6,5},
		 {3,2,5}, {3,4,10},
		 {4,5,10},
		 {6,5,4},
	 };
	 int n = 6; //nodes
	 int k = 2; //start node
	 int l = 5; //end node
#endif
	Adj_List list;
	for (int i = 1; i <= n; i++) {
		list[i] = std::vector<Edge>{};
	}

	for (int i = 0; i < times.size(); i++) {
		list[times[i][0]].push_back(Edge{times[i][1], times[i][2]});
	}
	std::vector<int> route = find_Shortest_Path(list, k, l);
	std::cout << "Shortest_Route: ";
	for (auto val : route) {
		std::cout << val << " ";
	}
	std::cout << "\n";
	return 0;
 }

#elif 0
using Data_t = std::pair<std::string, int>;
class Comp {
public:
	bool operator()(const Data_t& a, const Data_t& b) const {
		return (a.second < b.second);
	}
}; 

int main() {
	std::vector<Data_t> in = {
		{"California", 50},
		{"NewYork", 49},
		{"Washington", 5},
		{"Oregon", 2},
		{"Nevada", 15},
		{"Florida", 1}
	};

	B_Indexed_PQ<Data_t, Comp> pq(in.size());

	//Insert in Random order
	pq.insert(5, in[5]);
	pq.insert(4, in[4]);
	pq.insert(1, in[1]);
	pq.insert(3, in[3]);
	pq.insert(0, in[3]);

	Data_t t = { "Cali", 1 };
	pq.update(0, t);
	in[1].second = 5;
	pq.decrease_Key(1, in[1]);
	in[5].second = 100;
	pq.increase_Key(5, in[5]);
	pq.insert(2, in[2]);

	while (!pq.empty()) {
		Data_t t = pq.front();
		pq.pop();
		std::cout << t.first << " " << t.second << "\n";

	}
	return 0;
}

#if 0
int main() {
	std::string name = { "omnamashivayashivayanamaom" };
	B_Indexed_PQ<char> b_PQ(name.length());

	for (size_t i = 0; i < name.length(); i++) {
		b_PQ.insert(i, name[i]);
	}
	std::cout << "PQ: ";
	for (size_t i = 0; i < name.length(); i++) {
		char ch = b_PQ.front();
		b_PQ.pop();
		std::cout << ch << " ";
	}
	std::cout << "\n";
	std::string name_2 = { "binary" };
	for (size_t i = 0; i < name_2.length(); i++) {
		b_PQ.insert(i, name_2[i]);
	}
	char ch = 'c';
	b_PQ.decrease_Key(name_2.length() - 1, ch);
	ch = 'z';
	b_PQ.increase_Key(3, ch);
	ch = 'd';
	b_PQ.update(4, ch);
	std::cout << "PQ: ";
	for (size_t i = 0; i < name_2.length(); i++) {
		char ch = b_PQ.front();
		b_PQ.pop();
		std::cout << ch << " ";
	}

	std::cout << "\n";
	return 0;
}
#endif

#endif
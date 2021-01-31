#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
/*
	Topological Sort or Ordering:
	Topological ordering of a graph is a linear ordering of its vertices such that 
	every directed edge  UV from vertex U to vertex V, U Comes before V in the ordering.
	A Toplogical Sort is possible only if the graph has no cyclic, Directed Acyclic Graph(DAG).
	
	//https://leetcode.com/problems/sequence-reconstruction/
	Most impressed problem
*/

bool sequenceReconstruction(std::vector<int>& org, std::vector<std::vector<int>>& seqs) {
	std::unordered_map<int, std::vector<int>> adj_List;
	std::unordered_map<int, int> deg;

	for (auto& seq : seqs) {
		for (size_t i = 1; i < seq.size(); i++) {
			auto& val_Vec = adj_List[seq[i - 1]];
			bool found = false;
			for (auto val : val_Vec) {
				if (val == seq[i]) {
					found = true;
					break;
				}
			}
			if (!found) {
				val_Vec.emplace_back(seq[i]);
			}
		}
		if (adj_List.find(seq[seq.size() - 1]) == adj_List.end()) {
			adj_List[seq[seq.size() - 1]] = std::vector<int>{};
		}
	}
	if (adj_List.size() != org.size()) return false;
	for (auto it = adj_List.begin(); it != adj_List.end(); it++) {
		auto& vec = it->second;
		if (deg.find(it->first) == deg.end()) {
			deg[it->first] = 0;
		}
		for (auto val : vec) {
			++deg[val];
		}
	}

	std::queue<int> q;
	int count = 0;
	for (auto it = deg.begin(); it != deg.end(); it++) {
		if (!it->second) {
			++count;
			q.emplace(it->first);
		}
	}
	if (count > 1) return false;
	std::vector<int> order(deg.size(), 0);
	int index = 0;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		if (node != org[index]) {
			return false;
		}
		order[index++] = node;
		auto& vec = adj_List[node];
		int count = 0;
		for (auto c_Node : vec) {
			deg[c_Node]--;
			if (!deg[c_Node]) {
				++count;
				q.emplace(c_Node);
			}
		}
		if (count > 1) {
			return false;
		}
	}

	return index == org.size();

}

int main() {
	std::vector<int>  org = { 4, 1, 5, 2, 6, 3 };
	std::vector<std::vector<int>> seqs = {
		{5, 2, 6, 3},
		{4, 1, 5, 2}
	};
	sequenceReconstruction(org, seqs);
	return 0;
}

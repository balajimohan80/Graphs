#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<stack>


/*
To get more information on Isomorphic, please refer following material:
https://www.udemy.com/course/graph-theory-algorithms/learn/lecture/18603278#announcements
https://www.udemy.com/course/graph-theory-algorithms/learn/lecture/18603284#announcements
*/

using Adj_List = std::vector<std::vector<int>>;

class TreeNode {
public:
	int id;
	TreeNode* parent;
	std::vector<TreeNode*> child;
	TreeNode(int id) {
		this->id = id;
		this->parent = nullptr;
	}
	TreeNode(int id, TreeNode *par) {
		this->id = id;
		this->parent = par;
	}
};

std::vector<int> find_Center_of_Tree(Adj_List& graph) {
	const int max_Node = graph.size();
	std::vector<int> degree(max_Node, 0);
	std::vector<int> leaves;
	for (size_t i = 0; i < max_Node; i++) {
		degree[i] = graph[i].size();
		if (degree[i] < 2) {
			leaves.emplace_back(i);
		}
	}
	int count = leaves.size();
	while (count < max_Node) {
		std::vector<int> new_leaves;
		for (auto child_node : leaves) {
			for (auto node : graph[child_node]) {
				--degree[node];
				if (degree[node] == 1) {
					new_leaves.emplace_back(node);
				}
			}
			degree[child_node] = 0;
		}
		leaves = new_leaves;
		count += leaves.size();
	}
	return leaves;
}

TreeNode* build_RootTree(Adj_List& graph, int node) {
	TreeNode* root = new TreeNode(node);
	std::queue<TreeNode*> q;
	q.emplace(root);
	while (!q.empty()) {
		TreeNode* temp_Node = q.front();
		q.pop();
		for (auto node_id : graph[temp_Node->id]) {
			if (temp_Node->parent && temp_Node->parent->id == node_id) {
				continue;
			}
			TreeNode* new_Node = new TreeNode(node_id, temp_Node);
			temp_Node->child.emplace_back(new_Node);
			q.emplace(new_Node);
		}
	}
	return root;
}

void display_Rooted_Tree(TreeNode* root) {
	std::queue<TreeNode*> q;
	q.emplace(root);
	while (!q.empty()) {
		root = q.front();
		q.pop();
		if (!root->parent) {
			std::cout << "---------Root: " << root->id << "--------------\n";
		}
		else {
			std::cout << "------Parent: " << root->id << "---------------\n";
		}

		std::cout << "child: ";
		for (auto node : root->child) {
			std::cout << node->id << " ";
			q.emplace(node);
		}
		std::cout << "\n";
	}
}

void delete_Tree(TreeNode* root) {
	std::stack<TreeNode*> st;
	st.emplace(root);
	while (!st.empty()) {
		root = st.top();
		st.pop();
		for (auto child_Node : root->child) {
			st.emplace(child_Node);
		}
		delete root;
	}
}

std::string encode_Tree(TreeNode* root) {
	if (!root) return "";
	std::vector<std::string> encoded_Str;
	for (auto c_Node : root->child) {
		encoded_Str.emplace_back(encode_Tree(c_Node));
	}
	std::string str_Builder;
	for (auto& str : encoded_Str) {
		str_Builder += str;
	}
	return "(" + str_Builder + ")";
}

bool is_Trees_Are_Isomorphic(Adj_List& graph1, Adj_List& graph2) {
	std::vector<int> center_Graph_1 = find_Center_of_Tree(graph1);
	TreeNode* rooted_Graph_1 = build_RootTree(graph1, center_Graph_1[0]);
	std::string encoded_Graph_1 = encode_Tree(rooted_Graph_1);
	delete_Tree(rooted_Graph_1);

	std::vector<int> center_Graph_2 = find_Center_of_Tree(graph2);
	for (auto c1 : center_Graph_2) {
		TreeNode* rooted_Graph_2 = build_RootTree(graph2, c1);
		std::string encoded_Graph_2 = encode_Tree(rooted_Graph_2);
		delete_Tree(rooted_Graph_2);
		if (encoded_Graph_2 == encoded_Graph_1) {
			return true;
		}
	}
	return false;
}

int main() {
#if 0
	Adj_List graph_1 = {
		{1},
		{0,2},
		{1,3,6},
		{2,4,5},
		{3},
		{3},
		{2,7,8},
		{6},
		{6}
	};
	std::vector<int> center = find_Center_of_Tree(graph_1);
	std::cout << "Center of Graph1: ";
	for (size_t i = 0; i < center.size(); i++)
		std::cout << center[i] << " ";
	std::cout << "\n";
	TreeNode* root_Tree = build_RootTree(graph_1, center[0]);
	display_Rooted_Tree(root_Tree);
	std::string str = encode_Tree(root_Tree);
	std::cout << "Encoded Str: " << str << "\n";
	delete_Tree(root_Tree);
#else
	Adj_List graph1 = {
		{2},
		{2},
		{0,1,3},
		{2,4},
		{3}
	};
	
	Adj_List graph2 = {
			{1},
			{0,3,2},
			{1,4},
			{1},
			{2}
	};

	std::cout << "Isomorphic: " << is_Trees_Are_Isomorphic(graph1, graph2) << "\n";
	std::cout << "Isomorphic: " << is_Trees_Are_Isomorphic(graph2, graph1) << "\n";


	std::vector<int> center_g1 = find_Center_of_Tree(graph1);
	std::vector<int> center_g2 = find_Center_of_Tree(graph2);
	std::cout << "Center of Graph1: ";
	for (size_t i = 0; i < center_g1.size(); i++) {
		std::cout << "-----------" << center_g1[i] << "-------------\n";
		TreeNode* root = build_RootTree(graph1, center_g1[i]);
		display_Rooted_Tree(root);
		std::cout << "Encoded: " << encode_Tree(root) << "\n";
		delete_Tree(root);
	}
	std::cout << "\n";
	std::cout << "##################################################\n";
	std::cout << "Center of Graph2: ";
	for (size_t i = 0; i < center_g2.size(); i++) {
		std::cout << "------------" << center_g2[i] << "--------------\n";
		TreeNode* root = build_RootTree(graph2, center_g2[i]);
		display_Rooted_Tree(root);
		std::cout << "Encoded: " << encode_Tree(root) << "\n";
		delete_Tree(root);
	}

	std::cout << "\n";

#endif
	return 0;
}


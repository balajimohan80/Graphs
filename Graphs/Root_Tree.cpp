#include<iostream>
#include<vector>
#include<queue>
#include<stack>

class TreeNode {
public:
	int id;
	TreeNode* parent;
	std::vector<TreeNode*> child;
	TreeNode(int node_Id) {
		this->id = node_Id;
		this->parent = nullptr;
	}
	TreeNode(int node_Id, TreeNode* par) {
		this->id = node_Id;
		this->parent = par;
	}
};

using Adj_List = std::vector<std::vector<int>>;
using Q_Data_t = std::pair<TreeNode*, TreeNode*>;

TreeNode* buildTree(std::vector<std::vector<int>>& graph, int node) {
	std::queue<TreeNode*> q;
	TreeNode* root = new TreeNode(node);
	q.emplace(root);
	while (!q.empty()) {
		TreeNode* temp_Node = q.front();
		q.pop();
		for (auto node_val : graph[temp_Node->id]) {
			if (temp_Node->parent != nullptr && node_val == temp_Node->parent->id) {
				continue;
			} 
			TreeNode *c = new TreeNode(node_val, temp_Node);
			temp_Node->child.emplace_back(c);
			q.emplace(c);
		}
	}
	return root;
}

void display_Tree(TreeNode* root) {
	std::queue<TreeNode*> q;
	q.emplace(root);
	while (!q.empty()) {
		TreeNode* r = q.front();
		q.pop();
		if (r->parent != nullptr) {
			std::cout << "---------Parent: " << r->parent->id << " ID: " << r->id <<"---------------\n";
			std::cout << "Child: ";
		}
		else {
			std::cout << "------------Root Tree: " << r->id <<"------------\n";
			std::cout << "Child: ";
		}
		for (auto node : r->child) {
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
		for (auto child_node : root->child) {
			st.emplace(child_node);
		}
		std::cout << "Delete Node: " << root->id << "\n";
		delete root;
	}
}

int main() {
	Adj_List graph = {
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
	TreeNode* root_Tree = buildTree(graph, 6);
	display_Tree(root_Tree);
	delete_Tree(root_Tree);
	return 0;
}
#include<iostream>
#include<vector>

/*
To get clear definition about Center of Tree:
Please refer following link:
https://www.udemy.com/course/graph-theory-algorithms/learn/lecture/18603268#announcements
*/

using Mat_2D_Char = std::vector<std::vector<char>>;

std::vector<char> find_Center_of_Tree(const Mat_2D_Char& adj_List) {
	const int n_Nodes = adj_List.size();
	std::vector<int> degrees(n_Nodes, 0);
	std::vector<char> leaves;
	
	for (size_t i = 0; i < n_Nodes; i++) {
		degrees[i] = adj_List[i].size();
		if (degrees[i] < 2) {
			degrees[i] = 0;
			leaves.emplace_back('a' + i);
		}
	}

	int count = leaves.size();
	while (count < n_Nodes) {
		std::vector<char> new_Leaves;
#if 0
		std::cout << "leaves: ";
		for (auto node : leaves) {
			std::cout << node << " ";
		}
		std::cout << "\n";
#endif
		for (auto node : leaves) {
			const int index = node - 'a';
			for (auto neighboring_Node : adj_List[index]) {
				degrees[neighboring_Node - 'a'] -= 1;
				if (degrees[neighboring_Node - 'a'] == 1) {
					new_Leaves.emplace_back(neighboring_Node);
				}
			}
			degrees[index] = 0;
		}
		count += new_Leaves.size();
		leaves = new_Leaves;
	}
	return leaves;
}

int main() {
#if 0
	//Please refer: https://www.tutorialspoint.com/centers-of-a-tree
	//Problem-1
	Mat_2D_Char adj_List = {
		{'b'}, 
		{'a','c'}, 
		{'b','f','d','g'}, 
		{'c','e'},
		{'d'},
		{'c'},
		{'c'}
	};
#elif 0
	//https://www.udemy.com/course/graph-theory-algorithms/learn/lecture/18603268#announcements
	Mat_2D_Char adj_List = {
		{'b'},  // a
		{'a','c'}, // b
		{'b','j','g','d'}, // c
		{'c','e','f'}, // d
		{'d'}, //e
		{'d'}, //f
		{'c','h','i'}, //g
		{'g'}, //h
		{'g'}, //i
		{'c'}, //j
	};
#else
	//https://www.udemy.com/course/graph-theory-algorithms/learn/lecture/18603268#announcements
	Mat_2D_Char adj_List = {
		{'b'},  // a
		{'d','a','e'}, // b
		{'d'}, // c
		{'c','b','g','h'}, // d
		{'b','i'}, //e
		{'e'}, //f
		{'d','j'}, //g
		{'d'}, //h
		{'e'}, //i
		{'g'}, //j
	};
#endif
	std::vector<char> center_Of_Tree = find_Center_of_Tree(adj_List);
	std::cout << "Center of Tree: ";
	for (auto val : center_Of_Tree) {
		std::cout << val << " ";
	}
	std::cout << "\n";
	return 0;
}
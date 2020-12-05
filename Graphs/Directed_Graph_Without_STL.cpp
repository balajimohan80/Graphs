#include<iostream>

/* Data Structure to store ADJACENT list nodes */
struct Node {
	int val;
	Node* next;
};

struct Edge {
	int src, dest;
};

//Directed Graph
class Graph {
private:
	//Fucntion to allocate new node of Adjacency list
	Node* getAdjListNode(int dest, Node* head) {
		Node* newNode = new Node;
		newNode->val = dest;
		newNode->next = head;
		return newNode;
	}

	//Number of Nodes in Graph
	size_t no_Of_Nodes;
public:
	//An array of pointers to Node to represent adjacency list
	Node** head;

	Graph(Edge edges[], size_t no_Of_Edges, size_t no_Of_Vertces) {
		head = new Node * [no_Of_Vertces]();
		this->no_Of_Nodes = no_Of_Vertces;

		for (size_t i = 0; i < no_Of_Vertces; i++) {
			head[i] = nullptr;
		}

		for (size_t i = 0; i < no_Of_Edges; i++) {
			int src  = edges[i].src;
			int dest = edges[i].dest;
			//Insert in the Beginning
			Node* newNode = getAdjListNode(dest, head[src]);

			//Point head pointer to new Node
			head[src] = newNode;
			/* 
				Only for undirected Graph
				newNode = getAdjListNode(src, head[dest]);

				 // change head pointer to point to the new node
				 head[dest] = newNode;
			*/
		}
	}

	~Graph() {
		for (size_t i = 0; i < no_Of_Nodes; i++) {
			delete[] head[i];
		}

		delete[]head;
	}
};


void printList(Node* ptr) {
	while (ptr != nullptr) {
		std::cout << " -> " << ptr->val << " ";
		ptr = ptr->next;
	}
	std::cout << "\n";
}

/*
	Please refer Image representation:
	//https://www.techiedelight.com/graph-implementation-c-without-using-stl/
*/

int main() {
	Edge edges[] = {
		//Pair (X,Y) represents edge from X to Y
		{0, 1}, { 1, 2 }, { 2, 0 }, { 2, 1 },
		{ 3, 2 }, { 4, 5 }, { 5, 4 }
	};

	//Number of Vertices in the GRAPH
	size_t v = 6;

	//Calculate number of Edges
	size_t e = sizeof(edges) / sizeof(edges[0]);

	// construct graph
	Graph graph(edges, e, v);

	// print adjacency list representation of graph
	for (int i = 0; i < v; i++)
	{
		// print given vertex
		std::cout << i << " --";

		// print all its neighboring vertices
		printList(graph.head[i]);
	}


	return 0;
}



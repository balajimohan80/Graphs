#include<iostream>
#include<vector>
#include<string>


/*
For Theory, please refer following video:
https://www.youtube.com/watch?v=HqPJF2L5h9U&ab_channel=AbdulBari
*/

/* min-heap*/
template<typename T>
class Priority_Q {
private:
	std::vector<T> heap;
	size_t q_Size;

	inline int left_Child(int index) const {
		return (index << 1) + 1;
	}

	inline int right_Child(int index) const {
		return (index << 1) + 2;
	}

	inline int parent(int index) const {
		return (index - 1) >> 1;
	}


	void swim(int index) {
		while (parent(index) > -1 && heap[index] < heap[parent(index)]) {
			std::swap(heap[index], heap[parent(index)]);
			index = parent(index);
		}
	}

	void sink(int index) {
		while (left_Child(index) < q_Size) {
			int smaller;
			if (heap[index] > heap[left_Child(index)]) {
				smaller = left_Child(index);
			}
			else {
				smaller = index;
			}

			if (right_Child(index) < q_Size && heap[smaller] > heap[right_Child(index)]) {
				smaller = right_Child(index);
			}

			if (smaller != index) {
				std::swap(heap[smaller], heap[index]);
				index = smaller;
			}
			else {
				break;
			}
		}
	}

	void build_heap() {
		int count = (q_Size - 1) >> 1;
		while (count > -1) {
			sink(count);
			--count;
		}
		return;
	}

public:
	Priority_Q(std::vector<T>& data):heap(data), q_Size(data.size()) {
		build_heap();
	}

	Priority_Q() {};

	void insert(T& data) {
		heap.push_back(data);
		swim(q_Size);
		++q_Size;
	}

	bool pop(T& data) {
		if (q_Size) {
			data = heap[0];
			heap[0] = heap[q_Size-1];
			heap.pop_back();
			--q_Size;
			sink(0);
			return true;
		}
		return false;
	}

	size_t size() const {
		return q_Size;
	}

};

int main() {
	std::string input_str = { "omnamashivaya" };
	//std::string input_str = { "balaji" };
	std::vector<char> data;

	for (size_t i = 0; i < input_str.length(); i++) {
		data.push_back(input_str[i]);
	}

	Priority_Q<char> pq(data);
	std::string in = { "shivayanamaom" };
//	std::string in = {"ijalab"};
	for (size_t i = 0; i < input_str.length(); i++) {
		pq.insert(in[i]);
	}

	std::cout << "-------PQ-----\n";
	while (pq.size()) {
		char data;
		pq.pop(data);
		std::cout << data << " ";
	}
	std::cout << "\n";
	return 0;
}
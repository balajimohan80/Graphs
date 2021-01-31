#include<iostream>
#include<vector>
#include<string>

#if 0
template<typename T>
class Indexed_Priority_Q {
private:
	const size_t max_Q_Size;
	std::vector<int> pm;
	std::vector<T>   val;
	//Since Q size is already pre-determined.
	//Let pre-compute parent & child index.
	std::vector<int> parent;
	std::vector<int> child;
	//Q Current Size
	size_t curr_Q_Size;
	

	inline int left_Child(int index) const {
		return (index << 1) + 1;
	}

	inline int right_Child(int index) const {
		return (index << 1) + 2;
	}

	inline int parent(int index) const {
		return (index - 1) >> 1;
	}

	void swap(int x, int y) {
		int temp = pm[x];
		pm[x] = pm[y];
		pm[y] = temp;
	}

	void swim(int index) {
		while (parent(index) > -1 && val[pm[index]] < val[pm[parent(index)]]) {
			swap(index, parent(index));
			index = parent(index);
		}
	}

	void sink(int index) {
		while (left_Child(index) < q_Size) {
			int smaller = index;
			if (val[pm[index] > val[pm[left_Child(index)]]]) {
				smaller = left_Child(index);
			}
			
			if (right_Child(index) < q_Size && val[pm[smaller]] > val[pm[right_Child(index)]]) {
				smaller = right_Child(index);
			}

			if (smaller != index) {
				swap(index, smaller);
				index = smaller;
			}
			else {
				break;
			}
		}
	}

public:
	Indexed_Priority_Q(size_t max_Size):max_Q_Size(max_Size),
		pm(max_Size, 0),val(max_Size),parent(max_Size), 
		child(max_Size),curr_Q_Size(0) {
		for (size_t i = 0; i < max_Q_Size; i++) {
			parent[i] = (i - 1) >> 1;
			child[i]  = (i << 1) + 1;
			pm[i]     = -1;
		}
	}

	void insert(int key_Index, T& data) {
		pm.emplace_back(key_Index);
		val.emplace_back(data);
		swim(q_Size);
		++q_Size;
	}

	bool empty() {
		return q_Size == 0;
	}
	T top() {
		return val[pm[0]];
	}

	bool pop(T& data) {
		if (q_Size) {
			data = val[pm[0]];
		//	val.erase(val.begin() + pm[0]);
		//	pm[0] = pm[q_Size - 1];
		//	pm.pop_back();
			swap(0, q_Size - 1);
			--q_Size;
			sink(0);
			pm[q_Size ] = -1;
			return true;
		}
		return false;
	}
};
#endif

template<typename T>
class MinIndexedDHeap {

	// Current number of elements in the heap.
	int sz_;

	// Maximum number of elements in the heap.
	int N_;

	// The degree of every node in the heap.
	int D_;

	// Lookup arrays to track the child/parent indexes of each node.
	std::vector<int> child_, parent_;

	// The Position Map (pm) maps Key Indexes (ki) to where the position of that
	// key is represented in the priority queue in the domain [0, sz).
	std::vector<int> pm_;

	// The Inverse Map (im) stores the indexes of the keys in the range
	// [0, sz) which make up the priority queue. It should be noted that
	// 'im' and 'pm' are inverses of each other, so: pm[im[i]] = im[pm[i]] = i
	std::vector<int> im_;

	// The values associated with the keys. It is very important  to note
	// that this array is indexed by the key indexes (aka 'ki').
	std::vector<T> values_;

public:
	MinIndexedDHeap(const MinIndexedDHeap&) = delete;
	MinIndexedDHeap& operator=(MinIndexedDHeap const&) = delete;

	// Initializes a D-ary heap with a maximum capacity of maxSize.
	MinIndexedDHeap(int degree, int maxSize) {
		if (maxSize <= 0) throw std::invalid_argument("maxSize <= 0");

		sz_ = 0;
		D_ = std::max(2, degree);
		N_ = std::max(D_ + 1, maxSize);

		im_.resize(N_, 0);
		pm_.resize(N_, 0);
		child_.resize(N_, 0);
		parent_.resize(N_, 0);
		values_.resize(N_);

		for (int i = 0; i < N_; i++) {
			parent_[i] = (i - 1) / D_;
			child_[i] = i * D_ + 1;
			pm_[i] = im_[i] = -1;
		}
	}

	~MinIndexedDHeap() {
	}

	int size() {
		return sz_;
	}

	bool isEmpty() {
		return sz_ == 0;
	}

	bool contains(int ki) {
		keyInBoundsOrThrow(ki);
		return pm_[ki] != -1;
	}

	int peekMinKeyIndex() {
		isNotEmptyOrThrow();
		return im_[0];
	}

	int pollMinKeyIndex() {
		int minki = peekMinKeyIndex();
		deleteObj(minki);
		return minki;
	}

	T peekMinValue() {
		isNotEmptyOrThrow();
		return values_[im_[0]];
	}

	T pollMinValue() {
		T minValue = peekMinValue();
		deleteObj(peekMinKeyIndex());
		return minValue;
	}

	void insert(int ki, T value) {
		if (contains(ki)) throw std::invalid_argument("index already exists; received: " + ki);
		valueNotNullOrThrow(value);
		pm_[ki] = sz_;
		im_[sz_] = ki;
		values_[ki] = value;
		swim(sz_++);
	}

	T valueOf(int ki) {
		keyExistsOrThrow(ki);
		return values_[ki];
	}

	void deleteObj(int ki) {
		keyExistsOrThrow(ki);
		int i = pm_[ki];
		swap(i, --sz_);
		sink(i);
		swim(i);
		//    values_.erase(values_.begin()+ki);
		values_[ki] = 0;
		pm_[ki] = -1;
		im_[sz_] = -1;
	}

	T update(int ki, T value) {
		keyExistsAndValueNotNullOrThrow(ki, value);
		int i = pm_[ki];
		T oldValue = values_[ki];
		values_[ki] = value;
		sink(i);
		swim(i);
		return oldValue;
	}

	// Strictly decreases the value associated with 'ki' to 'value'
	void decrease(int ki, T value) {
		keyExistsAndValueNotNullOrThrow(ki, value);
		if (value < values_[ki]) {
			values_[ki] = value;
			swim(pm_[ki]);
		}
	}

	// Strictly increases the value associated with 'ki' to 'value'
	void increase(int ki, T value) {
		keyExistsAndValueNotNullOrThrow(ki, value);
		if (values_[ki] < value) {
			values_[ki] = value;
			sink(pm_[ki]);
		}
	}

	// Helper functions

	void sink(int i) {
		for (int j = minChild(i); j != -1; ) {
			swap(i, j);
			i = j;
			j = minChild(i);
		}
	}

	void swim(int i) {
		while (less(i , parent_[i])) {
			swap(i, parent_[i]);
			i = parent_[i];
		}
	}

	// From the parent node at index i find the minimum child below it
	int minChild(int i) {
		int index = -1, from = child_[i], to = std::min(sz_, from + D_);
		for (int j = from; j < to; j++) if (less(j, i)) index = i = j;
		return index;
	}

	void swap(int i, int j) {
		pm_[im_[j]] = i;
		pm_[im_[i]] = j;
		int tmp = im_[i];
		im_[i] = im_[j];
		im_[j] = tmp;
	}

	// Tests if the value of node i < node j
	bool less(int i, int j) {
		return (values_[im_[i]] < values_[im_[j]]);
	}

	std::string toString() {
		std::stringstream str;
		for (int i = 0; i < sz_; i++) {
			str << im_[i];
			str << " ";
		}
		return str.str();
	}

	// Helper functions to make the code more readable.
	void isNotEmptyOrThrow() {
		if (isEmpty()) throw std::invalid_argument("Priority queue underflow");
	}

	void keyExistsAndValueNotNullOrThrow(int ki, T value) {
		keyExistsOrThrow(ki);
		valueNotNullOrThrow(value);
	}

	void keyExistsOrThrow(int ki) {
		if (!contains(ki)) throw std::out_of_range("Index does not exist; received: " + ki);
	}

	void valueNotNullOrThrow(T value) {
		// if (value == nullptr) throw std::invalid_argument("value cannot be null");
	}

	void keyInBoundsOrThrow(int ki) {
		if (ki < 0 || ki >= N_)
			throw std::invalid_argument("Key index out of bounds; received: " + ki);
	}
};

#if 0
int main() {
	Indexed_Priority_Q<char> pq;
	std::string name = "balaji";
	std::vector<char> n;
	for (size_t i = 0; i < name.length(); i++) {
		n.emplace_back(name[i]);
	}

	for (size_t i = 0; i < n.size(); i++) {
		pq.insert(i, n[i]);
	}

	for (size_t i = 0; i < n.size(); i++) {
		char ch;
		pq.pop(ch);
		std::cout << ch << " ";
	}
	std::cout << "\n";
	std::string om = "onnamashivayashivayanamaom";
	for (size_t i = 0; i < om.length(); i++) {
		pq.insert(i + n.size(), om[i]);
	}
	for (size_t i = 0; i < om.length(); i++) {
		char ch;
		pq.pop(ch);
		std::cout << ch << " ";
	}
	std::cout << "\n";
	return 0;
}
#else
int main() {
#if 1
	std::string name = "onnamashivayashivayanamaom";
	MinIndexedDHeap<char> pq(2, name.length());
	for (size_t i = 0; i < name.size(); i++) {
		pq.insert(i, name[i]);
	}
	std::cout << "PQ: ";
	for (size_t i = 0; i < name.size(); i++) {
		std::cout << name[pq.peekMinKeyIndex()] << " ";
		pq.pollMinValue();
	}
	std::cout << "\n";

#else
	std::string om = "onnamashivayashivayanamaom";
	std::string name = "balaji";
	
	MinIndexedDHeap<char> pq(2,om.length() + name.length());
	for (size_t i = 0; i < name.size(); i++) {
		pq.insert(i, name[i]);
	}
	std::cout << "PQ: ";
	for (size_t i = 0; i < name.size(); i++) {
		std::cout << name[pq.peekMinKeyIndex()]<< " ";
		pq.pollMinValue();
	}
	std::cout << "\n";
	for (size_t i = 0; i < om.length(); i++) {
		pq.insert(i , om[i]);
	}

	for (size_t i = 0; i < om.size(); i++) {
		std::cout << pq.pollMinValue() << " ";
		
	}
	std::cout << "\n";
#endif
	return 0;
}
#endif

#include<iostream>
#include<vector>

#if 0
template<typename T>
class B_Indexed_PQ {
private:
	const size_t max_Q_Size;
	int curr_Q_Size;
	std::vector<int> parent;
	std::vector<int> child;
	std::vector<T> vals;
	std::vector<int> im;

	inline bool lesser(int i, int j) const {
		return vals[im[i]] < vals[im[j]];
	}

	void swap(int i, int j) {
		int tmp = im[i];
		im[i] = im[j];
		im[j] = tmp;
	}

	void swim(int index) {
		while (parent[index] > -1 && lesser(index, parent[index])) {
			swap(index, parent[index]);
			index = parent[index];
		}
	}

	void sink(int index) {
		do {
		int from = child[index];
		int to = curr_Q_Size < from + 2 ? curr_Q_Size : from+2;
		int smaller = index;
			while (from < to) {
				if (lesser(from, smaller)) {
					smaller = from;
				}
				from++;
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

public:
	B_Indexed_PQ(const size_t max_Size) :max_Q_Size(max_Size),
		curr_Q_Size(0), parent(max_Q_Size), child(max_Q_Size), vals(max_Q_Size),
		im(max_Q_Size) {
		for (int i = 0; i < max_Q_Size; i++) {
			parent[i] = (i - 1) / 2;
			child[i]  = (2 * i) + 1 ;
			vals[i]   = 0;
			im[i]     = -1;
		}
	}

	void insert(int key_Index, T& data) {
		im[curr_Q_Size] = key_Index;
		vals[key_Index] = data;
		swim(curr_Q_Size++);
	}

	bool pop(T& data) {
		if (curr_Q_Size) {
			--curr_Q_Size;
			data = vals[im[0]];
			vals[im[0]] = 0;
			im[0] = im[curr_Q_Size];
			im[curr_Q_Size] = -1;
			sink(0);
			return true;
		}
		return false;
	}

	T top() {
		if (curr_Q_Size) {
			return vals[im[0]];
		}
	}
};
#endif


template<typename T>
class B_Indexed_PQ {
private:
	const int max_Q_Sz;
	int curr_Q_Sz;
	std::vector<int> parent;
	std::vector<int> child;
	std::vector<int> im;
	std::vector<int> pm;
	std::vector<T>  vals;
	

	inline bool lesser(int i, int j) const {
		return vals[im[i]] < vals[im[j]];
	}

	void swap(int i, int j) {
		pm[im[i]] = j;
		pm[im[j]] = i;
		int tmp = im[i];
		im[i] = im[j];
		im[j] = tmp;
	}

	void swim(int index) {
		while (parent[index] > -1 && lesser(index, parent[index])) {
			swap(index, parent[index]);
			index = parent[index];
		}
	}

	void sink(int index) {
		do
		{
			int from = child[index];
			int to = curr_Q_Sz > from + 2 ? from + 2 : curr_Q_Sz;
			int smaller = index;
			while (from < to) {
				if (lesser(from, smaller)) {
					smaller = from;
				}
				++from;
			}
			if (smaller != index) {
				swap(index, smaller);
				index = smaller;
			}
			else {
				break;
			}
		} while (1);
	}

	void delete_Obj(int index) {
		--curr_Q_Sz;
		pm[im[index]]= -1;
		vals[im[index]] = 0;
		im[index] = im[curr_Q_Sz];
		sink(index);
		swim(index);
		im[curr_Q_Sz] = -1;
	}

public:
	B_Indexed_PQ(const int size) :max_Q_Sz(size), curr_Q_Sz(0),
		parent(size), child(size), im(size), pm(size),vals(size) {
		for (int i = 0; i < max_Q_Sz; i++) {
			parent[i] = (i - 1) / 2;
			child[i]  = (2 * i) + 1;
			im[i] = -1;
			pm[i] = -1;
			vals[i] = 0;
		}
	}

	void insert(int key_Index, T& val) {
		pm[key_Index] = curr_Q_Sz;
		im[curr_Q_Sz] = key_Index;
		vals[curr_Q_Sz] = val;
		swim(curr_Q_Sz++);
	}

	bool pop(T& val) {
		if (curr_Q_Sz > 0) {
			val = vals[im[0]];
			delete_Obj(0);
			return true;
		}
		return false;
	}

	void update(int key_Index, T& val) {
		vals[key_Index] = val;
		sink(pm[key_Index]);
		swim(pm[key_Index]);
	}

	void increase_Key(int key_Index, T& val) {
		if (vals[key_Index] < val) {
			vals[key_Index] = val;
			sink(pm[key_Index]);
		}
	}

	void decrease_Key(int key_Index, T& val) {
		if (val < vals[key_Index]) {
			vals[key_Index] = val;
			swim(pm[key_Index]);
		}
	}
};


int main() {
#if 1
	std::string name = { "omnamashivayashivayanamaom" };
	B_Indexed_PQ<char> b_PQ(name.length());

	for (size_t i = 0; i < name.length(); i++) {
		b_PQ.insert(i, name[i]);
	}
	std::cout << "PQ: ";
	for (size_t i = 0; i < name.length(); i++) {
		char ch;
		b_PQ.pop(ch);
		std::cout << ch << " ";
	}
	std::cout << "\n";
	std::string name_2 = { "balaji" };
#else
	std::string name_2 = { "balaji" };
	B_Indexed_PQ<char> b_PQ(name_2.length());
#endif
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
		char ch;
		b_PQ.pop(ch);
		std::cout << ch << " ";
	}

	std::cout << "\n";
	return 0;
}

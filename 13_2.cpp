#include<iostream>
using namespace std;

template<class T>
void swap1(T& x, T& y) {
	T t = x;
	x = y;
	y = t;
}

template<class T>
class EdgeWeight {
public:
	T v1 = 0;
	T v2 = 0;
	long long weight = 0;

	EdgeWeight() {}
	EdgeWeight(T v1, T v2, int weight) :v1(v1), v2(v2), weight(weight) {}
	~EdgeWeight() {}

	EdgeWeight<T> operator=(const EdgeWeight<T>& rhs) {
		this->v1 = rhs.v1;
		this->v2 = rhs.v2;
		this->weight = rhs.weight;
		return *this;
	}

	void set(const T& tv1, const T& tv2, const int& tweight) {
		v1 = tv1;
		v2 = tv2;
		weight = tweight;
	}
	bool operator>(const EdgeWeight<T>& rhs) {
		return this->weight > rhs.weight;
	}
	bool operator<(const EdgeWeight<T>& rhs) {
		return this->weight < rhs.weight;
	}
	bool operator==(const EdgeWeight<T>& rhs) {
		return this->weight == rhs.weight;
	}
};

template<class T>
class Heap {
	int len = 0;
	int size = 0;
	T* element = nullptr;

protected:
	bool empty() {
		return size == 0;
	}

public:
	Heap() {}
	Heap(int n) :len(n + 1) {
		element = new T[n + 1];
	}
	~Heap() {
		delete[] element;
	}
	void initial(T*, const int&);
	T top();
	void push(const T&);
	void pop();
	void expand() {
		T* exp = new T[(size + 1) * 2];
		for (int i = 1; i <= size; i++)
			exp[i] = element[i];
		delete[] element;
		element = exp;
		len = (size + 1) * 2;
	}

};

template<class T>
void Heap<T>::initial(T* heap, const int& n) {
	delete[] element;
	element = heap;
	size = n;
	len = n + 1;

	for (int root = size / 2; root >= 1; root--) {
		int idx = root;
		int branch = idx * 2;

		while (branch <= size) {
			if (branch < size && element[branch] > element[branch + 1])branch++;

			if (element[idx] > element[branch]) {
				swap1(element[idx], element[branch]);
				idx = branch;
				branch *= 2;
			}
			else break;
		}

	}

}

template<class T>
T Heap<T>::top() {
	return element[1];
}

template<class T>
void Heap<T>::push(const T& x) {
	if (size == len - 1)expand();
	int idx = ++size;
	element[idx] = x;
	while (idx > 1 && element[idx] < element[idx / 2]) {
		swap1(element[idx], element[idx / 2]);
		idx /= 2;
	}

}

template<class T>
void Heap<T>::pop() {
	if (empty())return;
	int idx = 1;
	int branch = 2;
	element[idx] = element[size--];
	while (branch <= size) {
		if (branch < size && element[branch] > element[branch + 1])branch++;
		if (element[idx] > element[branch]) {
			swap1(element[idx], element[branch]);
			idx = branch;
			branch *= 2;
		}
		else break;

	}

}

template<class T>
class UnionFind {
	int size = 0;
public:
	int* root = nullptr;
	UnionFind(int n):size(n){
		root = new int[n + 1];
		for (int i = 1; i < n + 1; i++) {
			root[i] = i;
		}
	}
	~UnionFind() { 
		delete[] root;
	}
	int find(const T& element);
	bool unite(const T& v1, const T& v2);

};

template<class T>
int UnionFind<T>::find(const T& element) {//二叉树递归寻根 
	T bottom = 0;
	if (root[element] != element)
		bottom = find(root[element]);
	else
		return root[element];
}

template<class T>
bool UnionFind<T>::unite(const T& v1, const T& v2) {
	int a = find(v1);
	int b = find(v2);
	if (a > b)
		swap1(a, b);
	if (a != b) {//把小的当根 
		root[b] = a;
		return 1;
	}
	else
		return 0;

}

int main() {
	int n = 0, e = 0, i = 0, j = 0, w = 0;
	cin >> n >> e;
	Heap<EdgeWeight<int>> heap(1);
	UnionFind<int> unf(e);
	EdgeWeight<int> tv;
	EdgeWeight<int>* tmp = new EdgeWeight<int>[e + 1];
	
	for (int k = 1; k < e+1; k++) {
		cin >> i >> j >> w;
		tv.set(i, j, w);
		tmp[k] = tv;
	}
	heap.initial(tmp, e);//把输入的边直接初始化成堆 
	
	int cnt = 0;
	long long res = 0;
	while (cnt < n - 1) {
		tv = heap.top();
		heap.pop();
		if (unf.unite(tv.v1, tv.v2)) {//如果并查集能unite即能成树 
			res += tv.weight;
			cnt++;
		}

	}
	cout << res << endl;

	return 0;
}

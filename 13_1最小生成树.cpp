#include<iostream>//Prim 
using namespace std;

template<class T>
void swap1(T& x, T& y) {
	T t = x;
	x = y;
	y = t;
}

template<class T>
class Edge {
	
public:
	T start = 0;
	T end = 0;
	long long wgt = 0;
	Edge() {}
	~Edge() {}
	void set(const T& v1, const T& v2, const long long& weight) {
		start = v1;
		end = v2;
		wgt = weight;
	}
	Edge& operator=(const Edge<T>& rhs) {
		this->start = rhs.start;
		this->end = rhs.end;
		this->wgt = rhs.wgt;
		return *this;
	}
	bool operator<(const Edge<T>& rhs) {
		return this->wgt < rhs.wgt;
	}
	bool operator>(const Edge<T>& rhs) {
		return this->wgt > rhs.wgt;
	}

};

template<class T>
class Graph_Node {
	
public:
	T end = 0;
	long long wgt = 0;
	Graph_Node<T>* next = nullptr;
	Graph_Node(T end,long long w):end(end),wgt(w){}
	Graph_Node(T end,long long w,Graph_Node<T>* next):end(end), wgt(w), next(next) {}

};

template<class T>
class Graph_Chain {
	int node_size = 0;
public:
	Graph_Node<T>* headnode = nullptr;
	Graph_Chain(){}
	~Graph_Chain() {
		Graph_Node<T>* dn = headnode;
		Graph_Node<T>* nn = nullptr;
		while (dn) {
			nn = dn->next;
			delete dn;
			dn = nn;
		}
		headnode = nullptr;
	}
	void insert(const T& end,const long long& wgt) {//满足头插即可 
		Graph_Node<T>* newnode = new Graph_Node<T>(end, wgt, headnode);
		headnode = newnode;
		node_size++;
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
	T top();
	void push(const T&);
	void pop();
	void expand() {
		T* exp = new T[size * 2];
		for (int i = 1; i <= size; i++)
			exp[i] = element[i];
		delete[] element;
		element = exp;
		len = (size + 1) * 2;
	}

};

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
class Graph {
	Graph_Chain<T>* start = nullptr;
	int vertex_size = 0;
public:
	bool* note = nullptr;
	Graph(int n) :vertex_size(n) {
		start = new Graph_Chain<T>[n + 1];
		note = new bool[n + 1];
		for (int i = 0; i < n + 1; i++) 
			note[i] = 0;
	}
	~Graph() {
		delete[] note;
		delete[] start;
	}
	void addEdge(const int& v1, const int& v2, const long long& wgt) {
		start[v1].insert(v2, wgt);
		start[v2].insert(v1, wgt);
	}
	void store(const T& v1, Heap<Edge<T>>& heap) {//把起点v1的所有邻接点入堆 
		Graph_Node<T>* cn = start[v1].headnode;
		Edge<T> tmpvt;
		while (cn) {
			if (!note[cn->end]) {
				tmpvt.set(v1, cn->end, cn->wgt);
				heap.push(tmpvt);
			}
			cn = cn->next;
		}
	}
};

int main() {
	int n, e, i, j;
	long long w;

	cin >> n >> e;
	Graph<int> g(n);
	Heap<Edge<int>> heap(e);

	for (int k = 0; k < e; k++) {
		cin >> i >> j >> w;
		g.addEdge(i, j, w);
	}
	g.store(1, heap);//以1为起点 
	g.note[1] = 1;

	int cnt = 0;
	long long res = 0;
	Edge<int> tmp;
	while (cnt < n - 1) {
		tmp = heap.top();
		heap.pop();
		if (!g.note[tmp.end]) {//没被标记即可以加入 
			g.note[tmp.end] = 1;
			cnt++;
			res += tmp.wgt;
			g.store(tmp.end, heap);
		}
	}
	cout << res << endl;

	return 0;
}

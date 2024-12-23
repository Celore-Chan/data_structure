#include<iostream>
using namespace std;

template<class T>
class UnionFind {
	int size = 0;
public:
	int* root = nullptr;
	UnionFind(int n) :size(n) {
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

	return 0;
}
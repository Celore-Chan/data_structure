#include <iostream>
using namespace std;

template<class T>
void swap1(T& x, T& y) {
	T t;
	t = x;
	x = y;
	y = t;
}

template<class T>
class Node {

public:
	Node<T>* next = NULL;
	T element;
	Node() {}
	Node(T x) :element(x) {}
	Node(T x, Node<T>* next) :element(x), next(next) {}
	~Node() {}
};

template<class T>
class Chain {

public:
	Node<T>* hp = NULL;
	int size = 0;
	Chain() {}
	~Chain();
	void insert(const T&);
	void erase(const T&);
	void outp();
};

template<class T>
Chain<T>::~Chain() {
	Node<T>* cp = hp;
	while (cp != NULL) {
		cp = cp->next;
		delete hp;
		hp = cp;
	}
	size = 0;
	hp = NULL;
}

template<class T>
void Chain<T>::insert(const T& x) {//只要满足头插即可 
	hp = new Node<T>(x, hp);
	size++;
}

template<class T>
void Chain<T>::erase(const T& x) {//清除节点，遍历到前一个元素，桥接、删除
	if (size == 0)return;

	Node<T>* cp = hp;
	Node<T>* dp = cp->next;
	if (hp->element == x) {
		hp = hp->next;
		delete cp;
		size--;
		return;
	}
	while (dp != NULL) {
		if (dp->element == x) {
			cp->next = dp->next;
			delete dp;
			size--;
			return;
		}
		cp = cp->next;
		dp = cp->next;
	}
}

template<class T>
void Chain<T>::outp() {
	Node<T>* cp = hp;
	while (cp != NULL) {
		cout << cp->element << " ";
		cp = cp->next;
	}
}

template<class T>
class HashTable {
	Chain<T>* table = nullptr;
	int D = 0;
public:
	HashTable(){}
	HashTable(int n) :D(n) { 
		table = new Chain<T>[D]; 
		
	}
	~HashTable() { delete[] table; }
	void insert(const T&);
	void erase(const T&);
	void find(const T&);
	bool search(const T&);

};

template<class T>
bool HashTable<T>::search(const T& x) {
	int idx = x % D;//取得初始位置 
	if (table[idx].size == 0)return 0;//空必无 
	else {
		Node<T>* cp = table[idx].hp;
		while (cp != NULL) {
			if (cp->element == x)return 1;
			cp = cp->next;
		}
		return 0;//出循环必为无 
	}
	
}

template<class T>
void HashTable<T>::insert(const T& x) {
	int idx = x % D;
	if (search(x)) {//先检查是否存在 
		cout << "Existed" << endl;
		return;
	}
	table[idx].insert(x);//直接头插 

}

template<class T>
void HashTable<T>::erase(const T& x) {
	int idx = x % D;
	if (table[idx].size == 0 || !search(x)) {//链表为空或者找不到就不必删除 
		cout << "Delete Failed" << endl; 
		return;
	}
	table[idx].erase(x);//否则直接运行当前链表的删除 
	cout << table[idx].size << endl;

}

template<class T>
void HashTable<T>::find(const T& x) {
	int idx = x % D;
	if (!search(x))cout << "Not Found" << endl;//找不到 

	else cout << table[idx].size << endl;

}

int main() {
	int D, m,opt,x;
	cin >> D >> m;
	HashTable<int> t(D);
	for (int i = 0; i < m; i++) {
		cin >> opt>>x;
		switch (opt) {
		case 0:
			t.insert(x);
			break;
		case 1:
			t.find(x);
			break;
		case 2:
			t.erase(x);
			break;
		}
	}

	return 0;
}

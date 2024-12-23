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
void Chain<T>::insert(const T& x) {//ֻҪ����ͷ�弴�� 
	hp = new Node<T>(x, hp);
	size++;
}

template<class T>
void Chain<T>::erase(const T& x) {//����ڵ㣬������ǰһ��Ԫ�أ��Žӡ�ɾ��
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
	int idx = x % D;//ȡ�ó�ʼλ�� 
	if (table[idx].size == 0)return 0;//�ձ��� 
	else {
		Node<T>* cp = table[idx].hp;
		while (cp != NULL) {
			if (cp->element == x)return 1;
			cp = cp->next;
		}
		return 0;//��ѭ����Ϊ�� 
	}
	
}

template<class T>
void HashTable<T>::insert(const T& x) {
	int idx = x % D;
	if (search(x)) {//�ȼ���Ƿ���� 
		cout << "Existed" << endl;
		return;
	}
	table[idx].insert(x);//ֱ��ͷ�� 

}

template<class T>
void HashTable<T>::erase(const T& x) {
	int idx = x % D;
	if (table[idx].size == 0 || !search(x)) {//����Ϊ�ջ����Ҳ����Ͳ���ɾ�� 
		cout << "Delete Failed" << endl; 
		return;
	}
	table[idx].erase(x);//����ֱ�����е�ǰ�����ɾ�� 
	cout << table[idx].size << endl;

}

template<class T>
void HashTable<T>::find(const T& x) {
	int idx = x % D;
	if (!search(x))cout << "Not Found" << endl;//�Ҳ��� 

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

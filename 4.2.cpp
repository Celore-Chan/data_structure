#include <iostream>
using namespace std;

template<class T>
void swap1(T& a, T& b) {
	T x = a;
	a = b;
	b = x;
}

template<class T>
class Node {

public:
	Node<T>* next;
	T element;
	Node() {}
	Node(T x) :element(x), next(NULL) {}
	Node(T x, Node* p) :element(x), next(p) {}
	~Node() {}

};

template<class T>
class Chain {

protected:
	int size;
	Node<T>* hp;

public:
	class iterator {
	protected:
		Node<T>* node;
	public:
		iterator(Node<T>* node = NULL) :node(node) {}
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }
		iterator& operator++() { node = node->next; return *this; }
		iterator operator++(int) { iterator old = *this; node = node->next; return old; }
		bool operator!=(const iterator right)const { return node != right.node; }
		bool operator==(const iterator right)const { return node == right.node; }
		iterator begin() { return iterator(hp); }
		iterator end() { return iterator(NULL); }

	};
	Chain() { hp = NULL; size = 0; }
	Chain(int s) :size(s), hp(NULL) {}
	~Chain();
	Chain(const Chain<T>&);
	void copy(const Chain<T>&);
	void init(int);
	void insert(int, const T&);
	void erase(const T&);
	void erasebyindex(int);
	void clear();
	void search(const T&);
	void trans();
	void outp();
	bool bubble(int);
	void bubblesort();
	void combine(const Chain<T>&, const Chain<T>&);
	void yihuo();

};

template<class T>
void Chain<T>::copy(const Chain<T>& that) {//复制链表，遍历节点，复制元素 
	size = that.size;
	if (size == 0) {
		hp = NULL;
		return;
	}
	Node<T>* sp = that.hp;
	hp = new Node<T>(sp->element);
	sp = sp->next;
	Node<T>* tp = hp;
	while (sp != NULL) {
		tp->next = new Node<T>(sp->element);
		tp = tp->next;
		sp = sp->next;
	}
	tp->next = NULL;
}

template<class T>
Chain<T>::Chain(const Chain<T>& x) {
	copy(x);

}

template<class T>
void Chain<T>::clear() {//清空链表，遍历节点，delete 
	Node<T>* cp = hp;
	while (cp != NULL) {
		Node<T>* np = cp->next;
		delete cp;
		cp = np;
	}
	size = 0;
	hp = NULL;

}

template<class T>
Chain<T>::~Chain() {
	clear();

}

template<class T>
void Chain<T>::init(int n) {//初始化链表，使链表初始化时间为n 
	if (n == 0)return;
	T x = 0;
	cin >> x;
	this->insert(0, x);
	Node<T>* cp = hp;
	for (int i = 1; i < n; i++) {
		cin >> x;
		cp->next = new Node<T>(x, NULL);
		cp = cp->next;
	}
}

template<class T>
void Chain<T>::insert(int index, const T& x) {//插入元素，遍历到索引前一个元素并插入目的元素
	if (index > size)return;
	if (index == 0) {
		hp = new Node<T>(x, hp);
		size++;
	}
	else if (index > 0) {
		Node<T>* cp = hp;
		for (int i = 0; i < index - 1; i++)
			cp = cp->next;
		cp->next = new Node<T>(x, cp->next);
		size++;
	}

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
	cout << -1 << endl;
}

template<class T>
void Chain<T>::erasebyindex(int index) {//清除节点，遍历到索引前一个元素，桥接、删除
	if (index >= size || index < 0)return;
	if (index == 0) {
		Node<T>* dp = hp;
		hp = hp->next;
		delete dp;
		size--;
	}
	else {
		Node<T>* cp = hp;
		Node<T>* dp = cp->next;
		for (int i = 0; i < index - 1; i++) {
			cp = cp->next;
			dp = cp->next;
		}
		cp->next = dp->next;
		delete dp;
		size--;
	}
}

template<class T>
void Chain<T>::search(const T& x) {//遍历链表即可 
	int i = 0;
	Node<T>* cp = hp;
	while (cp != NULL) {
		if (cp->element == x) {
			cout << i << endl;
			return;
		}
		cp = cp->next;
		i++;
	}
	cout << -1 << endl;
}

template<class T>
void Chain<T>::outp() {
	Node<T>* cp = hp;
	while (cp != NULL) {
		cout << cp->element << " ";
		cp = cp->next;
	}
	cout << endl;
}

template<class T>
void Chain<T>::trans() {//遍历数组，从头插入元素 
	Node<T>* cp = hp;
	Node<T>* dp = cp->next;
	while (dp != NULL) {
		insert(0, dp->element);
		cp->next = dp->next;
		delete dp;
		dp = cp->next;
	}
}

template<class T>
bool Chain<T>::bubble(int n) {//一次冒泡 
	bool flag = 1;
	Node<T>* cp = hp;
	while (cp->next != NULL) {
		if (cp->element > cp->next->element) { swap1(cp->element, cp->next->element); flag = 0; }
		cp = cp->next;
	}
	return flag;
}

template<class T>
void Chain<T>::bubblesort() {//总冒泡 
	iterator a(hp);
	int n = size;
	while (a != a.end()) {
		if (bubble(n--))return;
		a++;
	}
}

template<class T>
void Chain<T>::combine(const Chain& a, const Chain& b) {//链表结合并进行排序 
	iterator x(a.hp);
	iterator y(b.hp);
	int flag = 0;
	int size1 = a.size;
	int size2 = b.size;
	Node<T>* tp = NULL;
	if (x != x.end()) {//判断结合链表是否为空，从而决定hp的地址 
		hp = new Node<T>(*(x++), NULL);
		tp = hp;
	}
	else if (y != y.end()) {
		hp = new Node<T>(*(y++), NULL);
		tp = hp;
	}
	else hp = NULL;
	while (x != x.end()) {//遍历结合链表，复制元素即可 
		tp->next = new Node<T>(*(x++), NULL);
		tp = tp->next;
	}
	while (y != y.end()) {
		tp->next = new Node<T>(*(y++), NULL);
		tp = tp->next;
	}//复杂度n 
	bubblesort();//冒泡 
}

template<class T>
void Chain<T>::yihuo() {
	iterator a(hp);
	T res = 0;
	int i = 0;
	while (a != a.end()) {
		res += *(a++) ^ (i++);
	}
	cout << res << endl;
}

int main() {
	int n1, n2;
	cin >> n1;
	cin >> n2;
	Chain<long long>* a = new Chain<long long>(n1);
	Chain<long long>* b = new Chain<long long>(n2);
	Chain<long long>* c = new Chain<long long>(n2 + n1);
	a->init(n1);
	b->init(n2);
	a->bubblesort();
	b->bubblesort();
	c->combine(*a, *b);
	a->yihuo();
	b->yihuo();
	c->yihuo();

	delete a;
	delete b;
	delete c;
	return 0;
}

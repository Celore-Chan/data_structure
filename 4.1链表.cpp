#include <iostream>
using namespace std;

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
	Chain(int s):size(s),hp(NULL){}
	~Chain();
	Chain(const Chain<T>&);
	void copy(const Chain<T>&);
	void init(int);
	void insert(int, const T&);
	void erase(const T&);
	void erasebyindex(int);
	void search(const T&);
	void trans();
	void outp();
	void clear();	
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
	if(n==0) return;
	T x;
	cin >> x;
	this->insert(0, x);
	Node<T>* cp = hp;
	for (int i = 1; i < n; i++) {
		cin >> x;
		cp->next = new Node<T>(x, NULL);
		cp = cp->next;
	}
	size = n;
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
	if (size==0)return;
	
	Node<T>* cp = hp;
	Node<T>* dp = cp->next;
	if (hp->element == x) {
		hp = hp->next;
		delete cp;
		size--;
		return;
	}
	while(dp!=NULL){
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

template<class T>//超级改进版（原地排序） 地址倒排 
void Chain<T>::trans() {
	Node<T>* hp0 = hp;//固定初链表的首结点地址以桥接下一个结点 
	Node<T>* cp =hp0->next ;//要倒排的结点，即目标节点 
	while (cp != NULL) {
		hp0->next = cp->next;
		cp->next = hp;//目标结点放在头部结点 
		hp = cp;
		cp = hp0->next;//桥接 
	}
}
/*template<class T>
void Chain<T>::trans() {//遍历数组，从头插入元素 
	Node<T>* cp = hp;
	Node<T>* dp = cp->next;
	while (dp != NULL) {
		insert(0, dp->element);
		cp->next = dp->next;
		delete dp;
		dp = cp->next;
	}
}*/

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
	int n, q,cnt=0,idx;
	long long val;
	cin >> n;
	cin >> q;
	Chain<long long>* a = new Chain<long long>(n);
	a->init(n);
	while (cnt < q) {
		int choice = 0;
		cin >> choice;
		switch (choice) {
		case 1:
			cin >> idx;
			cin >> val;
			a->insert(idx, val);
			cnt++;
			break;
		case 2:
			cin >> val;
			a->erase(val);
			cnt++;
			break;
		case 3:
			a->trans();
			cnt++;
			break;
		case 4:
			cin >> val;
			a->search(val);
			cnt++;
			break;
		case 5:
			a->yihuo();
			cnt++;
			break;

		}
		
	}

	delete a;
	return 0;
}

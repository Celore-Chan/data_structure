#include <iostream>

using namespace std;

template<class T>
class Queue {
	T* element;
	int size;
	int length;
	int theFront;
	int theEnd;
public:
	Queue() :element(NULL), size(0), length(0), theFront(0), theEnd(1) {}
	Queue(int n) :element(NULL), size(0), length(n), theFront(0), theEnd(1) {
		element = new T[length];
	}
	~Queue() {
		delete[] element;
	}
	void push(const T&);
	void pop();
	T& top();
	void outp();
	int QueueSize() {
		return size;
	}
	bool full() {
		return size == length;
	}
	bool empty() {
		return size == 0;
	}

};

template<class T>
void Queue<T>::push(const T& x) {//����x 
	if (full())return;
	element[theEnd] = x;//�ڶ�β����Ԫ�� 
	theEnd = (theEnd + 1) % length;//��βλ����ѭ�������������ƶ� 
	size++;
}

template<class T>
void Queue<T>::pop() {
	if (empty())return;
	theFront = (theFront + 1) % length;//ֱ�ӰѶ�ͷλ�������� 
	size--;
}

template<class T>
T& Queue<T>::top() {
	return element[(theFront + 1) % length];//��ͷ��һλ���ǵ�һ��Ԫ�� 
}

template<class T>
void Queue<T>::outp() {
	while (!empty()) {
		cout << top() << " ";
		pop();
	}
	cout << endl;
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

public:
	Node<T>* hp;
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
	int chainsize() { return size; }
	bool empty() { return size == 0; }
	void copy(const Chain<T>&);
	void init(int);
	void insert(int, const T&);
	void insert_order(const T&);
	void erase(const T&);
	void erasebyindex(int);
	bool search(const T&);
	void trans();
	void outp();
	void clear();

};

template<class T>
void Chain<T>::copy(const Chain<T>& that) {//�������������ڵ㣬����Ԫ�� 
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
void Chain<T>::clear() {//������������ڵ㣬delete 
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
void Chain<T>::init(int n) {//��ʼ������ʹ�����ʼ��ʱ��Ϊn 
	if (n == 0) return;
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
void Chain<T>::insert(int index, const T& x) {//����Ԫ�أ�����������ǰһ��Ԫ�ز�����Ŀ��Ԫ�� 
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
void Chain<T>::insert_order(const T& x) {//����Ԫ�أ�����������ǰһ��Ԫ�ز�����Ŀ��Ԫ�� 
	Node<T>* cp = hp;
	bool flag = 1;

	if (!cp) {
		hp = new Node<T>(x);
		size++;
		return;
	}
	if (x < hp->element) {
		Node<T>* tp = new Node<T>(x, hp);
		hp = tp;
		size++;
		return;
	}
	for (int i = 0; i < chainsize() - 1; i++) {
		if (x < cp->next->element) {
			Node<T>* tp = new Node<T>(x, cp->next);
			cp->next = tp;
			flag = 0;
			size++;
			return;
		}
		cp = cp->next;
	}
	if (flag) {
		Node<T>* tp = new Node<T>(x);
		cp->next = tp;
		size++;
	}

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
	cout << -1 << endl;
}

template<class T>
void Chain<T>::erasebyindex(int index) {//����ڵ㣬����������ǰһ��Ԫ�أ��Žӡ�ɾ��
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
bool Chain<T>::search(const T& x) {//���������� 
	Node<T>* cp = hp;
	while (cp != NULL) {
		if (cp->element == x) return 1;
		cp = cp->next;
	}
	return 0;
}

template<class T>//�����Ľ��棨ԭ������ ��ַ����
void Chain<T>::trans() {
	Node<T>* hp0 = hp;//�̶���������׽���ַ���Ž���һ�����
	Node<T>* cp = hp0->next;//Ҫ���ŵĽ�㣬��Ŀ��ڵ�
	while (cp != NULL) {
		hp0->next = cp->next;
		cp->next = hp;//Ŀ�������ͷ�����
		hp = cp;
		cp = hp0->next;//�Ž�
	}
}

template<class T>
class Graph {
	int vertexcnt = 0;
	int edgecnt = 0;
	Chain<T>* vertex = nullptr;

public:
	bool* note = nullptr;
	Graph(int n) :vertexcnt(n) {
		vertex = new Chain<T>[n + 1];
		note = new bool[n + 1];
		for (int i = 1; i < vertexcnt + 1; i++) {
			note[i] = 0;
		}
	}
	~Graph() {
		delete[] vertex;
		delete[] note;
	}
	bool existEdge(const int& i, const int& j) {
		if (i<1 || i>vertexcnt || j<1 || j>vertexcnt || !vertex[i].search(j))return 0;
		else return 1;
	}
	void insertEdge(const int& i, const int& j) {
		if (i<1 || i>vertexcnt || j<1 || j>vertexcnt || vertex[i].search(j))return;
		vertex[i].insert_order(j);
		vertex[j].insert_order(i);
		edgecnt++;
	}
	void eraseEdge(const int& i, const int& j) {
		if (i<1 || i>vertexcnt || j<1 || j>vertexcnt || !vertex[i].search(j))return;
		vertex[i].erase(j);
		vertex[j].erase(i);
		edgecnt--;
	}
	int degreeof(const int& i) {
		if (i<1 || i>vertexcnt)return 0;
		return vertex[i].chainsize;
	}
	T bfs(const T&);
	T dfs(const T&);
	void clearnote() {
		for (int i = 1; i < vertexcnt + 1; i++)
			note[i] = 0;
	}
	Node<T>* next(const int&);
	T Min_in_Graph(const T&);
	void test1();
	void test2(const T&);
	int test3(const T& s);
	int test4(const T& s);
	void test5(const T& t);
	void test6(const T& t);
	void test7(const T& s, const T& t);
};

template<class T>
Node<T>* Graph<T>::next(const int& x) {//�ҵ�x��һ��δ����ǵ��ٽӵ�
	Node<T>* cp = vertex[x].hp;
	while (cp) {
		if (!note[cp->element]) {
			return cp;
		}
		cp = cp->next;
	}
	return cp;
}

template<class T>
T Graph<T>::Min_in_Graph(const T& s) {//�ҵ���ͨͼ����С�Ķ��㣬��ģ�����Ҫ�ö��� 
	if (vertex[s].empty()) {
		note[s] = 1;
		return s;
	}

	Queue<Node<T>*> q(vertexcnt);//��bfs�������ж���
	Node<T>* tmp1 = new Node<T>(s);
	q.push(tmp1);
	note[s] = 1;
	T min = s, tmp = 0;
	Node<T>* cp = nullptr;
	
	while (!q.empty()) {
		tmp = q.top()->element;
		q.pop();
		cp = vertex[tmp].hp;

		while (cp != nullptr) {//�ѵ�ǰ����������ٽӵ���ջ

			if (!note[cp->element]) {
				q.push(cp);
				note[cp->element] = 1;
				if (cp->element < min)
					min = cp->element;
			}
			cp = cp->next;
		}

	}

	delete tmp1;
	return min;
}

template<class T>
void Graph<T>::test1() {
	int cnt = 0;
	for (int i = 1; i < vertexcnt + 1; i++) {
		if (!note[i]) {
			Min_in_Graph(i);
			cnt++;
		}
	}
	cout << cnt << endl;
}

template<class T>
void Graph<T>::test2(const T& s) {
	for (int i = 1; i < vertexcnt + 1; i++) {
		if (!note[i]) {
			cout << Min_in_Graph(i) << " ";
		}
	}
	cout << endl;
}

template<class T>
int Graph<T>::test3(const T& s) {//�ݹ鴦��dfs
	int cnt = 1;
	T tmp;
	if (next(s))//����s����һ��δ����Ƕ���
		tmp = next(s)->element;
	else
		return cnt;
	while (!note[tmp]) {
		note[tmp] = 1;
		cnt += test3(tmp);//�ݹ������ζ�ŵ�ͷ����ʱ�ص���һ����s
		if (next(s))//��������һ����s����һ��δ��Ƕ���
			tmp = next(s)->element;
		else
			return cnt;
	}
	return cnt;
}

template<class T>
int Graph<T>::test4(const T& s) {//��test3һ����ֻ��������������ĳ��������
	int cnt = 1;
	T tmp;
	if (next(s))
		tmp = next(s)->element;
	else
		return cnt;
	while (!note[tmp]) {
		note[tmp] = 1;
		cout << tmp << " ";//�����ǰ����
		cnt += test4(tmp);
		if (next(s))
			tmp = next(s)->element;
		else
			return cnt;
	}
	return cnt;
}

template<class T>
void Graph<T>::test5(const T& s) {//��ģ�Ҫ�ö��� 
	Queue<Node<T>*> q(vertexcnt);

	Node<T>* tmp1 = new Node<T>(s);
	q.push(tmp1);
	note[s] = 1;
	T tmp = 0;
	int cnt = 1;
	Node<T>* cp = nullptr;
	while (!q.empty()) {
		tmp = q.top()->element;
		q.pop();
		cp = vertex[tmp].hp;

		while (cp != nullptr) {
			if (!note[cp->element]) {
				q.push(cp);
				note[cp->element] = 1;
				cnt++;
			}
			cp = cp->next;
		}

	}
	cout << cnt << endl;

	delete tmp1;
}

template<class T>
void Graph<T>::test6(const T& s) {
	Queue<Node<T>*> q(vertexcnt);

	Node<T>* tmp1 = new Node<T>(s);
	q.push(tmp1);
	note[s] = 1;
	T tmp = 0;
	Node<T>* cp = nullptr;
	cout << s << " ";
	while (!q.empty()) {
		tmp = q.top()->element;
		q.pop();
		cp = vertex[tmp].hp;

		while (cp != nullptr) {

			if (!note[cp->element]) {
				q.push(cp);
				cout << cp->element << " ";
				note[cp->element] = 1;
			}
			cp = cp->next;
		}

	}
	cout << endl;

	delete tmp1;
}

template<class T>
void Graph<T>::test7(const T& s, const T& t) {
	if (s == t) {
		cout << 1 << endl;
		return;
	}

	Queue<Node<T>*> q(vertexcnt);
	int cnt = 0, r_size = 0;
	int lastcnt = 1;

	Node<T>* tmp1 = new Node<T>(s);
	q.push(tmp1);
	note[s] = 1;
	T tmp = 0;
	Node<T>* cp = nullptr;
	while (!q.empty()) {
		if (lastcnt == 0) {//����һ�εĶ�����ͳ����ϣ�����ζ�Ÿò����
			r_size++;//������һ
			lastcnt = cnt;//ͳ�ƶ�����ά��
			cnt = 0;
		}
		tmp = q.top()->element;
		q.pop();
		cp = vertex[tmp].hp;

		while (cp != nullptr) {

			if (!note[cp->element]) {
				cnt++;
				q.push(cp);
				if (cp->element == t) {
					cout << r_size + 1 << endl;
					delete tmp1;
					return;
				}
				note[cp->element] = 1;
			}
			cp = cp->next;
		}lastcnt--;//ÿ�������ٽӵ�ı�������ζ�ŵ�ǰ����ͳ�����


	}
	cout << -1 << endl;

	delete tmp1;
}

int main() {
	int n, m, s, t;
	bool choice;
	cin >> n >> m >> s >> t;
	Graph<int> g(n);
	for (int i = 0; i < m; i++) {
		int v1, v2;
		cin >> choice >> v1 >> v2;
		if (choice)g.eraseEdge(v1, v2);
		else g.insertEdge(v1, v2);

	}

	g.test1();
	g.clearnote();

	g.test2(s);
	g.clearnote();

	g.note[s] = 1;
	cout << g.test3(s) << endl;//
	g.clearnote();

	g.note[s] = 1;
	cout << s << " ";
	g.test4(s);//
	cout << endl;
	g.clearnote();

	g.test5(t);//
	g.clearnote();

	g.test6(t);//
	g.clearnote();

	g.test7(s, t);
	g.clearnote();

	return 0;
}
/*
10 7 10 3
0 5 10
0 10 6
0 5 4
0 6 7
0 6 4
0 4 2
0 4 3
*/

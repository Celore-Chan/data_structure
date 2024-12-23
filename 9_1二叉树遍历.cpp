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
void Queue<T>::push(const T& x) {//插入x 
	if (full())return;
	element[theEnd] = x;//在队尾插入元素 
	theEnd = (theEnd + 1) % length;//队尾位置在循环队列中往后移动 
	size++;
}

template<class T>
void Queue<T>::pop() {
	if (empty())return;
	theFront = (theFront + 1) % length;//直接把队头位置往后移 
	size--;
}

template<class T>
T& Queue<T>::top() {
	return element[(theFront + 1) % length];//队头后一位才是第一个元素 
}

template<class T>
class Stack {
	int len = 0;
	int size = 0;
	T* element = nullptr;
	int hp = 0;
public:
	Stack() {}
	Stack(int n) {
		len = n;
		element = new T[n];
		hp = 0;
	}
	~Stack() {
		delete[] element;
	}
	bool empty() {
		return size == 0;
	}
	int listsize() {
		return size;
	}
	T& top() {
		return element[size - 1];
	}
	void pop() {//直接size--即可，这样的话被删数据就不在可用数据的范围内 
		if (empty())return;
		size--;
	}
	void push(const T& x) {//正常头插 
		if (listsize() == len)return;
		element[size] = x;
		size++;
	}


};


class TreeNode {
	
	
public:
	TreeNode* leftNode = NULL;
	TreeNode* rightNode = NULL;
	int value =-1;
	int size = 0;
	int height = 1;

	TreeNode(){}
	TreeNode(const int& value):value(value) {}
	TreeNode(const int& value, TreeNode* LeftNode, TreeNode* RightNode): value(value),leftNode(LeftNode),rightNode(RightNode){}
	~TreeNode() {}

};


class BinaryTree {
	
	TreeNode* nodes[100005];
	int size=1;
	int lastIndex = 0;
	
public:
	TreeNode* root=NULL;
	BinaryTree(){}
	BinaryTree(int n):size(n) {
		for (int i = 1; i < n+1; i++) {
			nodes[i] = new TreeNode(i);
		}
		root = nodes[1];
	}
	~BinaryTree() {  }
	void initialize();
	void pairing(int, int, int);
	bool empty()const { return size == 0; }
	int treesize()const { return size; }
	int height(TreeNode*);
	void preOrder(TreeNode*);
	void inOrder();
	void postOrder();
	void levelOrder();
	void nodeHeight();
	int nodecount(TreeNode*);
	void nodecnt();
	void clear();

};


void BinaryTree::pairing(int ri,int l,int r) {
	if(l != -1)
		nodes[ri]->leftNode = nodes[l];
	if (r != -1)
		nodes[ri]->rightNode = nodes[r];
}


void BinaryTree::initialize() {
	int l, r;
	int cnt = 1;
	for (int i = 1; i < 100005; i++) {
		if (cnt == treesize())return;
		cin >> l >> r;
		if (l != -1)cnt++;
		if (r != -1)cnt++;
		pairing(i, l, r);

	}
	
}

int BinaryTree::nodecount(TreeNode* r) {
	if (r == NULL)return 0;
	int cnt = nodecount(r->leftNode) + nodecount(r->rightNode);
	return ++cnt;

}

int BinaryTree::height(TreeNode* r) {
	if (r == NULL)return 0;
	int lh = height(r->leftNode);
	int rh = height(r->rightNode);
	if (rh > lh)return ++rh;
	else return ++lh;
}

void BinaryTree::preOrder(TreeNode* rootNode) {
	if (rootNode == NULL)return;
	cout << rootNode->value << " ";
	preOrder(rootNode->leftNode);
	preOrder(rootNode->rightNode);

}

void BinaryTree::inOrder() {
	int th = height(root);
	TreeNode* cp = root;
	Stack<TreeNode*> stk(th);
	while (cp || !stk.empty()) {
		while (cp) {
			stk.push(cp);
			cp = cp->leftNode;
		}
		cp = stk.top(); 
		stk.pop();
		cout << cp->value << " ";
		cp = cp->rightNode;
	}
	cout << endl;
}

void BinaryTree::postOrder() {
	int th = height(root);
	Stack<TreeNode*> stk1(treesize()), stk2(treesize());
	stk1.push(root);
	while (!stk1.empty()) {
		TreeNode* cp = stk1.top(); 
		stk1.pop();
		stk2.push(cp);
		if (cp->leftNode) stk1.push(cp->leftNode);
		if (cp->rightNode) stk1.push(cp->rightNode);
	}
	while (!stk2.empty()) {
		cout << stk2.top()->value << " ";
		stk2.pop();
	}
	cout << endl;
}

void BinaryTree::levelOrder() {
	Queue<TreeNode*> line(treesize());
	line.push(root);
	while (!line.empty()) {
		cout << line.top()->value << " ";
		if (line.top()->leftNode != NULL)line.push(line.top()->leftNode);
		if (line.top()->rightNode != NULL)line.push(line.top()->rightNode);
		line.pop();
	}
	cout << endl;
}

void BinaryTree::nodeHeight() {
	for (int i = 1; i < treesize() + 1; i++) {
		cout << height(nodes[i]) << " ";
	}
	cout << endl;
}

void BinaryTree::nodecnt() {
	for (int i = 1; i < treesize() + 1; i++) {
		cout << nodecount(nodes[i]) << " ";
	}
	cout << endl;
}

int main() {

	int n = 0;
	cin >> n;

	BinaryTree t(n);
	t.initialize();

	t.preOrder(t.root);
	cout << endl;
	t.inOrder();
	t.postOrder();
	t.levelOrder();
	t.nodecnt();
	t.nodeHeight();

	return 0;
}
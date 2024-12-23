#include<iostream>

using namespace std;

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
	int value = 0;
	int leftsize = 0;
	TreeNode* leftNode = nullptr;
	TreeNode* rightNode = nullptr;

	TreeNode(){}
	TreeNode(int x):value(x){}
	TreeNode(int x,TreeNode* left,TreeNode* right):value(x),leftNode(left),rightNode(right){}
	~TreeNode(){}
};

class IndexBSTree {
	
	int size = 0;

public:
	TreeNode* root = nullptr;
	IndexBSTree(){}
	~IndexBSTree() { destroy(); }

	int treesize() {
		return size;
	}
	bool empty() {
		return size == 0;
	}
	bool search(const int&);

	void destroy();
	void insert(const int&);
	void find(const int&);
	void erase(const int&);
	void find_rank(const int&);
	void erase_rank(const int&);
	void inorder(TreeNode* cp) {
		if (cp == nullptr)return;
		inorder(cp->leftNode);
		if (cp != nullptr)cout << "value:" << cp->value << " " << "leftsize:" << cp->leftsize << endl;
		inorder(cp->rightNode);
	}

};

bool IndexBSTree::search(const int& x) {//找元素在不在 
	if (empty())return 0;
	TreeNode* cn = root;

	while (cn != nullptr && cn->value != x) {
		if (x > cn->value)cn = cn->rightNode;
		else cn = cn->leftNode;
	}
	if (cn==nullptr)return 0;
	else return 1;

}

void IndexBSTree::destroy() {
	Stack<TreeNode*> stk1(treesize()), stk2(treesize());
	TreeNode* cp = root;
	stk1.push(cp);

	while (!stk1.empty()) {
		cp = stk1.top();
		stk2.push(cp);
		stk1.pop();
		if (cp->leftNode != nullptr)stk1.push(cp->leftNode);
		if (cp->rightNode != nullptr)stk1.push(cp->rightNode);

	}

	while (!stk2.empty()) {
		delete stk2.top();
		stk2.pop();
	}

}

void IndexBSTree::insert(const int& x) {
	if (search(x)) {
		cout << 0 << endl;
		return;
	}
	int res = 0;
	TreeNode* cn = root;//当前的节点current node
	TreeNode* ln = nullptr;//上一个节点last node

	while (cn != nullptr) {
		res ^= cn->value;
		if (x < cn->value) {
			cn->leftsize++;
			ln = cn;
			cn = cn->leftNode;
		}
		else {
			ln = cn;
			cn = cn->rightNode;
		}

	}
	cout << res << endl;

	TreeNode* tmp = new TreeNode(x);
	if (ln == nullptr)root = tmp;
	else if (x < ln->value)ln->leftNode = tmp;
	else ln->rightNode = tmp;
	size++;

}

void IndexBSTree::erase(const int& x) {
	if (empty() || !search(x)) {
		cout << 0 << endl;
		return;
	}
	int res = 0;
	TreeNode* dn = root;//要删除的节点delete node
	TreeNode* nTdn = nullptr;//dn上一个节点node To delete node

	while (dn->value != x) {
		res ^= dn->value;
		if (x > dn->value) {
			nTdn = dn;
			dn = dn->rightNode;

		}
		else {
			dn->leftsize--;
			nTdn = dn;
			dn = dn->leftNode;
		}
	}
	res ^= x;
	cout << res << endl;

	if (dn->leftNode != nullptr && dn->rightNode != nullptr) {
		TreeNode* rn = dn->rightNode;//要拿来替换的元素resouce node
		TreeNode* nTrn = dn;//rn的上一个节点node To resouce node

		while (rn->leftNode != NULL) {
			rn->leftsize--;
			nTrn = rn;
			rn = rn->leftNode;

		}
		rn->leftsize = dn->leftsize;

		if (nTrn == dn) {//维护nTrn的子树，分两种情况 
			if (rn->rightNode) nTrn->rightNode = rn->rightNode;
			else nTrn->rightNode = nullptr;
		}
		else {
			if (rn->rightNode) nTrn->leftNode = rn->rightNode;
			else nTrn->leftNode = nullptr;
		}
		
		if (dn == root) {//维护被删元素的子树，把它的子树接到rn，并把rn接到nTdn上 
			root = rn;
			rn->leftNode = dn->leftNode;
			rn->rightNode = dn->rightNode;
			delete dn;
			size--;
		}
		else if (dn->value < nTdn->value) {
			nTdn->leftNode = rn;
			rn->leftNode = dn->leftNode;
			rn->rightNode = dn->rightNode;
			delete dn;
			size--;
		}
		else {
			nTdn->rightNode = rn;
			rn->leftNode = dn->leftNode;
			rn->rightNode = dn->rightNode;
			delete dn;
			size--;
		}

	}
	else {//只有一个子树的情况，直接连接 
		if (dn == root) {
			if (dn->leftNode)root = dn->leftNode;
			else root = dn->rightNode;
			delete dn;
			size--;
		}
		else if (x < nTdn->value) {
			if (dn->leftNode)nTdn->leftNode = dn->leftNode;
			else nTdn->leftNode = dn->rightNode;
			delete dn;
			size--;
		}
		else{
			if (dn->leftNode)nTdn->rightNode = dn->leftNode;
			else nTdn->rightNode = dn->rightNode;
			delete dn;
			size--;
		}
	}

}

void IndexBSTree::find(const int& x) {
	if (empty() || !search(x)) {
		cout << 0 << endl;
		return;
	}
	int res = 0;
	TreeNode* cn = root;

	while (cn->value != x) {
		res ^= cn->value;
		if (x > cn->value)cn = cn->rightNode;
		else cn = cn->leftNode;
	}
	res ^= x;

	cout << res << endl;
}

void IndexBSTree::erase_rank(const int& x) {
	if (empty() || x > treesize() || x < 1) {
		cout << 0 << endl;
		return;
	}
	int idx = x;
	TreeNode* cp = root;

	while (1) {//元素的真实名次是左子树大小加一 
		if (cp->leftsize + 1 == idx) {
			erase(cp->value);
			return;
		}
		else if (idx < cp->leftsize + 1) {
			cp = cp->leftNode;
		}
		else {//如果到了右子树，就要把左子树的名次减完，以右子树顶做根，重新循环 
			idx -= cp->leftsize + 1;
			cp = cp->rightNode;
		}

	}
	
}

void IndexBSTree::find_rank(const int& x) {
	if (empty() || x > treesize() || x < 1) {
		cout << 0 << endl;
		return;
	}
	int idx = x;
	TreeNode* cp = root;

	while (1) {
		if (cp->leftsize + 1 == idx) {
			find(cp->value);
			return;
		}
		else if (idx < cp->leftsize + 1) {
			cp = cp->leftNode;
		}
		else {
			idx -= cp->leftsize + 1;
			cp = cp->rightNode;
		}

	}

}

int main() {
	int m = 0, a = 0, b = 0;
	cin >> m;
	IndexBSTree t;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		switch (a)
		{
		case 0:
			t.insert(b);
			break;

		case 1:
			t.find(b);
			break;

		case 2:
			t.erase(b);
			break;

		case 3:
			t.find_rank(b);
			break;

		case 4:
			t.erase_rank(b);
			break;

		default:
			break;
		}

	}

	return 0;
}

/*int m = 0, a = 0, b = 0;
	cin >> m;
	IndexBSTree t;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		switch (a)
		{
		case 0:
			t.insert(b);
			break;

		case 1:
			t.find(b);
			break;

		case 2:
			t.erase(b);
			break;

		case 3:
			t.find_rank(b);
			break;

		case 4:
			t.erase_rank(b);
			break;

		default:
			break;
		}

	}*///oj

/*
	IndexBSTree a;
	a.insert(20);
	a.insert(30);
	a.insert(10);
	a.insert(5);
	a.insert(15);
	a.insert(3);
	a.insert(9);
	a.insert(2);
	a.insert(4);
	a.insert(6);
	a.insert(8);
	a.insert(7);
	a.insert(25);
	a.insert(40);
	a.insert(23);
	a.insert(26);
	a.insert(35);
	a.insert(60);
	a.insert(21);
	a.insert(24);
	a.insert(28);
	a.insert(27);
	a.insert(29);
	a.insert(11);
	a.insert(17);
	a.insert(13);
	a.insert(16);
	a.insert(19);
	a.insert(12);
	a.insert(14);
	a.insert(18);
	a.insert(37);
	a.insert(46);
	a.insert(100);
	a.erase(11);
	a.inorder(a.root);*///test

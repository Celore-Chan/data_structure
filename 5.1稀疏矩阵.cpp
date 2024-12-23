#include<iostream>
using namespace std;
//ת���õ�Ͱ���򣬹��ȿ�һ������ 
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
	void erase();
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
//ֻҪ����ͷ��ͷɾ���� 
template<class T>
void Chain<T>::insert(const T& x) {
	hp = new Node<T>(x, hp);
	size++;
}

template<class T>
void Chain<T>::erase() {
	if (hp == NULL)return;
	Node<T>* cp = hp;
	hp = hp->next;
	delete cp;
	size--;
}

template<class T>
void Chain<T>::outp() {
	Node<T>* cp = hp;
	while (cp != NULL) {
		cout << cp->element << " ";
		cp = cp->next;
	}
}
//�������Ԫ�ص����� 
template <class T>
class Array {

public:
	Array() {}
	Array(int n);
	Array(const Array<T>&) {}
	~Array() { if (element) delete[] element; len = 0; size = 0; }
	bool empty()const { return size == 0; }
	int listsize() const { return size; }
	T& get(int)const;
	int theIndexof(const T&)const;
	void erase(int);
	void insert(int, const T&);
	void outp();
	void reset(int);
	void clear();
	Array<T>& operator=(const Array<T>&);
	int len = 0;
	int size = 0;
protected:
	void check(int)const;
	T* element=NULL;


};

template<class T>
void Array<T>::check(int index) const {
	/*if (index >= size || index < 0) {
		throw out_of_range("Index out of range.");
	};*/
}

template<class T>
Array<T>::Array(int n) {
	len = n;
	element = new T[n];
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& a)
{
	if (this == &a)return *this;
	delete[] element;
	len = a.len;
	size = a.size;
	element = new T[len];
	for (int i = 0; i < size; i++) {
		element[i] = a.element[i];
	}
	return *this;
}

template<class T>
T& Array<T>::get(int index)const {
	//check(index);
	return element[index];
}

template<class T>
int Array<T>::theIndexof(const T& x) const {
	for (int i = 0; i < size; i++) {
		if (element[i] == x)return i;
	}
	return -1;
}

template<class T>
void Array<T>::erase(int index) {
	//check(index);
	for (int i = index; i < size - 1; i++) {
		element[i] = element[i + 1];
	}
	size--;
}

template<class T>
void Array<T>::insert(int index, const T& x) {
	//check(index);
	for (int i = size; i > index; i--) {
		element[i] = element[i - 1];
	}
	element[index] = x;
	size++;
}

template<class T>
void Array<T>::outp() {
	for (int i = 0; i < size; i++) {
		cout << element[i] << " ";
	}
	cout << endl;
}

template<class T>
void Array<T>::clear() {
	delete[] element;
	len = 0;
	size = 0;
}

template<class T>
void Array<T>::reset(int n) {
	len = n;
	size = 0;
	delete[] element;
	element = new T[len];
}
//���� 
template<class T>
class matrixTerm {
public:
	int col = 0;
	int row = 0;
	T element;
	matrixTerm() {}
	~matrixTerm() {}
	matrixTerm(const matrixTerm<T>&);
	matrixTerm<T>& operator =(const matrixTerm<T>&);

};

template<class T>
matrixTerm<T>::matrixTerm(const matrixTerm<T>& c) {
	col = c.col;
	row = c.row;
	element = c.element;
}

template<class T>
matrixTerm<T>& matrixTerm<T>::operator=(const matrixTerm& c) {
	if (this == &c)return *this;

	col = c.col;
	row = c.row;
	element = c.element;
	return *this;
}
//ϡ����� 
template<class T>
class sparseMatrix {
	int col ;
	int row ;
	Array<(matrixTerm<T>)> terms;
public:
	sparseMatrix():col(0),row(0) {}
	sparseMatrix(int row, int col) :row(row), col(col) {}
	sparseMatrix(const sparseMatrix<T>&) {}
	~sparseMatrix() {}
	void initial1();
	void initial2();
	void sum(const sparseMatrix<T>&);
	void mul(sparseMatrix<T>&);
	void trans();
	void outp()const;
	void clear();
	void testini(int, int);
	sparseMatrix<T>& operator=(const sparseMatrix<T>&);

};

template<class T>
void sparseMatrix<T>::clear() {
	terms.reset(0);
	col = 0;
	row = 0;
}

template<class T>
sparseMatrix<T>& sparseMatrix<T>::operator=(const sparseMatrix<T>& c) {
	if (this == &c)return *this;
	col = c.col;
	row = c.row;
	terms = c.terms;
	return *this;
}
//û�з���Ԫ�ظ����µ� ��ʼ�� 
template<class T>
void sparseMatrix<T>::initial1() {
	int n, m;
	T x;
	cin >> n;
	cin >> m;
	row = n;
	col = m;
	Array<matrixTerm<T>>* tem = new Array<matrixTerm<T>>(n * m);
	n = 0;
	for (int i = 0; i < row; i++) {//����ȫ���󣬰ѷ���Ԫ�ش����ʱ��ϡ����� 
		for (int j = 0; j < col; j++) {
			cin >> x;
			if (x != 0) {
				tem->get(n).row = i;
				tem->get(n).col = j;
				tem->get(n++).element = x;
				tem->size++;
			}
		}
	}
	terms.reset(tem->listsize());

	for (int i = 0; i < tem->listsize(); i++) {//���� 
		(terms.get(i)).row = tem->get(i).row;
		(terms.get(i)).col = tem->get(i).col;
		(terms.get(i)).element = tem->get(i).element;
		terms.size++;
	}

	delete tem;
}
//�з���Ԫ�ظ����µ� ��ʼ�� 
template<class T>
void sparseMatrix<T>::initial2() {
	int n = 0, m = 0, t = 0, x = 0, y = 0, cnt = 0;
	T v;
	cin >> n;
	cin >> m;
	row = n;
	col = m;
	cin >> t;//����Ԫ�ظ��� 
	terms.reset(t);
	for (int i = 0; i < t; i++) {
		cin >> x;
		cin >> y;
		cin >> v;
		//cout << cnt++ << endl;

		terms.get(i).row = x - 1;
		terms.get(i).col = y - 1;
		terms.get(i).element = v;
		//cout << terms.get(i).row << " " << terms.get(i).col << " " << terms.get(i).element << endl;
		terms.size++;
	}

}

template<class T>
void sparseMatrix<T>::outp() const {
	int num = 0;
	int n = 0;
	cout << row << " " << col << endl;
	for (int i = 0; i < row; i++) {//����ȫ�����������㼴������������0 
		for (int j = 0; j < col; j++) {
			num = i * col + j;
			if (((terms.get(n).row) * col + terms.get(n).col) == num)
				cout << terms.get(n++).element << " ";
			else cout << 0 << " ";
		}
		cout << endl;
	}
}

template<class T>
void sparseMatrix<T>::sum(const sparseMatrix<T>& r) {
	if (row == r.row && col == r.col) {
		int m1 = 0;
		int m2 = 0;
		int num = 0;
		matrixTerm<T> res;
		Array<matrixTerm<T>>* a = new Array<matrixTerm<T>>(terms.size + r.terms.size);
		while (m1 != terms.listsize() && m2 != r.terms.listsize()) {//����ϡ����� ����ͷ���� 
			int m1n = terms.get(m1).row * col + terms.get(m1).col;
			int m2n = r.terms.get(m2).row * col + r.terms.get(m2).col;
			if (m1n == m2n) {//������ȼ�������ӣ������������ 
				
				T x = terms.get(m1).element + r.terms.get(m2).element;
				if (x != 0) {
					num++;
					res.row = terms.get(m1).row;
					res.col = terms.get(m1).col;
					res.element = x;
					a->insert(a->listsize(), res);
				}
				
				m1++;
				m2++;
			}
			else {//������С�Ĳ�����ʱ���󣬴�Ļ����ٱȽ� 
				if (m1n < m2n) {
					num++;

					a->insert(a->listsize(), terms.get(m1));

					m1++;
				}
				else {
					num++;

					a->insert(a->listsize(), r.terms.get(m2));

					m2++;
				}
			}

		}//�����Ժ��δ����Ԫ��ֱ�Ӳ��� 
		while (m1 < terms.listsize()) {
			a->insert(a->listsize(), terms.get(m1));
			m1++;
			num++;
		}
		while (m2 < r.terms.listsize()) {
			a->insert(a->listsize(), r.terms.get(m2));
			m2++;
			num++;
		}
		terms.reset(num);
		for (int i = 0; i < num; i++) {
			terms.get(i) = a->get(i);
			terms.size++;
		}
		delete a;
	}
	else {//������ʱ���� 
		row = r.row;
		col = r.col;
		terms.reset(r.terms.listsize());
		for (int i = 0; i < r.terms.size; i++) {
			terms.get(i) = r.terms.get(i);
			terms.size++;
		}
		cout << -1 << endl;;
	}

}

template<class T>
void sparseMatrix<T>::mul(sparseMatrix<T>& r) {
	if (col == r.row) {
		r.trans();//ת�þ���2 
		Array<matrixTerm<T>>* a = new Array<matrixTerm<T>>(row * r.row);
		matrixTerm<T> res;
		int m1 = 0, m2 = 0;
		int* AoM1 = new int[row];//����1���з������ 
		int* AoM2 = new int[r.row];//ͬ�� 
		for (int i = 0; i < row; i++) {//��ʼ�� 
			AoM1[i] = 0;
		}
		for (int i = 0; i < r.row; i++) {
			AoM2[i] = 0;
		}
		for (int i = 0; i < r.terms.listsize(); i++) {
			AoM2[r.terms.get(i).row]++;
		}
		for (int i = 0; i < terms.listsize(); i++) {
			AoM1[terms.get(i).row]++;
		}
		int left1 = 0, left2 = 0, num = 0;
		m1 = m2 = 0;
		T val = 0;

		for (int row2 = 0; row2 < r.row; row2++) {//��������2������ 

			if (AoM2[row2] != 0) {
				m2 = left2;
				for (int row1 = 0; row1 < row; row1++) {//��������1������ 

					if (AoM1[row1] != 0) {
						m1 = left1;
						for (int i = 0; i < AoM2[row2]; i++) {//����2��ÿ��Ԫ�ر��������1ȫ��Ԫ�� 
							for (int j = 0; j < AoM1[row1]; j++) {

								if (terms.get(m1).col == r.terms.get(m2).col) {
									val += terms.get(m1).element * r.terms.get(m2).element;

									break;//��������ͬ�е���˱��������ֱ������2���б����� 
								}
								m1++;
							}
							if (i + 1 != AoM2[row2]) { m1 = left1; m2++; }//����1������һ���������2�ص����� 

						}
						left1 += AoM1[row1];//���þ���1ÿ�е�����Ԫ������������ 
						if (val != 0) {
							num++;
							res.row = row2;
							res.col = row1;
							res.element = val;
							a->insert(a->listsize(), res);
							val = 0;
						}//���������2��һ�����жϷ�����񣬷������ 

					}
					if (row1 + 1 != row)m2 = left2;
				}
			}//���������1�� 
			left2 += AoM2[row2];//���þ���2ÿ�е�����Ԫ������������
			m1 = 0;
			left1 = 0;//����1�ص���ʼ��0��0�� 
		}
		col = row;
		row = r.row;
		terms.reset(num);
		//cout << num << endl;
		for (int i = 0; i < num; i++) {
			terms.get(i) = a->get(i);
			terms.size++;
		}

		this->trans();//�������������ǽ�������ת�ã��˴�������ת�� 
		//outp();
		delete[] AoM1;
		delete[] AoM2;
		delete a;
	}
	else {
		row = r.row;
		col = r.col;
		terms.reset(r.terms.size);
		for (int i = 0; i < r.terms.size; i++) {
			terms.get(i).row = r.terms.get(i).row;
			terms.get(i).col = r.terms.get(i).col;
			terms.get(i).element = r.terms.get(i).element;
			terms.size++;
		}
		cout << -1 << endl;
	}

}


template<class T>
void sparseMatrix<T>::trans() {
	int cnt = 0;
	matrixTerm<T> res;
	Chain<matrixTerm<T>>* rank = new Chain<matrixTerm<T>>[col];
	Array<matrixTerm<T>>* tem = new Array<matrixTerm<T>>(terms.size);
	for (int i = 0; i < terms.size; i++) {//Ͱ�ţ�������������Ͱ��ÿ��Ͱ���ǰ���ͷ�壬������ʵ��ÿ�е�ת�� 
		cnt = (terms.get(i)).col;
		res.col = (terms.get(i)).row;
		res.row = (terms.get(i)).col;
		res.element = (terms.get(i)).element;
		rank[cnt].insert(res);
	}
	/*for (int i = 0; i < col; i++) {
		while (rank[i].hp != NULL) {
			cout<<((rank[i].hp)->element).element;
			rank[i].erase();
		}
	}*/
	cnt = 0;
	for (int i = 0; i < col; i++) {
		while (rank[i].hp != NULL) {
			tem->insert(cnt, (rank[i].hp)->element);//ÿһ�ж�����Ӧ�е�ͰԪ��ͷ�� 
			rank[i].erase();
		}
		cnt = tem->size;//���� 
	}
	terms = *tem;//������ʱ���� 
	int t = col;
	col = row;
	row = t;//���������� 

	delete[]rank;
	delete tem;
}

template<class T>
void sparseMatrix<T>::testini(int m, int n) {
	int num = 0, cnt = 0;
	row = m;
	col = n;
	terms.reset(row * col);
	int flag = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			num = i * col + j;
			if (flag == 5) {
				terms.get(cnt).row = i;
				terms.get(cnt).col = j;
				terms.get(cnt++).element = num;
				terms.size++;
				flag = 0;
			}
			else {
				flag++;
			}

		}
	}
}

int main() {
	sparseMatrix<int> a, b;

	a.testini(10, 10);
	a.outp();
	b.testini(100, 10);
	a.mul(b);
	a.outp();

	/*int steps = 0, choice = 0, x = 0, y = 0, v = 0, m = 0, n = 0, t = 0;
	cin >> steps;
	for (int i = 0; i < steps; i++) {
		cin >> choice;
		switch (choice) {
		case 1:
			//a.clear();
			a.initial1();
			break;
		case 2:
			//b.clear();
			b.initial2();
			a.mul(b);
			break;
		case 3:
			//b.clear();
			b.initial2();
			a.sum(b);
			break;
		case 4:
			a.outp();
			break;
		case 5:
			a.trans();
			break;
		}
		//b.outp();
	}*/

	return 0;
}

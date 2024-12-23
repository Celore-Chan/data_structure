#include <iostream>

using namespace std;

template<class T>
void swap1(T& x, T& y) {
	T t = x;
	x = y;
	y = t;
}

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
	void initial(T*, const int&);
	T top();
	void push(const T&);
	void pop();
	void sort(T*, const int&);
	void expand() {
		T* exp = new T[(size + 1) * 2];
		for (int i = 1; i <= size; i++)
			exp[i] = element[i];
		delete[] element;
		element = exp;
		len = (size + 1) * 2;
	}

};

template<class T>
void Heap<T>::initial(T* heap, const int& n) {
	delete[] element;
	element = heap;
	size = n;
	len = n + 1;

	for (int root = size / 2; root >= 1; root--) {
		int idx = root;
		int branch = idx * 2;

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
}

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
void Heap<T>::sort(T* val, const int& n) {
	initial(val, n);
	for (int i = 1; i <= n; i++) {
		cout << top() << " ";
		pop();
	}
	cout << endl;
}

int main() {
	Heap<int> heap(5005);
	int size = 0, choice = 0, val = 0, steps = 0;
	cin >> size;
	int* ini = new int[size+1];
	for (int i = 1; i <= size; i++) {
		cin >> val;
		ini[i] = val;
	}
	heap.initial(ini, size);
	cout << heap.top() << endl;
	cin >> steps;
	for (int i = 0; i < steps; i++) {
		cin >> choice;
		switch (choice)
		{
		case 1:
			cin >> val;
			heap.push(val) ;
			cout << heap.top() << endl;
			break;

		case 2:
			heap.pop() ;
			cout << heap.top() << endl;
			break;

		case 3:
			cin >> size;
			int* tmp = new int[size + 1];
			for (int i = 1; i <= size; i++) {
				cin >> tmp[i];
			}
			heap.sort(tmp, size);
			break;
		}
	}

	return 0;
}

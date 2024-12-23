#include <iostream>
#define null 104743
using namespace std;

template<class T>
void swap1(T& x, T& y) {
	T t;
	t = x;
	x = y;
	y = t;
}

template<class T>
class HashTable {
	T* table = nullptr;
	int D = 0;
	int size = 0;
public:
	HashTable(){}
	HashTable(int n) :D(n) { 
		table = new T[D]; 
		for (int i = 0; i < D; i++)
			table[i] = null; 
	}
	~HashTable() { delete[] table; }
	void insert(const T&);
	void erase(const T&);
	void find(const T&);
	bool search(const T&);

};


template<class T>
bool HashTable<T>::search(const T& x) {
	int theindex = x % D;//定位元素的初始位置（应该在的位置） 
	int index = theindex;//从初始位置开始遍历 
	if (table[index] == null)return 0;
	if (table[index] == x)return 1;
	index = (index + 1) % D;
	while (table[index] != null&&index!=theindex) {//直到空或重新回到初始位置为止 
		if (table[index] == x) 
			return 1;
		index = (index + 1) % D;
	}
	return 0;//如果循环结束，必定查找失败 
}


template<class T>
void HashTable<T>::insert(const T& x) {
	if (search(x)) {//先查找，有，就不用插入 
		cout << "Existed" << endl;
		return;
	}
	if (size == D)return;
	int theindex = x % D;//找到初始位置 
	int index = theindex;
	if (table[theindex] == null) {//空就立马插入 
		table[theindex] = x;
		size++;
		cout << theindex<<endl;
	}
	else {
		do {//找到空位置为止 
			index = (index + 1) % D;
		} while (table[index] != null );
		table[index] = x;
		size++;
		cout << index << endl;

	}
}

template<class T>
void HashTable<T>::erase(const T& x) {
	if (size == 0 || !search(x)) {//非空且存在才执行函数，否则直接就是“not found” 
		cout << "Not Found" << endl; 
		return;
	}
	int theindex = x % D;//初始位置 
	int index = theindex;//索引 
	int last = 0 ;//记录空的位置 
	int move = 0 ;
	if (table[index] == x) {
		table[index] = null;//直接清空 
		size--;
		last = index;//记录空位置 
		
		index = (index + 1) % D;

		int index0 = 0;
		int distance1=0 ,distance2=0; 
		while (table[index] !=null && index != theindex) {
			index0 = table[index] % D;//当前元素的初始位置 
			distance1 = index - index0;//当前元素位置到初始位置的距离 
			if (distance1 < 0)distance1 += D;

			distance2 = last - index0;//待补位置到初始位置的距离 
			if (distance2 < 0)distance2 += D;

			if (distance2 < distance1) {
				swap1(table[index], table[last]);//如果待补位置比较近，就元素前移 
				last = index;
				index = (index + 1) % D;
				move++;
			}
			else index = (index + 1) % D;
		}
		cout << move << endl;
	}
	else {
		do {
			index = (index + 1) % D;
		}while (table[index] != x );//直接找到x为止，因为函数开头的维护已经保证了x必存在 
		table[index] = null;
		size--;
		last = index;

		index = (index + 1) % D; 

		int index0 = 0;
		int distance1 = 0, distance2 = 0;
		while (table[index] != null && index != theindex) {//同上操作 
			index0 = table[index] % D;
			distance1 = index - index0;
			if (distance1 < 0)distance1 += D;

			distance2 = last - index0;
			if (distance2 < 0)distance2 += D;

			if (distance2 < distance1) {
				swap1(table[index], table[last]);
				last = index;
				index = (index + 1) % D;
				move++;
			}
			else index = (index + 1) % D;
		}
		cout << move << endl;
	}
}

template<class T>
void HashTable<T>::find(const T& x) {
	if (!search(x)){//先检查是否存在，不存在就跳出 
		cout << -1 << endl;
		return;
	}
	int theindex = x % D;
	int index = theindex;
	while (table[index] != null) {//只要非空就继续找，x必存在 
		if (table[index] == x) {
			cout << index << endl;
			return;
		}
		index = (index + 1) % D;
	}

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

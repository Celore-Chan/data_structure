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
	int theindex = x % D;//��λԪ�صĳ�ʼλ�ã�Ӧ���ڵ�λ�ã� 
	int index = theindex;//�ӳ�ʼλ�ÿ�ʼ���� 
	if (table[index] == null)return 0;
	if (table[index] == x)return 1;
	index = (index + 1) % D;
	while (table[index] != null&&index!=theindex) {//ֱ���ջ����»ص���ʼλ��Ϊֹ 
		if (table[index] == x) 
			return 1;
		index = (index + 1) % D;
	}
	return 0;//���ѭ���������ض�����ʧ�� 
}


template<class T>
void HashTable<T>::insert(const T& x) {
	if (search(x)) {//�Ȳ��ң��У��Ͳ��ò��� 
		cout << "Existed" << endl;
		return;
	}
	if (size == D)return;
	int theindex = x % D;//�ҵ���ʼλ�� 
	int index = theindex;
	if (table[theindex] == null) {//�վ�������� 
		table[theindex] = x;
		size++;
		cout << theindex<<endl;
	}
	else {
		do {//�ҵ���λ��Ϊֹ 
			index = (index + 1) % D;
		} while (table[index] != null );
		table[index] = x;
		size++;
		cout << index << endl;

	}
}

template<class T>
void HashTable<T>::erase(const T& x) {
	if (size == 0 || !search(x)) {//�ǿ��Ҵ��ڲ�ִ�к���������ֱ�Ӿ��ǡ�not found�� 
		cout << "Not Found" << endl; 
		return;
	}
	int theindex = x % D;//��ʼλ�� 
	int index = theindex;//���� 
	int last = 0 ;//��¼�յ�λ�� 
	int move = 0 ;
	if (table[index] == x) {
		table[index] = null;//ֱ����� 
		size--;
		last = index;//��¼��λ�� 
		
		index = (index + 1) % D;

		int index0 = 0;
		int distance1=0 ,distance2=0; 
		while (table[index] !=null && index != theindex) {
			index0 = table[index] % D;//��ǰԪ�صĳ�ʼλ�� 
			distance1 = index - index0;//��ǰԪ��λ�õ���ʼλ�õľ��� 
			if (distance1 < 0)distance1 += D;

			distance2 = last - index0;//����λ�õ���ʼλ�õľ��� 
			if (distance2 < 0)distance2 += D;

			if (distance2 < distance1) {
				swap1(table[index], table[last]);//�������λ�ñȽϽ�����Ԫ��ǰ�� 
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
		}while (table[index] != x );//ֱ���ҵ�xΪֹ����Ϊ������ͷ��ά���Ѿ���֤��x�ش��� 
		table[index] = null;
		size--;
		last = index;

		index = (index + 1) % D; 

		int index0 = 0;
		int distance1 = 0, distance2 = 0;
		while (table[index] != null && index != theindex) {//ͬ�ϲ��� 
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
	if (!search(x)){//�ȼ���Ƿ���ڣ������ھ����� 
		cout << -1 << endl;
		return;
	}
	int theindex = x % D;
	int index = theindex;
	while (table[index] != null) {//ֻҪ�ǿվͼ����ң�x�ش��� 
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

#include <iostream>
#include<string>
using namespace std;

class Contact {

	string num;
public:

	int dorm;
	string clas;
	string name;
	Contact() :name("0"), num("0"), clas("0"), dorm(0) {}
	~Contact() {}
	Contact& operator =(Contact& a) {
		this->name = a.name;
		this->clas = a.clas;
		this->dorm = a.dorm;
		this->num = a.num;
		return *this;
	}
	void insert();
	void edit();
};

class Array {
	Contact* list;
	int len;
	int size;
public:
	Array(int n) :len(n) ,size(0){ list = new Contact[n]; }
	~Array() { delete[] list; }
	bool insertin();
	bool deletin();
	bool editin();
	bool search();
	void outpc();
};

void Contact::insert() {
	string n, nu, c;
	int d;
	cin >> n;
	cin >> nu;
	cin >> c;
	cin >> d;
	name = n;
	num = nu;
	clas = c;
	dorm = d;
}

bool Array::insertin() {
	if (size < len) { 
		list[size].insert();//在末尾插入元素 
		size++;
		return 1;
	}
	else return 0;
}

bool Array::deletin() {
	string n;
	cin >> n;
	for (int i = 0; i < size; i++) {
		if (list[i].name == n) {//遍历到元素处 
			for (int j = i; j < size-1; j++) {
				list[j] = list[j + 1];//将后面的元素直接向前覆盖 
			}
			size--;
			return 1;
		}
	}
	return 0;
}

void Contact::edit() {
	int choice = 0;
	cin >> choice;
	switch (choice) {
	case 1:
		cin >> num;
		break;
	case 2:
		cin >> clas;
		break;
	case 3:
		cin >>dorm;
		break;
	}
}

bool Array::editin() {
	string n;
	cin >> n;
	for (int i = 0; i < size; i++) {
		if (list[i].name == n) {//遍历到元素后调用编辑函数 
			list[i].edit();
			return 1;
		}
	}
	return 0;
}

bool Array::search() {
	string n;
	cin >> n;
	for (int i = 0; i < size; i++) {
		if (list[i].name == n)return 1;
	}
	return 0;
}

void Array::outpc() {
	string c;
	cin >> c;
	int res = 0;
	for (int i = 0; i < size; i++) {
		if (list[i].clas == c)res ^= list[i].dorm;
	}
	cout << res << endl;
}

int main() {
	
	int cnt = 0;
	cin >> cnt;
	Array a(cnt);
	do {
		int choice = -1;
		cin >> choice;
		if (choice < 0 || choice>4)continue;
		switch (choice) {
		case 0:
			a.insertin();
			cnt--;
			break;
		case 1:
			a.deletin();
			cnt--;
			break;
		case 2:
			a.editin();
			cnt--;
			break;
		case 3:
			if (a.search())cout << 1 << endl;
			else cout << 0 << endl;
			cnt--;
			break;
		case 4:
			a.outpc();
			cnt--;
			break;
		}

	} while (cnt > 0);

	return 0;
}

#include<iostream>
#include<iomanip>
using namespace std;

template<class T>
class Queue {
	T* element ;
	int size ;
	int length ;
	int theFront ;
	int theEnd ;
public:
	Queue():element(NULL),size(0),length(0),theFront(0),theEnd(1){}
	Queue(int n):element(NULL),size(0),length(n),theFront(0),theEnd(1) {
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
void Queue<T>::outp() {
	while (!empty()) {
		cout << top() << " ";
		pop();
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	Queue<int> cards(n);
	for (int i = 1; i <= n; i++)
		cards.push(i);//从小到大开始排队 
	while (cards.QueueSize() > 1) {//先删后插 
		cards.pop();
		cards.push(cards.top());
		cards.pop();
	}
	cout << cards.top() << endl;//直接输出牌顶元素 

	return 0;
}

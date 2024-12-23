#include<iostream>
using namespace std;

template<class T>
void swap1(T& a, T& b) {//交换 
	T t = a;
	a = b;
	b = t;
}

template<class T>
int max(T* a, int n)//找出数组中最大的数，返回index 
{
	int b = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= a[b])
			b = i;
	}
	return b;
}

template<class T>
class sort
{
public:
	void ranksort(T* a, int n);
	void selectsort(T* a, int n);
	bool bubblesort(T* a, int n);
	void insertsort(T* a, int n);
};

template<class T>
void sort<T>::ranksort(T*a,int n)
{
	int* b = new int[n];
	for (int i = 0; i < n; i++)
	{
		b[i] = 0;
	}
	for (int i = 1; i < n; i++)//二重循环，从第一个开始比较，比较它的后面的数，大就排位加一 
	{
		for (int j = 0; j < i; j++)
		{
			if (a[i] <= a[j])
				b[j]++;
			else
				b[i]++;
		}
	}
	T *u=new T[n];
	for(int i=0;i<n;i++){//按排位安插在新数组里 
		u[b[i]]=a[i];
	}
	for(int i=0;i<n;i++){
		a[i]=u[i];
	}
	delete[] b,u;
}

template<class T>
void sort<T>::selectsort(T* a, int n)
{
	for (int i = n-1; i >0; i--) {//从数组最末尾开始排，先找出数组中最大值，让它和最末尾交换，每做完一次找最大值函数的size--，因为最末尾已经排好 
		swap1(a[i], a[max(a,n--)]);
	}
}//n*(n+1)/2 (n^2)

template<class T>
bool bubble(T* a, int n) {
	int flag = 1;
	for (int i = 0; i < n - 1; i++) {//遍历数组，前者大则交换 
		if (a[i] > a[i + 1]) {
			swap1(a[i], a[i + 1]);
			flag = 0;
		}
	}
	return flag;
}

template<class T>
bool sort<T>::bubblesort(T*a,int n)
{
	for (int i = 0; i < n; i++) {//由于每进行一次bubble肯定能把最大值排在末尾， 所以size减去循环次数即可 
		if (bubble(a, n - i))return 1;
	}
	return 1;
}

template<class T>
void insert(T* a,T x,int n){
	int i;
	for (i = n - 1; i >= 0 && x < a[i]; i--)//从末尾开始排，若比所排数小则后移，大则插入 
		a[i + 1] = a[i];
	a[i + 1] = x;
}

template<class T>
void sort<T>::insertsort(T* a, int n)
{
	int* b = new int[n];
	int size=1;
	b[0]=a[0];
	for(int i=1;i<n;i++){//插入新数组中即可 
		insert(b,a[i],size++);
	}
	for(int i=0;i<n;i++){
		a[i]=b[i];
	}
	delete b;
}

int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sort<int> p;
	p.bubblesort(a, n);
	for (int i = 0; i <n; i++)
	{
		cout << a[i] <<" ";
	}
}

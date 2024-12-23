#include <iostream>
#include<math.h>
using namespace std;

int cnt = 0;

void swap(int& a, int& b) {//交换 
	int t = a;
	a = b;
	b = t;
}

void qpl(int a[], int k, int n) { //全排列
	if (k == n) {//当交换进行到最后，意味着一次全排列实现，此时计算结果 
		int res = 0;
		for (int i = 0; i < n; i++) {
			res += a[i] ^ (i + 1);
		}
		cnt = cnt|res;
	}
	else {
		for (int i = k; i <n; i++) {//全排列交换 
			swap(a[i], a[k]);
			qpl(a, k + 1, n);
			swap(a[i], a[k]);
		}
	}
}

int main() {
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin>>a[i];
	}
	qpl(a, 0, n);
	cout<<cnt;
	
	return 0;
}

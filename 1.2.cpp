#include <iostream>
#include<math.h>
using namespace std;

int cnt = 0;

void swap(int& a, int& b) {//���� 
	int t = a;
	a = b;
	b = t;
}

void qpl(int a[], int k, int n) { //ȫ����
	if (k == n) {//���������е������ζ��һ��ȫ����ʵ�֣���ʱ������ 
		int res = 0;
		for (int i = 0; i < n; i++) {
			res += a[i] ^ (i + 1);
		}
		cnt = cnt|res;
	}
	else {
		for (int i = k; i <n; i++) {//ȫ���н��� 
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

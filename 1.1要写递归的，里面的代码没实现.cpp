#include <iostream>
#include<math.h>
using namespace std;

long val=0;

int main() {
	int n;
	cin >> n;
	long* a = new long[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	long cnt = pow(2, n);
	int* flag = new int[n];
	for (long z = 0; z < cnt; z++) {
		long i = 0, note = 0,res1=z,ct=1;
		do {
			flag[i] = res1 % 2;	
			if (flag[i] == 1) { note += a[i] * ct ; ct++; }//ѡ�о���ȡ��ֵ 
			res1/=2;
			i++;
		} while (res1 != 0);//������� ��һ��whileѭ������ һ���Ӽ� 
		val^=note;//һ��forѭ������һ���Ӽ���ֵ 
	}
	cout<<val<<endl;

	return 0;
}

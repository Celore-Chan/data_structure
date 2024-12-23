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
			if (flag[i] == 1) { note += a[i] * ct ; ct++; }//选中就提取价值 
			res1/=2;
			i++;
		} while (res1 != 0);//背包组合 ，一次while循环就是 一格子集 
		val^=note;//一次for循环就是一个子集价值 
	}
	cout<<val<<endl;

	return 0;
}

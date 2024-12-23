#include<iostream>
#include<iomanip>
using namespace std;

template<class T>
class Stack {
	int len = 0;
	int size = 0;
	T* element = nullptr;
	int hp = 0;
public:
	Stack() {}
	Stack(int n) {
		len = n;
		element = new T[n];
		hp = 0;
	}
	~Stack() {
		delete[] element;
	}
	bool empty() {
		return size == 0;
	}
	int listsize() {
		return size;
	}
	T& top() {
		return element[size - 1];
	}
	void pop() {//ֱ��size--���ɣ������Ļ���ɾ���ݾͲ��ڿ������ݵķ�Χ�� 
		if (empty())return;
		size--;
	}
	void push(const T& x) {//����ͷ�� 
		if (listsize() == len)return;
		element[size] = x;
		size++;
	}


};

double trans(const char& c) {//���ַ�ת����double 
	switch (c) {
	case '1':
		return 1;
		break;
	case'2':
		return 2;
		break;
	case'3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case '0':
		return 0;
		break;
	}
}

bool num(const char& c) {//�ж��ǲ������� 
	if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0')return 1;
	else return 0;

}

bool ifoperators(const char& c) {//�ж��ǲ�������� 
	if (c == '+' || c == '-' || c == '*' || c == '/')return 1;
	else return 0;
}

int operators(const char& c) {//������� 
	if (c == '+')return 1;
	else if (c == '-')return 2;
	else if (c == '*')return 3;
	else if (c == '/')return 4;

	else return 0;
}

int incomp(const char& c) {//����ּ� 
	if (c == '+')return 1;
	else if (c == '-')return 1;
	else if (c == '*')return 2;
	else if (c == '/')return 2;
	else return 3;
}

bool comp(const char& inside, const char& outside) {//�ж�ջ��������ǲ��Ǳ�Ҫ����������С 
	if (incomp(inside) < incomp(outside))return 1;
	else return 0;
}

int main() {
	
	//Stack<float> numstack(2000);
	int steps = 0;
	bool flag = 0;
	char bin;
	scanf("%d", &steps);
	scanf("%c", &bin);
	char val;
	double l = 0, r = 0, result = 0;
	for (int i = 0; i < steps; i++) {
		Stack<double> nums(2000);
		nums.push(0);
		Stack<char> oprt(2000);
		oprt.push('+');
		do {

			scanf("%c", &val);
			if (num(val)) {
				nums.push(trans(val));
				if (flag) {//��flagΪ1ʱ������һ��������Ĳ���ȼ���ǰһ���ߣ��������� 
					r = nums.top();
					nums.pop();
					l = nums.top();
					nums.pop();
					switch (operators(oprt.top()))
					{
					case 3:
						result = l * r;
						nums.push(result);
						break;
					case 4:
						result = l / r;
						nums.push(result);
						break;
					default:
						break;
					}
					oprt.pop();
					flag = 0;
				}
			}
			else if (ifoperators(val)) {
				if (oprt.empty()) oprt.push(val);
				else if (comp(oprt.top(), val)) {//�жϺ�һ����ջ���ȼ� 
					flag = 1;
					oprt.push(val);
				}
				else if (incomp(oprt.top()) == incomp(val)) {//�жϺ�һ����ջ���ȼ�����ʱ��ȣ���ʱ��������ջ��������� 
					r = nums.top();
					nums.pop();
					l = nums.top();
					nums.pop();
					char tmp = oprt.top();
					oprt.pop();
					switch (operators(tmp))
					{
					case 1:
						result = l + r;
						nums.push(result);
						break;
					case 2:
						result = l - r;
						nums.push(result);
						break;
					case 3:
						result = l * r;
						nums.push(result);
						break;
					case 4:
						result = l / r;
						nums.push(result);
						break;
					default:
						break;
					}
					oprt.push(val);
				}
				else {
					oprt.push(val);
				}
			}
			else if (val == '(') {//����ǰ���žͰ�flag=0����������жϵȼ� 
				flag = 0;
				oprt.push(val);
				nums.push(0);
				oprt.push('+');
			}
			else if (val == ')') {//����������������ǰ���㣨����ջ����ֱ����������������� 
				do {
					val = oprt.top();
					oprt.pop();
					r = nums.top();
					nums.pop();
					l = nums.top();
					nums.pop();
					switch (operators(val))
					{
					case 1:
						result = l + r;
						nums.push(result);
						break;
					case 2:
						result = l - r;
						nums.push(result);
						break;
					case 3:
						result = l * r;
						nums.push(result);
						break;
					case 4:
						result = l / r;
						nums.push(result);
						break;
					default:
						break;
					}
					val = oprt.top();

				} while (val != '(');
				oprt.pop();
				if (oprt.top() == '*' || oprt.top() == '/') {//����������Ա���* /���������� 
					val = oprt.top();
					oprt.pop();
					r = nums.top();
					nums.pop();
					l = nums.top();
					nums.pop();
					switch (operators(val))
					{
					case 3:
						result = l * r;
						nums.push(result);
						break;
					case 4:
						result = l / r;
						nums.push(result);
						break;
					default:
						break;
					}
				}
			}
		} while (val != ' ' && val != '\n');
		while (nums.listsize() > 1) {//����ʣ�µ�������� 
			val = oprt.top();
			oprt.pop();
			r = nums.top();
			nums.pop();
			l = nums.top();
			nums.pop();
			switch (operators(val))
			{
			case 1:
				result = l + r;
				nums.push(result);
				break;
			case 2:
				result = l - r;
				nums.push(result);
				break;
			case 3:
				result = l * r;
				nums.push(result);
				break;
			case 4:
				result = l / r;
				nums.push(result);
				break;
			default:
				break;
			}
		}
		printf("%.2lf\n",result);
	}

	return 0;
}

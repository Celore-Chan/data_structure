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
	void pop() {//直接size--即可，这样的话被删数据就不在可用数据的范围内 
		if (empty())return;
		size--;
	}
	void push(const T& x) {//正常头插 
		if (listsize() == len)return;
		element[size] = x;
		size++;
	}


};

double trans(const char& c) {//把字符转换成double 
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

bool num(const char& c) {//判断是不是数字 
	if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0')return 1;
	else return 0;

}

bool ifoperators(const char& c) {//判断是不是运算符 
	if (c == '+' || c == '-' || c == '*' || c == '/')return 1;
	else return 0;
}

int operators(const char& c) {//运算分类 
	if (c == '+')return 1;
	else if (c == '-')return 2;
	else if (c == '*')return 3;
	else if (c == '/')return 4;

	else return 0;
}

int incomp(const char& c) {//运算分级 
	if (c == '+')return 1;
	else if (c == '-')return 1;
	else if (c == '*')return 2;
	else if (c == '/')return 2;
	else return 3;
}

bool comp(const char& inside, const char& outside) {//判断栈顶运算符是不是比要插入的运算符小 
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
				if (flag) {//当flag为1时，即上一个运算符的插入等级比前一个高，立马运算 
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
				else if (comp(oprt.top(), val)) {//判断后一个与栈顶等级 
					flag = 1;
					oprt.push(val);
				}
				else if (incomp(oprt.top()) == incomp(val)) {//判断后一个与栈顶等级，此时相等，这时就先运算栈顶的运算符 
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
			else if (val == '(') {//遇到前括号就把flag=0，避免错误判断等级 
				flag = 0;
				oprt.push(val);
				nums.push(0);
				oprt.push('+');
			}
			else if (val == ')') {//遇到右括号立马往前运算（调用栈），直到遇到最近的左括号 
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
				if (oprt.top() == '*' || oprt.top() == '/') {//如果左括号旁边是* /，进行运算 
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
		while (nums.listsize() > 1) {//最后把剩下的运算完成 
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

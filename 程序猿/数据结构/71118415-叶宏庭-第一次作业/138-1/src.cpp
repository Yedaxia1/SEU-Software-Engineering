#include <iostream>

using namespace std;

template<class T>
class Stack {
public:
	Stack(int c)
	{
		capacity = c;
		myStack = new T[capacity];
		top = -1;
	}
	void Push(T &a)
	{
		if (top == capacity - 1)//ջ�������¿����ռ�
		{
			T *temp = new T[capacity*2];  //doubleing �ռ�
			for (int i = 0; i < capacity; i++)
				temp[i] = myStack[i];//����ԭ������
			capacity *= 2;
			myStack = new T[capacity];
			for (int i = 0; i < capacity/2; i++)
				myStack[i] = temp[i];//��ԭԭ������
		}
		myStack[++top] = a;
	}
	T &Pop()
	{
		return myStack[top--];
	}
	T &Top()
	{
		return myStack[top];
	}
	void outputStack()
	{
		for (int i = 0; i <= top; i++)
			cout << myStack[i] << " ";
		cout << endl;
	}
	Stack & Divide()
	{
		Stack c(capacity / 2);//����һ���С�Ŀռ�
		for (int i = capacity / 2; i < capacity; i++)//���ѹջ����
		{
			c.Push(myStack[i]);
			top--;
		}
		capacity /= 2;
		return c;//���η��أ�this��Ϊǰ���
	}
	Stack & Combine(Stack &a)
	{
		Stack c(capacity + a.capacity);
		for (int i = 0; i < capacity; i++)//�ȸ���this������
			c.Push(myStack[i]);
		for (int i = 0; i < a.capacity; i++)//�ڸ���a������
			c.Push(a.myStack[i]);
		return c;//���ϳɵ�ջ���ء�
	}
private:
	int capacity;
	T *myStack;
	int top;
};

int main()
{
	Stack<int> s1(4);
	cout << "Enter your num to push stack(-1 to end)" << endl;
	int x;
	cin >> x;
	while (x != -1)
	{
		s1.Push(x);
		cin >> x;
	}
	cout << "your stack is:";
	s1.outputStack();
	Stack<int> s2 = s1.Divide();
	cout << "After divide is:";
	s1.outputStack();
	cout << "Another divide is:";
	s2.outputStack();
	Stack<int> s3 = s1.Combine(s2);
	cout << "Combine the two stacks is:";
	s3.outputStack();
	system("pause");
}

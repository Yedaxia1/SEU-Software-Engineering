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
		if (top == capacity - 1)//栈满，重新开创空间
		{
			T *temp = new T[capacity*2];  //doubleing 空间
			for (int i = 0; i < capacity; i++)
				temp[i] = myStack[i];//复制原有数据
			capacity *= 2;
			myStack = new T[capacity];
			for (int i = 0; i < capacity/2; i++)
				myStack[i] = temp[i];//还原原有数据
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
		Stack c(capacity / 2);//开创一半大小的空间
		for (int i = capacity / 2; i < capacity; i++)//逐个压栈后半段
		{
			c.Push(myStack[i]);
			top--;
		}
		capacity /= 2;
		return c;//后半段返回，this变为前半段
	}
	Stack & Combine(Stack &a)
	{
		Stack c(capacity + a.capacity);
		for (int i = 0; i < capacity; i++)//先复制this的数据
			c.Push(myStack[i]);
		for (int i = 0; i < a.capacity; i++)//在复制a的数据
			c.Push(a.myStack[i]);
		return c;//将合成的栈返回。
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

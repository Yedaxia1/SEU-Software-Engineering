#include <iostream>

using namespace std;
template<class T>
class Stack {//栈类，用于遍历tree
private:
	T * term;
	int capacity;
	int top;
public:
	Stack(int a=100)
	{
		capacity = a;
		top = -1;
		term = new T[capacity];
	}
	void Push(T &a)
	{
		term[++top] = a;
	}
	void Pop()
	{
		term[top--].~T();
	}
	T & Top()
	{
		return term[top];
	}
	void Get()
	{
		for (int i = 0; i <= top; i++)
			cout << term[i] << "  ";
		cout << endl;
	}
	bool IsEmpty()
	{
		if (top == -1)
			return true;
		return false;
	}
};

template<class T>
class Tree;

template<class T>
class TreeNode {
	friend class Tree<T>;
private:
	T data;//结点数据
	TreeNode<T> *leftChlid;//左孩子
	TreeNode<T> *rightChlid;//右孩子
public:
	TreeNode(T a=NULL) { data = a; }
};

template<class T>
class Tree {
private:
	TreeNode<T> *root;//根结点
public:
	Tree(TreeNode<T> *a) { root = a; }
	bool IsEmpty()//判断tree是否为空
	{
		if (!root)
			return true;
		return false;
	}
	//插入结点，根据数组a的值来决定插入位置，
	//具体规则：0代表左子树，1代表右子树，如a={0，1，0}代表插入到root.leftChild.rightChild.leftChild的位置。
	//m为要插入的结点
	void InsertNode(char a[],int size,TreeNode<T> *m)
	{
		TreeNode<T> *currentNode = root;
		if (size == 1)
		{
			if (a[0] == 0)
				currentNode->leftChlid = m;
			else
				currentNode->rightChlid = m;
			return;
		}
		for (int i = 0; i < size -1; i++)
		{
			if (a[i] == 0)
				currentNode = currentNode->leftChlid;
			else
				currentNode = currentNode->rightChlid;
		}
		if (a[size - 1] == 0)
			currentNode->leftChlid = m;
		else
			currentNode->rightChlid = m;
	}
	void Visit(TreeNode<T> *m)//访问某一个结点
	{
		cout<<m->data<<" ";
	}
	TreeNode<T> *GetRoot()
	{
		return root;
	}
	class InorderIterator {//内部类（迭代器）
	public:
		InorderIterator(TreeNode<T> *root) { currentNode = root; }
		T* Next()//获得下一个结点
		{
			while (currentNode)//判断currentNode是否为空
			{
				s.Push(currentNode);//压栈
				currentNode = currentNode->leftChlid;//currentNode指向左孩子
			}
			if (s.IsEmpty()) return 0;//判断栈是否为空，栈空则遍历完毕
			currentNode = s.Top();//获取栈顶元素
			s.Pop();//出栈
			T& temp = currentNode->data;//访问本次访问的数据区域
			currentNode = currentNode->rightChlid;//currentNode指向右孩子
			return &temp;
		}
	private:
		Stack<TreeNode<T>*>  s;
		TreeNode<T> *currentNode;
	} ;
};

int main()
{
	//插入结点时使用的数组
	char a1[] = { 0};
	char a2[] = { 1};
	char a3[] = { 0 , 0};
	char a4[] = { 0 , 1};
	char a5[] = { 1 , 0};

	//创建root结点
	TreeNode<int> *r=new TreeNode<int>(4);

	//以root结点为根，创建树
	Tree<int> *myTree=new Tree<int>(r);
	
	//插入结点到树中
	myTree->InsertNode(a1, 1, new TreeNode<int>(2));
	myTree->InsertNode(a2, 1, new TreeNode<int>(6));
	myTree->InsertNode(a3, 2, new TreeNode<int>(1));
	myTree->InsertNode(a4, 2, new TreeNode<int>(3));
	myTree->InsertNode(a5, 2, new TreeNode<int>(5));

	//创建迭代器
	Tree<int>::InorderIterator i1(myTree->GetRoot());
	cout << "Traverse by InnerIterator (in inorder):";

	//遍历树
	int *temp = i1.Next();
	while (temp != 0)
	{
		cout << *temp << " ";
		temp = i1.Next();
	}
	system("pause");
	return 0;
}
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
class MyQueue {
private:
	T *term;
	int front;
	int rear;
	int capacity;
public:
	MyQueue(int s=100)
	{
		capacity = s;
		term = new T[capacity];
		front = rear = 0;
	}
	bool IsEmpty()
	{
		if (front == rear == 0)
			return true;
		return false;
	}
	void Push(T &a)
	{
		term[rear++] = a;
	}
	T & Front()
	{
		return term[front];
	}
	void Pop()
	{
		term[front++].~T();
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
	~Tree()
	{
		InorderIterator i1(root);
		TreeNode<T> * temp;
		while (temp = i1.Next())
			delete temp;
	}
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
	void CreatByArray(T arrays[],int size)
	{
		MyQueue<TreeNode<T> *> qc;
		TreeNode<T> *currentNode = root;
		int sub = 1;
		while (1)
		{
			if (sub == size)
				return;
			currentNode->data = arrays[sub];
			if (sub * 2 < size)
			{
				currentNode->leftChlid = new TreeNode<T>();
				qc.Push(currentNode->leftChlid);
			}
			if (sub * 2 + 1 < size)
			{
				currentNode->rightChlid = new TreeNode<T>();
				qc.Push(currentNode->rightChlid);
			}
			currentNode = qc.Front();
			qc.Pop();
			sub++;
		}
	}
	int LeafNodeNumber()//获取叶子结点个数
	{
		InorderIterator i1(root);//创建迭代器
		int counter = 0;//计数
		TreeNode<T> * temp;
		while (temp = i1.Next())//使用迭代器遍历
		{
			if (!temp->leftChlid)//若当前结点不存在左孩子，则该结点为叶子结点
				counter++;
		}
		return counter;
	}
	//非递归前序遍历
	void nonrecursivePreorder()
	{
		Stack<TreeNode<T>*>  s;
		TreeNode<T> *currentNode = root;
		while (1)
		{
			while (currentNode)
			{
				if (currentNode->rightChlid)//若当前结点存在rightChlid，则将rightChlid压栈，以便leftChild访问完毕后，可以从栈中取出rightChild
					s.Push(currentNode->rightChlid);
				Visit(currentNode);//前序遍历，先访问当前结点
				currentNode = currentNode->leftChlid;//结点左移
			}
			if (s.IsEmpty()) return;
			currentNode = s.Top();//从栈中取出最近一次存在的rightChild
			s.Pop();//取出最近的rightChild后，出栈
		}
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
		Stack<TreeNode<T>*>  s;
		T* NextData()//获得下一个结点
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
		TreeNode<T> * Next()
		{
			while (currentNode)//判断currentNode是否为空
			{
				s.Push(currentNode);//压栈
				currentNode = currentNode->leftChlid;//currentNode指向左孩子
			}
			if (s.IsEmpty()) return 0;//判断栈是否为空，栈空则遍历完毕
			currentNode = s.Top();//获取栈顶元素
			s.Pop();//出栈
			TreeNode<T> * temp = currentNode;//
			currentNode = currentNode->rightChlid;//currentNode指向右孩子
			return temp;
		}
	private:
		TreeNode<T> *currentNode;
	} ;
};

int main()
{
	////插入结点时使用的数组
	//char a1[] = { 0};
	//char a2[] = { 1};
	//char a3[] = { 0 , 0};
	//char a4[] = { 0 , 1};
	//char a5[] = { 1 , 0};

	////创建root结点
	//TreeNode<int> *r=new TreeNode<int>(4);

	////以root结点为根，创建树
	//Tree<int> *myTree=new Tree<int>(r);
	//
	////插入结点到树中
	//myTree->InsertNode(a1, 1, new TreeNode<int>(2));
	//myTree->InsertNode(a2, 1, new TreeNode<int>(6));
	//myTree->InsertNode(a3, 2, new TreeNode<int>(1));
	//myTree->InsertNode(a4, 2, new TreeNode<int>(3));
	//myTree->InsertNode(a5, 2, new TreeNode<int>(5));

	////创建迭代器
	//Tree<int>::InorderIterator i1(myTree->GetRoot());
	//cout << "Traverse by InnerIterator (in inorder):";

	////中序遍历树
	//int *temp = i1.Next();
	//while (temp != 0)
	//{
	//	cout << *temp << " ";
	//	temp = i1.Next();
	//}

	////前序遍历
	//myTree->nonrecursivePreorder();
	TreeNode<int> *r = new TreeNode<int>();
	Tree<int> *myTree = new Tree<int>(r);

	int myArray[] = { 0,1,2,3,4,5,6,7,8 };
	myTree->CreatByArray(myArray, sizeof(myArray) / sizeof(int));//使用数组创建树
	cout << "The tree is (preorder):";
	myTree->nonrecursivePreorder();//打印树
	myTree->~Tree();//析构
	system("pause");
	return 0;
}
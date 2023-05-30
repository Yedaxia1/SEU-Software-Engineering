#include <iostream>

using namespace std;

template<class T>
class Stack {//栈类，用于遍历tree
private:
	T * term;
	int capacity;
	int top;
public:
	Stack(int a = 100)
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
	MyQueue(int s = 100)
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
	bool leftThread;
	bool rightThread;
	TreeNode<T> *leftChlid;//左孩子
	TreeNode<T> *rightChlid;//右孩子
public:
	TreeNode(T a=NULL) 
	{ 
		data = a;
		leftThread = rightThread = false;
	}
};

template<class T>
class Tree {
private:
	TreeNode<T> * root;//根结点
public:
	Tree(TreeNode<T> *a)
	{
		root = new TreeNode<T>();
		root->rightChlid = root;	
		root->leftChlid = a;
	}
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
	void CreatByArray(T arrays[],int size)
	{
		MyQueue<TreeNode<T> *> qc;
		TreeNode<T> *currentNode = root->leftChlid;
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
	void CreatThread()
	{
		InorderIterator i1(root->leftChlid, root);
		TreeNode<T> *temp2=root;
		TreeNode<T> *temp3=i1.Next();
		TreeNode<T> *temp1 =temp3;
		while (1)
		{
			temp3 = i1.Next();
			if (!temp1->leftChlid)
			{
				temp1->leftThread = true;
				temp1->leftChlid = temp2;
			}
			if (!temp1->rightChlid)
			{
				temp1->rightThread = true;
				temp1->rightChlid = temp3;
			}
			if (!temp3)
				break;
			temp2 = temp1;
			temp1 = temp3;
		}
		temp1->rightChlid = root;
	}
	void InsertNodeAfterS(TreeNode<T> *s, TreeNode<T> *a)
	{
		InorderIterator i1(root->leftChlid, root);
		TreeNode<T> *temp = i1.NextData();
		while (temp)
		{
			if (temp->data == s->data)
				break;
			temp = i1.NextData();
		}
		a->leftChlid = temp->leftChlid;
		a->leftThread = temp->leftThread;
		a->rightChlid = temp;
		a->rightThread = true;
		temp->leftChlid->rightChlid = a;
		temp->leftChlid = a;
		temp->leftThread = false;
	}
	void GetTree()
	{
		InorderIterator i1(root->leftChlid,root);
		TreeNode<T> *  temp = i1.NextData();
		while (temp)
		{
			cout << temp->data << " ";
			temp = i1.NextData();
		}
			
	}
	int LeafNodeNumber()//获取叶子结点个数
	{
		InorderIterator i1(root->leftChlid,root);//创建迭代器
		int counter = 0;//计数
		TreeNode<T> * temp;
		while (temp = i1.Next())//使用迭代器遍历
		{
			if (!temp->leftChlid)//若当前结点不存在左孩子，则该结点为叶子结点
				counter++;
		}
		return counter;
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
		InorderIterator(TreeNode<T> *r, TreeNode<T> *r1) { currentNode = r; root1 = currentNode2 = r1; }
		Stack<TreeNode<T>*>  s;
		TreeNode<T> * NextData()//获得下一个结点
		{
			TreeNode<T> *temp = currentNode2->rightChlid;
			if (!currentNode2->rightThread)
				while (!temp->leftThread) temp = temp->leftChlid;
			currentNode2 = temp;
			if (currentNode2 == root1) return 0;
			else return currentNode2;
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
		TreeNode<T> *root1;
		TreeNode<T> *currentNode;
		TreeNode<T> *currentNode2;
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
	myTree->CreatThread();
	cout << "Initial tree(inorder):";
	myTree->GetTree();
	cout << endl;
	myTree->InsertNodeAfterS(new TreeNode<int>(5), new TreeNode<int>(9));
	cout << "Insert 9 after 5, the tree is:";
	myTree->GetTree();
	system("pause");
	return 0;
}
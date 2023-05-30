#include <iostream>
#include <string>

using namespace std;

class TreeNode {
public:
	TreeNode()
	{
		key = -1;
		value = 1000;
	}
	TreeNode(int k, int v)
	{
		key = k;
		value = v;
	}
	int key;
	int value;
};

class WinnerTree {
public:
	WinnerTree()
	{
		terms = new TreeNode[16];
	}
	TreeNode GetTop()
	{
		return terms[0];
	}
	//插入下一个元素，即已经取走第一个数，接下来进行第二次取数
	void InsertNode(int k, TreeNode &a)
	{//k表示来自那个序列
		int sub = k + 7;
		//插入新元素
		terms[sub] = a;
		//循环比较，对树重构
		while (sub >= 1)
		{
			//若该点为偶序列，则兄弟为sub+1
			if (sub % 2 == 0)
			{
				//若新元素优先级>兄弟的优先级（因为为升序排序，所以数小，优先级反倒大），父亲更新为新元素
				if (a.value < terms[sub + 1].value)
				{
					sub /= 2;
					terms[sub] = a;
				}
				else {//若新元素优先级<兄弟的优先级，则不在更新
					a = terms[sub + 1];
					terms[sub / 2] = terms[sub + 1];
					sub /= 2;
				}
			}
			else {//若该点为奇序列，则兄弟为sub-1
				//以下操作同上，仅是因为兄弟下标计算不同，所以有if，else操作。
				if (a.value < terms[sub - 1].value)
				{
					sub /= 2;
					terms[sub] = a;
				}
				else {
					a = terms[sub - 1];
					terms[sub / 2] = terms[sub - 1];
					sub /= 2;
				}
			}
		}
		terms[0] = terms[1];
	}
private:
	TreeNode *terms;
};

class LoserTree {
public:
	LoserTree()
	{
		terms = new TreeNode[16];
		for (int i = 0; i < 16; i++)
			terms[i].value = -5;
	}
	TreeNode GetTop()
	{
		return terms[0];
	}
	//插入下一个元素，即已经取走第一个数，接下来进行第二次取数
	void InsertNode(int k, TreeNode &a)
	{//k表示来自那个序列
		int sub = k + 7;
		//插入新元素
		terms[sub] = a;
		TreeNode temp;
		//循环比较，对树重构
		while (sub > 1)
		{
			//若新元素优先级>父节点优先级，则新元素继续往上爬
			if (a.value < terms[sub / 2].value)
				sub /= 2;
			else//若新元素优先级<父节点优先级，则新元素放入父节点位置，父节点元素继续往上爬
			{
				temp = terms[sub / 2];
				terms[sub / 2] = a;
				a = temp;
				sub /= 2;
			}
			if (sub == 1)
				terms[0] = a;
		}
	}
private:
	TreeNode *terms;
};

void main()
{
	//创建8个结点
	TreeNode n1(1, 10);
	TreeNode n2(2, 9);
	TreeNode n3(3, 20);
	TreeNode n4(4, 15);
	TreeNode n5(5, 8);
	TreeNode n6(6, 9);
	TreeNode n7(7, 90);
	TreeNode n8(8, 17);

	//创建胜者树，并依次加入8个结点
	WinnerTree t1;
	t1.InsertNode(n1.key, n1);
	t1.InsertNode(n2.key, n2);
	t1.InsertNode(n3.key, n3);
	t1.InsertNode(n4.key, n4);
	t1.InsertNode(n5.key, n5);
	t1.InsertNode(n6.key, n6);
	t1.InsertNode(n7.key, n7);
	t1.InsertNode(n8.key, n8);

	//创建败者树，加入结点
	LoserTree t2;
	t2.InsertNode(n1.key, n1);
	t2.InsertNode(n2.key, n2);
	t2.InsertNode(n3.key, n3);
	t2.InsertNode(n4.key, n4);
	t2.InsertNode(n5.key, n5);
	t2.InsertNode(n6.key, n6);
	t2.InsertNode(n7.key, n7);
	t2.InsertNode(n8.key, n8);
	return;
}
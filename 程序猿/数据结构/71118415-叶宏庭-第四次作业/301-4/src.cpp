#include <iostream>
#include <string>

using namespace std;

class TreeNode {
public:
	TreeNode()
	{
		key = -1;
		value = -5;
	}
	TreeNode(int k, int v)
	{
		key = k;
		value = v;
	}
	int key;
	int value;
};

class LoserTree {
public:
	LoserTree(int k,TreeNode *a)
	{
		terms = new TreeNode[2*k];
		for (int i = 1; i <= k; i++)
		{
			InsertNode(i, a[i - 1]);
		}
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
	TreeNode *a = new TreeNode[8]{
		TreeNode(1, 10),
		TreeNode(2, 9),
		TreeNode(3, 20),
		TreeNode(4, 15),
		TreeNode(5, 8),
		TreeNode(6, 9),
		TreeNode(7, 90),
		TreeNode(8, 17)
	};

	//创建败者树，加入结点
	LoserTree t2(8,a);
	
	return;
}
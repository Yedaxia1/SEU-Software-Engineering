#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Vertice {
public:
	Vertice()
	{
		value = ++n;
		next = NULL;
	}
	Vertice(Vertice &v)
	{
		value = v.GetValue();
		next = NULL;
	}
	Vertice(int v) { value = v; next = NULL;}
	int GetValue() { return value; }
	Vertice* next;
private:
	static int n;
	int value;
};
int Vertice::n = 0;

class Graph {
public:
	Graph(int numofV)
	{
		capacity = numofV;
		myVertice = new Vertice[capacity];
	}
	//往图中加入边(v1,v2代表两个顶点)
	void inputEdge(Vertice v1, Vertice v2)
	{
		//获取v1,v2对应链表
		Vertice *temp1 = &myVertice[v1.GetValue()-1];
		Vertice *temp2 = &myVertice[v2.GetValue()-1];

		//若存在next，则后移（将新来的顶点加入到链表末尾），此处将v2插入v1的链末
		while (temp1->next)
		{
			temp1 = temp1->next;
		}
		temp1->next = new Vertice(v2.GetValue());

		//若存在next，则后移（将新来的顶点加入到链表末尾），此处将v1插入v2的链末
		while (temp2->next)
		{
			temp2 = temp2->next;
		}
		temp2->next = new Vertice(v1.GetValue());
	}
	//输出邻接表
	void GetLists()
	{
		for (int i = 0; i < capacity; i++)
		{
			Vertice *temp1 = &myVertice[i];
			while (temp1->next)
			{
				cout << temp1->GetValue() << "-->";
				temp1 = temp1->next;
			}
			cout << temp1->GetValue() << endl;
		}
	}
	void DFS() {
		visited = new bool[capacity];
		for (int i = 0; i < capacity; i++)
			visited[i] = false;
		DFS(0);
		delete[]visited;
	}
	void DFS(const int n) {
		visited[n] = true;
		cout << n+1 << "  ";
		Vertice *temp = &myVertice[n];
		while (temp->next)
		{
			if (!visited[temp->next->GetValue()-1])
			{
				DFS(temp->next->GetValue()-1);
			}
			temp = temp->next;
		}
		return;
	}
	//广度优先搜索函数
	void BFS(int n)
	{
		//visited数组表示是否搜索过该结点
		visited = new bool[capacity];
		for (int i = 0; i < capacity; i++) visited[i] = false;
		visited[n] = true;
		//使用队列完成广度搜索
		queue<int> q;
		q.push(n);
		//若队列不为空，则未搜索完
		while (!q.empty())
		{
			//取出队列头进行搜索
			n = q.front();
			cout << myVertice[n].GetValue() << "  ";
			q.pop();
			//搜索队列头对应结点的链表，即为一个广度搜索
			Vertice *temp = myVertice[n].next;
			//遍历该结点对应的链表
			while (temp)
			{
				//未被搜素过的结点放入队列中，等待搜索
				if (!visited[temp->GetValue() - 1])
				{
					q.push(temp->GetValue() - 1);
					//放入队列等待搜索，即代表该点已被搜索过
					visited[temp->GetValue() - 1] = true;
				}
				temp = temp->next;
			}
		}
	}
private:
	int capacity;
	Vertice* myVertice;
	bool * visited;
};

int main()
{
	//创建一个包含4个顶点的图
	Graph graph(4);
	//创建4个顶点
	Vertice v1(1);
	Vertice v2(2);
	Vertice v3(3);
	Vertice v4(4);
	//将边加入到图中
	graph.inputEdge(v1,v2);
	graph.inputEdge(v1, v4);
	graph.inputEdge(v2, v4);
	graph.inputEdge(v3, v4);
	//输出邻接表
	cout << "邻接表：" << endl;
	graph.GetLists();
	cout << endl;
	cout << "Breadth_First_Search result :";
	graph.BFS(0);
	return 0;
}
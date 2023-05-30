#include <iostream>
#include <string>

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
private:
	int capacity;
	Vertice* myVertice;
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
	graph.GetLists();
	return 0;
}
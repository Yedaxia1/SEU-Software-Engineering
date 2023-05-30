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
	//��ͼ�м����(v1,v2������������)
	void inputEdge(Vertice v1, Vertice v2)
	{
		//��ȡv1,v2��Ӧ����
		Vertice *temp1 = &myVertice[v1.GetValue()-1];
		Vertice *temp2 = &myVertice[v2.GetValue()-1];

		//������next������ƣ��������Ķ�����뵽����ĩβ�����˴���v2����v1����ĩ
		while (temp1->next)
		{
			temp1 = temp1->next;
		}
		temp1->next = new Vertice(v2.GetValue());

		//������next������ƣ��������Ķ�����뵽����ĩβ�����˴���v1����v2����ĩ
		while (temp2->next)
		{
			temp2 = temp2->next;
		}
		temp2->next = new Vertice(v1.GetValue());
	}
	//����ڽӱ�
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
	//���������������
	void BFS(int n)
	{
		//visited�����ʾ�Ƿ��������ý��
		visited = new bool[capacity];
		for (int i = 0; i < capacity; i++) visited[i] = false;
		visited[n] = true;
		//ʹ�ö�����ɹ������
		queue<int> q;
		q.push(n);
		//�����в�Ϊ�գ���δ������
		while (!q.empty())
		{
			//ȡ������ͷ��������
			n = q.front();
			cout << myVertice[n].GetValue() << "  ";
			q.pop();
			//��������ͷ��Ӧ����������Ϊһ���������
			Vertice *temp = myVertice[n].next;
			//�����ý���Ӧ������
			while (temp)
			{
				//δ�����ع��Ľ���������У��ȴ�����
				if (!visited[temp->GetValue() - 1])
				{
					q.push(temp->GetValue() - 1);
					//������еȴ�������������õ��ѱ�������
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
	//����һ������4�������ͼ
	Graph graph(4);
	//����4������
	Vertice v1(1);
	Vertice v2(2);
	Vertice v3(3);
	Vertice v4(4);
	//���߼��뵽ͼ��
	graph.inputEdge(v1,v2);
	graph.inputEdge(v1, v4);
	graph.inputEdge(v2, v4);
	graph.inputEdge(v3, v4);
	//����ڽӱ�
	cout << "�ڽӱ�" << endl;
	graph.GetLists();
	cout << endl;
	cout << "Breadth_First_Search result :";
	graph.BFS(0);
	return 0;
}
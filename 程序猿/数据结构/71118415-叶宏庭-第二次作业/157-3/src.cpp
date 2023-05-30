#include <iostream>

using namespace std;
class Items;
bool Path();
enum direction { N, EN, E, ES, S, WS, W, WN };//ö��С������ߵİ˸�����

class offest {//�����Ӧ����仯��
public:
	int a, b;
};

class Items {//λ���࣬�е�ǰ�����Լ���һ�������߷���
public:
	Items(int i=0, int j=0, int d=0) { a = i; b = j; dir = d; }
	int a, b,dir;
	bool operator==(Items &t)//���������==
	{
		if (a == t.a&&b == t.b) return true;
		return false;
	}
};

class Stack {//�Զ���ջ�����ڴ洢���ߵ�·��
public:
	Stack(int c) {
		capacity = c;
		top = -1;
		terms = new Items[capacity];
	}
	void Push(Items &a)
	{
		terms[++top] = a;
	}
	Items &Top()
	{
		return terms[top];
	}
	void Pop()
	{
		terms[top].~Items();
		top--;
	}
	void GetPath()//������ߵ�·��
	{
		for (int i = 0; i < top; i++)
		{
			cout << "(" << terms[i].a << "," << terms[i].b << ")-->";
		}
		cout << "(" << terms[top].a << "," << terms[top].b << ")";
	}
private:
	Items * terms;
	int capacity;
	int top;
};

Stack mystack(1000);
offest mmove[8];//�˸������Ӧ����仯
int maze[100][100];//�Թ�����
int mark[100][100] = { 0 };//��־���飬��ע��λ����û���߹�
Items Start;//��ʼλ��
Items End;//����λ��

int main()
{
	mmove[N].a = -1; mmove[N].b = 0;
	mmove[EN].a = -1; mmove[EN].b = 1;
	mmove[E].a = 0; mmove[E].b = 1;
	mmove[ES].a = 1; mmove[ES].b = 1;
	mmove[S].a = 1; mmove[S].b = 0;
	mmove[WS].a = 1; mmove[WS].b = -1;
	mmove[W].a = 0; mmove[W].b = -1;
	mmove[WN].a = -1; mmove[WN].b = -1;
	int m, p;
	cout << "Enter the size of your maze." << endl;
	cin >> m >> p;
	cout << "Enter your maze(0 or 1)." << endl;
	int g;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= p; j++)
		{
			cin >> g;
			maze[i][j] = g;//���û������Թ���0��������ߣ�1����������
		}
	for (int i = 0; i <= m + 1; i++)//���Թ�����Χ����ǽ
	{
		maze[i][0] = 1;
		maze[i][p + 1] = 1;
	}
	for (int i = 0; i <= p + 1; i++)//���Թ�����Χ����ǽ
	{
		maze[0][i] = 1;
		maze[m + 1][i] = 1;
	}
	cout << "Enter the start of the maze." << endl;
	cin >> Start.a >> Start.b;
	cout << "Enter the end of the maze." << endl;
	cin >> End.a >> End.b;
	mystack.Push(Start);
	Path();//����㿪ʼ����
	mystack.GetPath();//�������·��
	system("pause");
}

bool Path()
{
	if (mystack.Top() == End)//�ж��Ƿ񵽴��յ�
		return true;
	else
	{
		for (int i = 0; i < 8; i++)//�����˸�����Ѱ�ҿ��ߵķ���
		{
			Items t(mystack.Top().a + mmove[i].a, mystack.Top().b + mmove[i].b, 0);
			if (maze[t.a][t.b] == 0 && mark[t.a][t.b] == 0)//��ѡ��������ߣ�������ø�
			{
				mystack.Push(t);//����ø��򽲸ø�ѹջ
				mark[t.a][t.b] = 1;//��־�ø����߹�
				return Path();//����Ѱ����һ��
			}
		}
		mystack.Pop();//���˸�����������ߣ����˻ص���һ��
		return Path();//�ص���һ�������Ѱ�ҷ���
	}
}
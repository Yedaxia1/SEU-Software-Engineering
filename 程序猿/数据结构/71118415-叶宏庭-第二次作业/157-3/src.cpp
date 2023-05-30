#include <iostream>

using namespace std;
class Items;
bool Path();
enum direction { N, EN, E, ES, S, WS, W, WN };//枚举小鼠可行走的八个方向

class offest {//方向对应坐标变化类
public:
	int a, b;
};

class Items {//位置类，有当前坐标以及下一步的行走方向
public:
	Items(int i=0, int j=0, int d=0) { a = i; b = j; dir = d; }
	int a, b,dir;
	bool operator==(Items &t)//重载运算符==
	{
		if (a == t.a&&b == t.b) return true;
		return false;
	}
};

class Stack {//自定义栈，用于存储行走的路径
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
	void GetPath()//输出行走的路径
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
offest mmove[8];//八个方向对应坐标变化
int maze[100][100];//迷宫数组
int mark[100][100] = { 0 };//标志数组，标注该位置有没有走过
Items Start;//开始位置
Items End;//结束位置

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
			maze[i][j] = g;//由用户输入迷宫，0代表可行走，1代表不可行走
		}
	for (int i = 0; i <= m + 1; i++)//在迷宫最外围加上墙
	{
		maze[i][0] = 1;
		maze[i][p + 1] = 1;
	}
	for (int i = 0; i <= p + 1; i++)//在迷宫最外围加上墙
	{
		maze[0][i] = 1;
		maze[m + 1][i] = 1;
	}
	cout << "Enter the start of the maze." << endl;
	cin >> Start.a >> Start.b;
	cout << "Enter the end of the maze." << endl;
	cin >> End.a >> End.b;
	mystack.Push(Start);
	Path();//由起点开始行走
	mystack.GetPath();//输出行走路径
	system("pause");
}

bool Path()
{
	if (mystack.Top() == End)//判断是否到达终点
		return true;
	else
	{
		for (int i = 0; i < 8; i++)//遍历八个方向，寻找可走的方向
		{
			Items t(mystack.Top().a + mmove[i].a, mystack.Top().b + mmove[i].b, 0);
			if (maze[t.a][t.b] == 0 && mark[t.a][t.b] == 0)//若选定方向可走，则走入该格
			{
				mystack.Push(t);//走入该格则讲该格压栈
				mark[t.a][t.b] = 1;//标志该格已走过
				return Path();//继续寻找下一格
			}
		}
		mystack.Pop();//若八个方向均不可走，则退回到上一步
		return Path();//回到上一步后继续寻找方向
	}
}
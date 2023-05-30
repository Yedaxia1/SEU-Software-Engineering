#include <iostream>
#include <iomanip>
using namespace std;
void nextSeat(int, int, int);
bool allWalked();
int selectDirection(int, int);
void getCounter();
int imove[8] = { -1,0,1,1,1,0,-1,-1 };//定义八个方向的坐标变化
int jmove[8] = { 1,1,1,0,-1,-1,-1,0 };//定义八个方向的坐标变化
int counter[40][20] = { 0 };
int n, m;//房间大小（数组大小）
int sumCounter = 0;//总步数

int main()
{
	cout << "Enter the size of room(n×m)." << endl;
	cin >> n >> m;
	int FirstI, FirstJ;
	cout << "Enter the initial place." << endl;
	cin >> FirstI >> FirstJ;
	while(!allWalked() && sumCounter <= 50000)//房间未走满且总步数小于50000步
		nextSeat(FirstI, FirstJ, selectDirection(FirstI, FirstJ));//寻找下一步
	cout << "The sum of walks is:";
	cout << sumCounter << endl;
	cout << "The walk array is:" << endl;
	getCounter();
	system("pause");
}

void nextSeat(int nowi,int nowj,int k)
{
	if ((nowi + imove[k]) < 0 || (nowi + imove[k]) > (n - 1) || (nowj + jmove[k]) < 0 || (nowj + jmove[k]) > (m - 1))//若走出房间，则返回上一步
		return ;
	else
	{
		counter[nowi + imove[k]][nowj + jmove[k]]++;//走到的位置计数加1
		sumCounter++;//总步数加1
		while (!allWalked() && sumCounter <= 50000)//房间未走满且总步数小于50000步
		{
			nextSeat(nowi + imove[k], nowj + jmove[k], selectDirection(nowi + imove[k], nowj + jmove[k]));//寻找下一步
		}
	}
}

bool allWalked()//判断是否走满房间
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (counter[i][j] == 0)//若有一处没走，则直接返回false
				return false;
	return true;
}

void getCounter()//输出步数数组
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout <<setw(4)<< counter[i][j] << " ";
		cout << endl;
	}
}

int selectDirection(int nowi,int nowj)//查找下一个方向
{
	int d = 10000;
	int s = 10000;
	for (int k = 0; k < 8; k++)//选出八个方向的最优方向
	{
		if ((nowi + imove[k]) < 0 || (nowi + imove[k]) > (n - 1) || (nowj + jmove[k]) < 0 || (nowj + jmove[k]) > (m - 1))//走出房间的方向不可选
			continue;
		else
		{
			if (counter[nowi + imove[k]][nowj + jmove[k]] < s)//若指定方向走过的次数小，则将该方向定为下一方向
			{
				d = k;
				s = counter[nowi + imove[k]][nowj + jmove[k]];
			}
		}
	}
	return d;
}
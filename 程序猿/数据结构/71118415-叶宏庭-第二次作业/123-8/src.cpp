#include <iostream>
#include <iomanip>
using namespace std;
void nextSeat(int, int, int);
bool allWalked();
int selectDirection(int, int);
void getCounter();
int imove[8] = { -1,0,1,1,1,0,-1,-1 };//����˸����������仯
int jmove[8] = { 1,1,1,0,-1,-1,-1,0 };//����˸����������仯
int counter[40][20] = { 0 };
int n, m;//�����С�������С��
int sumCounter = 0;//�ܲ���

int main()
{
	cout << "Enter the size of room(n��m)." << endl;
	cin >> n >> m;
	int FirstI, FirstJ;
	cout << "Enter the initial place." << endl;
	cin >> FirstI >> FirstJ;
	while(!allWalked() && sumCounter <= 50000)//����δ�������ܲ���С��50000��
		nextSeat(FirstI, FirstJ, selectDirection(FirstI, FirstJ));//Ѱ����һ��
	cout << "The sum of walks is:";
	cout << sumCounter << endl;
	cout << "The walk array is:" << endl;
	getCounter();
	system("pause");
}

void nextSeat(int nowi,int nowj,int k)
{
	if ((nowi + imove[k]) < 0 || (nowi + imove[k]) > (n - 1) || (nowj + jmove[k]) < 0 || (nowj + jmove[k]) > (m - 1))//���߳����䣬�򷵻���һ��
		return ;
	else
	{
		counter[nowi + imove[k]][nowj + jmove[k]]++;//�ߵ���λ�ü�����1
		sumCounter++;//�ܲ�����1
		while (!allWalked() && sumCounter <= 50000)//����δ�������ܲ���С��50000��
		{
			nextSeat(nowi + imove[k], nowj + jmove[k], selectDirection(nowi + imove[k], nowj + jmove[k]));//Ѱ����һ��
		}
	}
}

bool allWalked()//�ж��Ƿ���������
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (counter[i][j] == 0)//����һ��û�ߣ���ֱ�ӷ���false
				return false;
	return true;
}

void getCounter()//�����������
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout <<setw(4)<< counter[i][j] << " ";
		cout << endl;
	}
}

int selectDirection(int nowi,int nowj)//������һ������
{
	int d = 10000;
	int s = 10000;
	for (int k = 0; k < 8; k++)//ѡ���˸���������ŷ���
	{
		if ((nowi + imove[k]) < 0 || (nowi + imove[k]) > (n - 1) || (nowj + jmove[k]) < 0 || (nowj + jmove[k]) > (m - 1))//�߳�����ķ��򲻿�ѡ
			continue;
		else
		{
			if (counter[nowi + imove[k]][nowj + jmove[k]] < s)//��ָ�������߹��Ĵ���С���򽫸÷���Ϊ��һ����
			{
				d = k;
				s = counter[nowi + imove[k]][nowj + jmove[k]];
			}
		}
	}
	return d;
}
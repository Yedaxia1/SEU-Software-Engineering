#include <iostream>
using namespace std;

class SparseMatrix;
class MatrixTerm {
	friend class SparseMatrix;
	void set(int r, int c, int v)
	{
		row = r;
		col = c;
		value = v;
	}
private:
	int row, col, value;
};

class SparseMatrix {
public:
	SparseMatrix(int r, int c, int t)
	{
		rows = r;
		cols = c;
		terms = t;
		capacity = 0;
		smArray = new MatrixTerm[terms];
	}
	void inputElements(int r, int c, int v)
	{
		if (capacity < terms)
			smArray[capacity++].set(r, c, v);
	}
	void outputMatrix()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				for (int k = 0; k < terms; k++)
				{
					if (smArray[k].row == i && smArray[k].col == j)
					{
						cout << smArray[k].value << "  ";
						break;
					}
					else if (smArray[k].row > i)
					{
						cout << 0 << "  ";
						break;
					}
				}
			}
			cout << endl;
		}
	}
	SparseMatrix FastTranspose()
	{
		SparseMatrix b(cols, rows, terms);
		if (terms > 0)
		{
			int *rowStart = new int[cols];//用于存储每一行第一个元素的开始位置

			fill(rowStart, rowStart + cols, 0);//初始化为0
			for (int i = 0; i < terms; i++)
				rowStart[smArray[i].col]++;//计算每一行nonzero元素个数

			int temp1 = rowStart[0]; //用于顺序计算每一个rowStart的值
			int temp2 = 0;  //用于顺序计算每一个rowStart的值
			rowStart[0] = 0; //第一行的第一个元素开始的位置为0
			for (int i = 1; i < cols; i++)
			{
				temp2 = temp1;//将temp1给temp2
				temp1 = rowStart[i];//temp1取出当前的rowStart，为下一次计算准备
				rowStart[i] = rowStart[i - 1] + temp2;//每一行的开始位置＝上一行的开始位置+上一行的元素数量
			}

			for (int i = 0; i < terms; i++)
			{
				int j = rowStart[smArray[i].col];//找出该元素转置后所在行的开始位置
				b.smArray[j].row = smArray[i].col;//赋值
				b.smArray[j].col = smArray[i].row;//赋值
				b.smArray[j].value = smArray[i].value;//赋值
				rowStart[smArray[i].col]++;//该行开始位置加1，为下一个元素指向空间
			}
			delete[] rowStart;
		}
		return b;
	}
private:
	int rows, cols, terms, capacity;
	MatrixTerm *smArray;
};

int main()
{
	SparseMatrix a(3, 3, 9);
	int r, c, v;
	cin >> r >> c >> v;
	while (r != -1)
	{
		a.inputElements(r - 1, c - 1, v);
		cin >> r >> c >> v;
	}
	cout << "Initial matrix is:" << endl;
	a.outputMatrix();
	SparseMatrix b = a.FastTranspose();
	cout << "After transpose is:" << endl;
	b.outputMatrix();
	system("pause");
}

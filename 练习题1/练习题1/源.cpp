#include<iostream>
#include<cstring>
#include<string>
using namespace std;

int main(){
	string temp;
	string A, B, C;
	int num = 0;
	for (int a = 1; a <= 4; a++)
	{
		A = to_string(a);
		for (int b = 1; b <= 4; b++)
		{
			B = to_string(b);
			if (a != b)
			{
				for (int c = 1; c <= 4; c++)
				{
					C = to_string(c);
					if (c != a && c != b)
					{
						temp = A + B + C;
						cout << temp<<endl;
						num++;
					}
				}
			}
		}
	}
	cout <<"个数为：" << num << endl;
}

//参考答案：
/*#include<iostream>
using namespace std;
int main()
{
	int num;
	int count = 0;
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 1; k <= 4; k++)
			{
				if (i != j && i != k && j != k)
				{
					count++;
					num = i * 100 + j * 10 + k;
					cout << "这些数为" << num << endl;
				}

			}
		}
	}
	cout << "能组成的互不相同且无重复数字的三位数为" << count << endl;
	system("pause");
	return 0;
}*/


/*
题目：有1、2、3、4个数字，能组成多少个
互不相同且无重复数字的三位数？都是多少？
*/
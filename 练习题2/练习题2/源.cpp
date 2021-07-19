#include <iostream> 
using namespace std;

double P;

int main() {
	double mon;
	double prize;
	cout << "请输入利润：" << endl;
	cin >> mon;
	if (mon <= 0)
		cout << "输入错误:" << endl;
	if (mon > 0 && mon <= 100000)
	{
		prize = mon + mon * 0.1;
		cout << "奖金为：" << prize << endl;
	}
	if (mon > 100000 && mon <= 200000)
	{
		double temp;
		temp = mon - 100000;
		prize = mon + 100000 * 0.1 + temp * 0.075 ;
		cout << "奖金为：" << prize << endl;
	}
	if (mon > 200000 && mon <= 400000)
	{
		double temp;
		temp = mon - 200000;
		prize = mon + 100000 * 0.1 + 100000 * 0.075 + temp * 0.05;
		cout << "奖金为：" << prize << endl;
	}
	if (mon > 400000 && mon <= 600000)
	{
		double temp;
		temp = mon - 400000;
		prize = mon + 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05+temp*0.03;
		cout << "奖金为：" << prize << endl;
	}
	if (mon > 600000 && mon <= 1000000)
	{
		double temp;
		temp = mon - 600000;
		prize = mon + 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + temp * 0.015 + 200000 * 0.03;
		cout << "奖金为：" << prize << endl;
	}
	if (mon > 1000000)
	{
		double temp;
		temp = mon - 1000000;
		prize = mon + 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + 400000 * 0.015 + 200000 * 0.03 + temp * 0.01;
		cout << "奖金为：" << prize << endl;
	}
}
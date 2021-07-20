#include <iostream>
#include<cmath>  
using namespace std;
#include<stdio.h>

class point{
private:
	double x,y;
public:
	point(double x1,double y1)
	{
	x=x1,y=y1;
	}
	
friend double Distance(point &a,point &b);
double getx()
{return x;}
double gety()
{return y;}
void show()
{cout<<'('<<getx()<<','<<gety()<<')'<<endl;}
};

double Distance(point &a,point &b)
{
	double x2,y2;
	x2=a.x-b.x;
	y2=b.x-a.y;
	return sqrt(x2*x2+y2*y2);
}

int main()
{
point p1(1,3);
point p2(2,4);
cout<<"两个点的坐标分别是："<<endl;
p1.show();
p2.show();
cout<<"两点之间的距离为："<<Distance(p1,p2)<<endl;
return 0;
}
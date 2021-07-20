#include <iostream.h>						


class Time{
private:
	int hour;
	int minute;
	int second;
public:
	Time(int a=0,int b=0,int c=0);
	friend Time operator +(Time& x,Time& y);
	friend Time operator -(Time& x,Time& y);
	friend istream& operator >>(istream& cin,Time& z);
	friend ostream& operator <<(ostream& cout,Time& z);
};
Time::Time(int a,int b,int c)
{hour=a; minute=b; second=c;}

Time operator +(Time& x,Time& y)  
{
	Time temp;
	temp.hour=x.hour+y.hour;
	temp.minute=x.minute+y.minute;
	temp.second=x.second+y.second;
	if(temp.second>=60) temp.second-=60,temp.minute++;
	if(temp.minute>=60) temp.minute-=60,temp.hour++;
	if(temp.hour>=24) temp.hour-=24;
	return temp;
}

Time operator -(Time& x,Time& y)
{
	Time temp;
	if(x.hour<y.hour) x.hour+=24;
	if(x.minute<y.minute) x.minute+=60,x.hour--;
	if(x.second<y.second) x.second+=60,x.minute--;
	temp.hour=x.hour-y.hour;
	temp.minute=x.minute-y.minute;
	temp.second=x.second-y.second;
	return temp;
}

istream& operator >>(istream& cin,Time& z)
{
	char op;
	cin>>z.hour>>op>>z.minute>>op>>z.second;
	return cin;
}

ostream& operator <<(ostream& cout,Time& z)
{
	cout<<z.hour<<":"<<z.minute<<":"<<z.second;
	return cout;
}

int main()
{
	Time a,b,c,d;
	cout<<"请分别输入两个时间："<<endl;
	cin>>a>>b;
	c=a+b;
	cout<<" "<<endl;
	cout<<c<<endl;
	d=a-b;
	cout<<d<<endl;
	return 0;
}
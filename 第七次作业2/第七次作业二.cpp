#include <iostream>

using namespace std;

class Building
{
private:
	int f;
	int r;
	int a;
public:
Building(int g1,int g2,int g3)
{
	f=g1;
	r=g2;
	a=g3;
}
int getf()
{
return f;
}
int getr()
{
return r;
}
int geta()
{
return a;
}
};

class Housing:public Building
{
private:
	int bed,bath;
public:
	Housing(int g1,int g2,int g3,int z1,int z2):Building(g1,g2,g3)
	{
		bed=z1;
		bath=z2;
	}
	int getbed()
	{
	return bed;
	}
	int getbath()
	{
	return bath;
	}
};

class Office:public Building
{
private:
	int p,e;
public:
	Office(int g1,int g2,int g3,int v1,int v2):Building(g1,g2,g3)
	{
		p=v1;
		e=v2;
	}
	int getp()
	{
	return p;
	}
	int gete()
	{
	return e;
	}
};

int main()
{
	Housing w1(5,25,650,10,10);
	cout<<"HOUSING:"<<endl;
	cout<<"floors:"<<w1.getf()<<endl;
	cout<<"rooms:"<<w1.getr()<<endl;
	cout<<"total area:"<<w1.geta()<<endl;
	cout<<"bedrooms:"<<w1.getbed()<<endl;
	cout<<"bathrooms:"<<w1.getbath()<<endl;
	cout<<"                                      "<<endl;
	
	Office w2(8,20,5000,12,45);
	cout<<"OFFICE:"<<endl;
	cout<<"floors:"<<w2.getf()<<endl;
	cout<<"rooms:"<<w2.getr()<<endl;
	cout<<"total area:"<<w2.geta()<<endl;
	cout<<"phones:"<<w2.getp()<<endl;
	cout<<"extinguishers:"<<w2.gete()<<endl;
	return 0;
}
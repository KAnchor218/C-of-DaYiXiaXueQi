#include <iostream>	
#include<cstring>				
using namespace std;

class Staff{
protected:
	int num;
	char name[10];
	float rateOfAttend;
	float basicSal;
	float prize;
public:
	Staff(int a,char b[],float c,float d,float e);
	void Output();
	void OutputWage();
};
Staff::Staff(int a,char b[],float c,float d,float e)
{
	num=a;
	strcpy(name,b);
	rateOfAttend=c;
	basicSal=d;
	prize=e;
}
void Staff::OutputWage() {cout<<"ʵ�ʹ��ʣ�"<<basicSal+prize*rateOfAttend<<endl;}
void Staff::Output()
{
cout<<"Ա����ţ�"<<num<<endl;
cout<<"Ա��������"<<name<<endl;
cout<<"�����ʣ�"<<rateOfAttend<<endl;
cout<<"�������ʣ�"<<basicSal<<endl;
cout<<"����"<<prize<<endl;
}

class Saleman: virtual public Staff{
protected:
	float deductRate;
	float personAmount;
public:
	Saleman(int a,char b[],float c,float d,float e,float f,float g);
	void Output();
	void OutputWage();
	void fact();
};
Saleman::Saleman(int a,char b[],float c,float d,float e,float f,float g):Staff(a,b,c,d,e)
{
	deductRate=f;
	personAmount=g;
}
void Saleman::OutputWage() {cout<<"ʵ�ʹ��ʣ�"<<basicSal+prize*rateOfAttend+personAmount*deductRate<<endl;}
void Saleman::Output() {Staff::Output();cout<<"����Ա��ɱ�����"<<deductRate<<endl;cout<<"�������۶"<<personAmount<<endl;}

class Manager: virtual public Staff{
protected:
	float totalDeductRate;
	float totalAmount;
public:
	Manager(int a,char b[],float c,float d,float e,float h,float i);
	void Output();
	void OutputWage();
};
Manager::Manager(int a,char b[],float c,float d,float e,float h,float i):Staff(a,b,c,d,e) {totalDeductRate=h;totalAmount=i;}
void Manager::OutputWage(){cout<<"ʵ�ʹ��ʣ�"<<basicSal+prize*rateOfAttend+totalDeductRate*totalAmount<<endl;}
void Manager::Output(){Staff::Output();cout<<"������ɱ���:"<<totalDeductRate<<endl;cout<<"�����۶�:"<<totalAmount<<endl;}

class SaleManager: public Saleman,public Manager{
public:
	SaleManager(int a,char b[],float c,float d,float e,float f,float g,float h,float i);
	void Output();
	void OutputWage();
};
SaleManager::SaleManager(int a,char b[],float c,float d,float e,float f,float g,float h,float i):Staff(a,b,c,d,e),Saleman(a,b,c,d,e,f,g),Manager(a,b,c,d,e,h,i)
{}
void SaleManager::OutputWage(){cout<<"ʵ�ʹ��ʣ�"<<basicSal+prize*rateOfAttend+totalDeductRate*totalAmount+personAmount*deductRate<<endl;}
void SaleManager::Output(){Staff::Output();cout<<"����Ա��ɱ�����"<<deductRate<<endl;cout<<"�������۶"<<personAmount<<endl;cout<<"������ɱ���:"<<totalDeductRate<<endl;cout<<"�����۶�:"<<totalAmount<<endl;}

int main()
{
	Staff x1(101,"Zhang",0.9,2000,3000);
	x1.Output();
	x1.OutputWage();
	cout<<"  "<<endl;
	Saleman x2(201,"Sun",0.9,3000,4000,0.1,10000);
	x2.Output();
	x2.OutputWage();
	cout<<"  "<<endl;
	Manager x3(301,"Li",0.9,4000,5000,0.1,20000);
	x3.Output();
	x3.OutputWage();
	cout<<"  "<<endl;
	SaleManager x4(401,"Wu",1,5000,6000,0.1,10000,0.05,40000);
	x4.Output();
	x4.OutputWage();
	return 0;
}
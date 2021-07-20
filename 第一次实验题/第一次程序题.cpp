
#include<iostream>
#include<cstring>
using namespace std;

class Student{
	private:
		char name[18];
		int num;
		int mathScore;
		int englishScore;
		static int count;
		static int mathtotalScore;
		static int englishTotalScore;
	public:
		Student(char nm[],int nu,int math,int english);
		void showbase();
		static void showstatic();
};

Student::Student(char nm[],int nu,int math,int english)
{
	strcpy(name,nm);
	num=nu;
	mathScore=math;
	englishScore=english;
	count++;
	mathtotalScore+=math;
	englishTotalScore+=english;
}
int Student::count=0;
int Student::mathtotalScore=0;
int Student::englishTotalScore=0;

void Student::showbase()
{
	cout<<"���֣�"<<name<<endl;
	cout<<"ѧ�ţ�"<<num<<endl;
	cout<<"��ѧ������"<<mathScore<<endl;
	cout<<"Ӣ�������"<<englishScore<<endl;
}
void Student::showstatic()
{
	cout<<"��������"<<count<<endl;
	cout<<"����ѧ�ɼ���"<<mathtotalScore<<endl;
	cout<<"��Ӣ��ɼ���"<<englishTotalScore<<endl;
}

int main()
{
	Student p1("������",123,96,96),p2("�����",345,2,3);
	p1.showbase();
	cout<<"   "<<endl;
	p2.showbase();
	cout<<"   "<<endl;
	Student::showstatic();
	cout<<"   "<<endl;
	return 0;
}
#include <iostream>

using namespace std;

class A

{

public:

    A(int i,int j)

    {

        x= i;

        y= j;

    }

    int sum()

    {

        return x+ y;

    }

private:

    int x,y;

};

class B:public A

{

public:

    B(int i, int j,int k, int l):A(i,j)

    {

        w=k;

        h=l;

    }

    int sum()

    {

        return w+h;

    }

private:

    int w, h;

};

void f(&A s)			/*����ob��Ҳ������A�е����ݳ�Ա�����ob����Ϊ������������A����Ϊ�βεĺ�������ʱ���õ��Ƕ���ob�е���A�����ݳ�Ա*/

{

    cout<< s.sum()<<endl;

}

int main()

{

    B ob(1,3,5,7);

    f(ob);

    return 0;

}


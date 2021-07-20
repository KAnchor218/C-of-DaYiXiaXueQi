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

void f(&A s)			/*对象ob中也含有类A中的数据成员，因此ob可作为参数传入以类A对象为形参的函数，此时调用的是对象ob中的类A的数据成员*/

{

    cout<< s.sum()<<endl;

}

int main()

{

    B ob(1,3,5,7);

    f(ob);

    return 0;

}


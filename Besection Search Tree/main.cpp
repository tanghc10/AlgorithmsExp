#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

int ConstructOptimalBTSLeft(int **root, int i, int j);
int ConstructOptimalBTSRight(int **root, int i, int j);

int n = 0;
int count = 0;

int main()
{
    int i = 0, j = 0;
    ifstream in("in.dat");
    if(!in.is_open())
    {
        cout<<"fail to open file : in.dat"<<endl;
		return -1;
    }
    in>>n;
    int root[n][n];
    for(i = 0 ; i < n; i++)
        for(j = 0; j < n; j++)
            in>>root[i][j];
    cout<<"k"<<root[0][n-1]<<"�Ǹ�"<<endl;
    ConstructOptimalBTSLeft((int **)root, 1, root[0][n - 1] - 1);
    ConstructOptimalBTSRight((int **)root, root[0][n - 1] + 1, n);
    system("pause");
    return 0;
}

int ConstructOptimalBTSLeft(int **root, int i, int j)
{
    if(i > j)
        return 0;
    int temp = *((int *)root + n * (i - 1) + j - 1);
    cout<<"k"<<temp<<"��k"<<j+1<<"������"<<endl;
    if(i == j)
    {
    	cout<<"d"<<count<<"��k"<<i<<"������"<<endl;
        count++;
    	cout<<"d"<<count<<"��k"<<i<<"���Һ���"<<endl;
        count++;
        return 0;
    }
    else
    {
        int temp = *((int *)root + n * (i - 1) + j - 1);
        if(temp == i)
        {
    		cout<<"d"<<count<<"��k"<<i<<"������"<<endl;
            count++;
        }
        else
            ConstructOptimalBTSLeft(root, i, temp - 1);
        if(temp == j)
        {
    		cout<<"d"<<count<<"��k"<<i<<"���Һ���"<<endl;
            count++;
        }
        else
            ConstructOptimalBTSRight(root, temp + 1, j);
    }
}
int ConstructOptimalBTSRight(int **root, int i, int j)
{
    if(i > j)
        return 0;
    int temp = *((int *)root + n * (i - 1) + j - 1);
	cout<<"k"<<temp<<"��k"<<i-1<<"���Һ���"<<endl;
    if(i == j)
    {
    	cout<<"d"<<count<<"��k"<<i<<"������"<<endl;
        count++;
        cout<<"d"<<count<<"��k"<<i<<"���Һ���"<<endl;
        count++;
        return 0;
    }
    else
    {
        int temp = *((int *)root + n * (i - 1) + j - 1);
        if(temp == i)
        {
        	cout<<"d"<<count<<"��k"<<i<<"������"<<endl;
            count++;
        }
        else
            ConstructOptimalBTSLeft(root, i, temp - 1);
        if(temp == j)
        {
        	cout<<"d"<<count<<"��k"<<i<<"���Һ���"<<endl;
            count++;
        }
        else
            ConstructOptimalBTSRight(root, temp + 1, j);
    }
}

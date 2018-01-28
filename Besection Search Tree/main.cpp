#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

void ConstructOptimalBTSLeft(vector< vector<int> >root, int i, int j);
void ConstructOptimalBTSRight(vector< vector<int> >root, int i, int j);

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
    vector< vector<int> > root;
    in>>n;
    for(i = 0 ; i < n; i++){
    	root.push_back(vector<int>(n, 0));
        for(j = 0; j < n; j++)
            in>>root[i][j];
    }
    cout<<"k"<<root[0][n-1]<<"�Ǹ�"<<endl;
    ConstructOptimalBTSLeft(root, 1, root[0][n-1] - 1);
    ConstructOptimalBTSRight(root, root[0][n-1] + 1, n);
    system("pause");
    return 0;
}

void ConstructOptimalBTSLeft(vector< vector<int> >root, int i, int j)
{
    if(i > j)
        return;
    int temp = root[i-1][j-1];
    cout<<"k"<<temp<<"��k"<<j+1<<"������"<<endl;
    if(i == j)
    {
    	cout<<"d"<<count++<<"��k"<<i<<"������"<<endl;
    	cout<<"d"<<count++<<"��k"<<i<<"���Һ���"<<endl;
        return;
    }
    else
    {
        int temp = root[i-1][j-1];
        if(temp == i)
    		cout<<"d"<<count++<<"��k"<<i<<"������"<<endl;
        else
            ConstructOptimalBTSLeft(root, i, temp - 1);
        if(temp == j)
    		cout<<"d"<<count++<<"��k"<<i<<"���Һ���"<<endl;
        else
            ConstructOptimalBTSRight(root, temp + 1, j);
    }
}
void ConstructOptimalBTSRight(vector< vector<int> >root, int i, int j)
{
    if(i > j)
        return;
    int temp = root[i-1][j-1];
	cout<<"k"<<temp<<"��k"<<i-1<<"���Һ���"<<endl;
    if(i == j)
    {
    	cout<<"d"<<count++<<"��k"<<i<<"������"<<endl;
        cout<<"d"<<count++<<"��k"<<i<<"���Һ���"<<endl;
        return;
    }
    else
    {
        int temp = root[i-1][j-1];
        if(temp == i)
        	cout<<"d"<<count++<<"��k"<<i<<"������"<<endl;
        else
            ConstructOptimalBTSLeft(root, i, temp - 1);
        if(temp == j)
        	cout<<"d"<<count++<<"��k"<<i<<"���Һ���"<<endl;
        else
            ConstructOptimalBTSRight(root, temp + 1, j);
    }
}

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
    cout<<"k"<<root[0][n-1]<<"是根"<<endl;
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
    cout<<"k"<<temp<<"是k"<<j+1<<"的左孩子"<<endl;
    if(i == j)
    {
    	cout<<"d"<<count++<<"是k"<<i<<"的左孩子"<<endl;
    	cout<<"d"<<count++<<"是k"<<i<<"的右孩子"<<endl;
        return;
    }
    else
    {
        int temp = root[i-1][j-1];
        if(temp == i)
    		cout<<"d"<<count++<<"是k"<<i<<"的左孩子"<<endl;
        else
            ConstructOptimalBTSLeft(root, i, temp - 1);
        if(temp == j)
    		cout<<"d"<<count++<<"是k"<<i<<"的右孩子"<<endl;
        else
            ConstructOptimalBTSRight(root, temp + 1, j);
    }
}
void ConstructOptimalBTSRight(vector< vector<int> >root, int i, int j)
{
    if(i > j)
        return;
    int temp = root[i-1][j-1];
	cout<<"k"<<temp<<"是k"<<i-1<<"的右孩子"<<endl;
    if(i == j)
    {
    	cout<<"d"<<count++<<"是k"<<i<<"的左孩子"<<endl;
        cout<<"d"<<count++<<"是k"<<i<<"的右孩子"<<endl;
        return;
    }
    else
    {
        int temp = root[i-1][j-1];
        if(temp == i)
        	cout<<"d"<<count++<<"是k"<<i<<"的左孩子"<<endl;
        else
            ConstructOptimalBTSLeft(root, i, temp - 1);
        if(temp == j)
        	cout<<"d"<<count++<<"是k"<<i<<"的右孩子"<<endl;
        else
            ConstructOptimalBTSRight(root, temp + 1, j);
    }
}

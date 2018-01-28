#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class Road{
public:
	int a, b, c, p, r;
};

Road *road = new Road[11];
int *visit = new int[11];
int min_cost = 2000;
int m = 0, n = 0;

void DFS(int a, int fee){	//a为当前城市编号，fee为当前的费用
	if (fee > min_cost)
		return;
	if(a == n){
		if (fee < min_cost)
			min_cost = fee;
		return;
	}
	int i = 1;
	for(; i <= m; i++){
		if (a == road[i].a && visit[road[i].b] <= 3){
			int b = road[i].b;
			visit[b]++;
			if (visit[road[i].c])
				DFS(b, fee + road[i].p);
			else
				DFS(b, fee + road[i].r);
			visit[b]--;
		}
	}
	return;
}

int main(){
	int i = 0;
	ifstream in("in.dat");
	visit[1] = 1;	//从第一个城市出发，记录一次
    for(i = 1; i< 11; i++)
        visit[i] = 0;
	in>>n>>m;
	for(i = 1; i <= m; i++)
		in>>road[i].a>>road[i].b>>road[i].c>>road[i].p>>road[i].r;
	DFS(1, 0);
	if (min_cost == 2000)
		cout<<"impossible"<<endl;
	else
		cout<<min_cost<<endl;
    system("pause");
	return 1;
}

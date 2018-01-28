#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define mod 100000000
#define N 15
#define M 4100

int map[N];	//该行的输入状态
int v[M]; 	//所有可能的状态的集合
int dp[N][M];	//表示在第i行状态为j时候可以放牛的情况数量
int n, m;
int size;

void getValidState(){
	size = 0;
	int i = 0;
	for (i = 0; i < (1<<m); i++){
		if ((i & i<<1) == 0)
			v[size++] = i;
	}
	return;
}

bool valid(int state, int r){
	return (!(state & (~map[r])));
}

int main(){
	int i = 0, j = 0, x = 0, y = 0;
	int res = 0;
	ifstream in("in.dat");
	while(in>>n>>m){
		res = 0;
		for(i = 0; i < n; i++){
			map[i] = 0;
			for(j = 0; j < m; j++){
				in>>x;
				if (x)
					map[i] += (1<<(m - j - 1));
			}
		}
		getValidState();
		for (i = 0; i < size; i++)
		{
			if (valid(v[i], 0))
				dp[0][i] = 1;
		}
		for(i = 1; i < n; i++){
			for (j = 0; j < size; j++){
				if (valid(v[j], i)){	//第x个可行的状态不与i中的土地冲突
					for (x = 0; x < size; x++){
						if (valid(v[x], i - 1) && !(v[x] & v[j])){
							dp[i][j] = (dp[i][j] + dp[i-1][x]) % mod;
						}
					}
				}
			}
		}
		for(i = 0; i < size; i++)
			res = (res + dp[n - 1][i]) % mod;
		cout<<res<<endl;
	}
	system("pause");
	return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#define MAX 32767

using namespace std;

void getPath(int i, int j, vector<vector<int> > p){
	if (p[i][j] == j){
		cout<<" "<<j+1<<endl;
		return;
	}
	cout<<" "<<p[i][j]+1<<flush;
	getPath(p[i][j], j, p);
}

int main(){
	int t = 0;	//测试样例个数
	int n = 0;	//测试样例结点个数
	int i = 0, j = 0, temp = 0;
	vector< vector<int> > d;
	vector< vector<int> > p;
	ifstream in("in.dat");
	if (!in.is_open()){
		cout<<"fail to open file : in.dat"<<endl;
		return -1;
	}
	in>>t;
	cout<<t;
	while(t--){
		in>>n;
		for(i = 0; i < n; i++){
			d.push_back(vector<int>(n, 0));
			p.push_back(vector<int>(n, 0));
			for (j = 0; j < n; j++){
				in>>temp;
				if (temp == 100)
					temp = MAX;
				d[i][j] = temp;
				p[i][j] = j;
			}
		}
		
		for(temp = 0; temp < n; temp++){
			for(i = 0; i < n; i++){
				for(j = 0; j < n; j++){
					if (i != j && d[i][j] > d[i][temp] + d[temp][j]){
						d[i][j] = d[i][temp] + d[temp][j];	//更新D矩阵
						p[i][j] = p[i][temp];	//更新P矩阵
					}
				}
			}
		}
		cout<<n<<endl;
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				if (j)	cout<<" ";
				cout<<d[i][j]<<flush;
			}
			cout<<endl;
		}

		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				if (d[i][j] >= 32767){
					cout<<"NULL"<<endl;
				}
				if(i == j)
					cout<<i+1<<endl;
				else{
					cout<<i+1<<flush;
					getPath(i, j, p);
				}
			}
		}
		d.clear();
		p.clear();
	}
	system("pause");
	return 0;
}

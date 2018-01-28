#include<iostream>
#include<algorithm>
#include<fstream>
#include<cstdlib>
using namespace std;

typedef struct _Stick
{
	int length, weight;
}my_Stick;

bool cmp(const my_Stick &a, const my_Stick &b){
	if (a.length != b.length)
		return a.length > b.length;
	else
		return a.weight > b.weight;
}

int main(){
	/*测试样例组数*/
	my_Stick s[5001];
	int flag[5001];
	int t = 0, i = 0, j = 0, cnt = 1, min = 0;
	ifstream in("in.dat");
	in>>t;
	while(t--){
		int n = 0; /*木棍个数*/
		in>>n;
		i = 0;
		/*读入木棍数据信息*/
		while(i < n){
			in>>s[i].length>>s[i].weight;
			flag[i] = 0;
			i++;
		}
		/*对木棍数据进行降序排序*/
		sort(s, s+n, cmp);
		/*贪心算法*/
		cnt = 0;
		for (i = 0; i < n; i++){
            if (flag[i])    continue;
            min = s[i].weight;
			for (j = i + 1; j < n; j++){
				if (min >= s[j].weight && !flag[j]){
                    min = s[j].weight;
					flag[j] = 1;
				}
			}
			cnt++;
		}
        cout<<cnt<<endl;
	}
	system("pause");
	return 0;
}

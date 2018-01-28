#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{
	int c = 0;	//用来控制输出格式
	int n = 0;	//鱼塘个数
	int h = 0;	//钓鱼时间
	int h_temp = 0;	//枚举过程中使用的钓鱼时间
	int ti[200];	//ti[i]表示从第i个湖去第i+1个湖所需要的时间
	int fi_temp[200];   //鱼塘鱼量
	int fi[200];	//fi[i]表示第i个湖的初始鱼的数量
	int di[200];	//di[i]表示如果在第i个湖钓鱼，则该湖每五分钟鱼的数量的减少值
	int result[200];	//result[i]表示在第i个湖中钓鱼的时间
	int temp[200];		//储存中间结果
	int i = 0;
	int num_max = 0;	//总共的最大钓鱼数
	int num_temp = 0;	//中间某次钓鱼选择的钓鱼数
	int fishIndex = 0;	//本次钓鱼过程选择钓鱼的鱼塘下标
	int endIndex = 0;	//结束钓鱼时所在的鱼塘下标
	ifstream in("in.dat");
	if (!in.is_open()){
		cout<<"fail to open file : in.dat"<<endl;
		return -1;
	}
	while(i < 200){
		ti[i] = 0;
		fi[i] = 0;
		di[i] = 0;
		result[i] = 0;
		temp[i++] = 0;
	}
	while(cin>>n && n > 0){
		if (c != 0)
			cout<<endl;
		c = 1;
		cin>>h;
		h = h * 12;		//将小时化成以五分钟为单位
		for(i = 0; i < n; i++)
			cin>>fi[i];
		for(i = 0; i < n; i++)
			cin>>di[i];
		for(i = 0; i < n-1; i++)
			cin>>ti[i];
		i = 0;
		endIndex = 0;
		num_max = -1;
		while(endIndex < n){
            num_temp = 0;   //本次计算的钓鱼数请0
		    h_temp = h;     //钓鱼总时间重置
            for (i = 0; i < n; i++){   //存储在每个鱼塘钓鱼的时间的数组清零，鱼塘鱼的数量重置
                temp[i] = 0;
                fi_temp[i] = fi[i];
            }
            i = 0;
			while(i < endIndex)	h_temp -= ti[i++];	//先减去在路上花费的时间
			while(h_temp > 0){
				fishIndex = 0;

				for(i = 0; i <= endIndex; i++)	//选择一个鱼的数量最多的鱼塘
					if (fi_temp[i] > fi_temp[fishIndex])	fishIndex = i;

				if (fi_temp[fishIndex] == 0){	//所有鱼塘都为空，把剩下的时间加到第一个鱼塘中，退出本次的计算
                    //cout<<"lake empty h = "<<h_temp<<endl;
					temp[0] += h_temp * 5;
					break;
				}else{	//在鱼最多的池塘中钓鱼
				    //cout<<"fish in lack "<<fishIndex<<" : "<<fi_temp[fishIndex]<<endl;
					num_temp += fi_temp[fishIndex];
					fi_temp[fishIndex] -= di[fishIndex];
					if (fi_temp[fishIndex] < 0) fi_temp[fishIndex] = 0;
					temp[fishIndex] += 5;
					h_temp--;
				}
			}
			if (num_temp > num_max){
				i = 0;
				while(i < n)
					result[i] = temp[i++];
				num_max = num_temp;
			}
			endIndex++;
		}
		cout<<result[0];
		for (i = 1; i < n; ++i)
			cout<<", "<<result[i];
		cout<<endl;
		cout<<"Number of fish expected: "<<num_max<<endl;
	}
	system("pause");
	return 0;
}

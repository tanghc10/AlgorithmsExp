#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
using namespace std;

class Point {
	int x;
	int y;
public:
	Point(int x, int y) : x(x), y(y) {};
	~Point() {};
	int getx() const {
		return x;
	}
	int gety() const {
		return y;
	}
};

class Distance
{
	Point p1, p2;
public:
	double dist();
	void show();
	Distance(Point d1, Point d2) :p1(d1), p2(d2) {};
	~Distance() {};
};

double Distance::dist()
{
	int x1 = p1.getx();
	int x2 = p2.getx();
	int y1 = p1.gety();
	int y2 = p2.gety();
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void Distance::show() {
	cout<<p1.getx()<<" "<<p1.gety()<<" "<<p2.getx()<<" "<<p2.gety();
}

bool comp(const Point &a, const Point &b)
{
	return a.getx() < b.getx();
}

void crossMid(vector<Point> &p, vector<Distance> &d) {
	vector<Point> ml;
	vector<Point> mr;
	int x;
	/*找点集中距离中心点的x距离小于目前最近点对的距离的点*/
	if (p.size() % 2) {
		x = p[p.size() / 2].getx();
		ml.push_back(p[p.size() / 2]);
		int i = 1;
		while (1) {	//寻找左边的点
			if ((i <= p.size() / 2) && (x - p[p.size() / 2 - i].getx() <= d[0].dist())) {
				ml.push_back(p[p.size() / 2 - i]);
				++i;
			}
			else break;
		}
		i = -1;
		while (1) {	//寻找右边的点
			if ((-i < p.size() - p.size() / 2) && (x - p[p.size() / 2 - i].getx() <= d[0].dist())) {
					mr.push_back(p[p.size() / 2 - i]);
					--i;
			}else break;
		}
	}else{
		x = p[p.size() / 2 - 1].getx();
		ml.push_back(p[p.size() / 2 - 1]);
		int i = 1;
		while (1) {
			if ((i <= p.size() / 2 - 1) && (x - p[p.size() / 2 - 1 - i].getx() <= d[0].dist())) {
					ml.push_back(p[p.size() / 2 - 1 - i]);
					++i;
			}else break;
		}
		i = -1;
		while (1) {
			if ((-i < p.size() - p.size() / 2 + 1) && (x - p[p.size() / 2 - 1 - i].getx() <= d[0].dist())) {
					mr.push_back(p[p.size() / 2 - 1 - i]);
					--i;
			}else break;
		}
	}
	/*计算左边的点和右边的点之间的距离，检查是否小于当前的最近点对距离*/
	for (int i = 0; i < ml.size(); ++i) {
		for (int j = 0; j < mr.size(); ++j) {
			Distance s(ml[i], mr[j]);
			if (d.empty())	//距离集为空，直接插入
				d.push_back(s);
			else if (s.dist() < d[0].dist()) {	//此距离比目前的最近点对的距离小，先清空距离矢量集，再插入
				d.clear();
				d.push_back(s);
			}else if (s.dist() == d[0].dist())	//此距离等于目前的最近点对距离，插入到距离矢量集的尾部
				d.push_back(s);
		}
	}
}

void divideAndConquer(vector<Point> &p, vector<Distance> &d) {
	if (p.empty() || p.size() == 1) return;
	else if (p.size() == 2) {
		Distance last(p[0], p[1]);
		if (d.empty()) {	//距离集为空，直接将此点对加入距离集
			d.push_back(last);
		}
		else if (last.dist() < d[0].dist()) {	//此点对的距离比距离集的点对距离要小，先清空距离集中的点对，再将此点对加入到距离集中
			d.clear();
			d.push_back(last);
		}
		else if (last.dist() == d[0].dist())	//此点对的距离和距离集的点对距离相同，将此点对加入到距离集的队列尾部
			d.push_back(last);
	}
	else {
		if (p.size() % 2) {		//奇数个点，将中心点划分到左边的点的集合，再对两个子集合进行递归
			vector<Point> subp1(p.begin(), p.begin() + p.size() / 2 + 1);
			vector<Point> subp2(p.begin() + p.size() / 2 + 1, p.end());
			divideAndConquer(subp1, d);
			divideAndConquer(subp2, d);
		}	
		else {		//偶数个点，将点集划分成数量相等的左右两部分，再对两个子集合进行递归
			vector<Point> subp1(p.begin(), p.begin() + p.size() / 2);
			vector<Point> subp2(p.begin() + p.size() / 2, p.end());
			divideAndConquer(subp1, d);
			divideAndConquer(subp2, d);
		}
		crossMid(p, d);
	}
}

int main() {
	int n;	//测试样例个数
	int num;	//当前测试样例点的个数
	int x, y;	//用来接收点的坐标
	ifstream in("in.dat");	//从文件中读入数据
	if (!in.is_open()){
		cout<<"fail to open file : in.dat"<<endl;
		return -1;
	}
	vector<Point> pointList;	//点集
	pointList.reserve(100*sizeof(Point));
	vector<Distance> disList;	//距离集
	in>>n;
	while(n--){
		in>>num;
		while(num--){
			in>>x>>y;
			pointList.push_back(Point(x, y));	//将点加入点集的尾部
		}
		sort(pointList.begin(), pointList.end(), comp);	//根据x坐标排序
		divideAndConquer(pointList, disList);
		for (int i = 0; i < disList.size(); ++i) {	//输出最近点对
			if (i)
				cout<<" "<<flush;
			disList[i].show();
		}
		cout<<endl;
		pointList.clear();
		disList.clear();
	}
	system("pause");
	return 0;
}

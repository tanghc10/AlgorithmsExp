#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

string IntAdd(string x, string y);

//string����ת����int����
int string_to_num(string k)//string�ַ���������������str="1234"��ת��Ϊ������1234.
{
	int back;
	stringstream stream;
	stream << k;
	stream >> back;
	return back;
}
//������ת��Ϊstring����
string num_to_string(int intValue)
{
	string result;
	stringstream stream;
	stream << intValue;//��int������
	stream >> result;//��stream�г�ȡǰ������intֵ
	return result;
}
//���ַ���strǰ���s����
string stringBeforeZero(string str, int s)
{
	for (int i = 0;i<s;i++)
	{
		str.insert(0, "0");
	}
	return str;
}
//�����������ַ�����ӣ������������ʾ��Χ����Ҳ��ʵ�����(����������ʵ�ִ������ӷ�����)
string stringAddstring(string str1, string str2)
{
	//�ٶ�str1��str2����ȵĳ��ȣ������ʱ��ǰ���Զ����㣬ʹ�����ַ����������
	if (str1.size() > str2.size())
	{
		str2 = stringBeforeZero(str2, str1.size() - str2.size());
	}
	else if (str1.size() < str2.size())
	{
		str1 = stringBeforeZero(str1, str2.size() - str1.size());
	}
	string result;
	int flag = 0;//ǰһ��λ�Ƿ��б�־,0�����޽�λ��1�����н�λ
	for (int i = str1.size() - 1;i >= 0;i--)
	{
		int c = (str1[i] - '0') + (str2[i] - '0') + flag;//����ASCII����ַ���������,�������flag�������:��ǰһλ�н�λʱ��1���޽�λʱ��0
		flag = c / 10;//c����10ʱ��flag��Ϊ1������Ϊ0
		c %= 10;//c����10ʱȡģ������Ϊ�䱾��
		result.insert(0, num_to_string(c));//��result�ַ�����ǰ�˲��������ɵĵ����ַ�
	}
	if (0 != flag) //���һΪ(���λ)�жϣ�����н�λ������һλ
	{
		result.insert(0, num_to_string(flag));
	}
	return result;
}
/*�����������ַ�������������������ʾ��Χ����Ҳ��ʵ�����(������Ƚ����⣬��һ������һ�����ڵڶ�������,
��Ϊ��a1*b0+a0*b1=(a1+a0)*(b1+b0)-(a1*b1+a0*b0) > 0 ,����(a1+a0)*(b1+b0) > (a1*b1+a0*b0)
���������������������һ���������ʵ����(a1+a0)*(b1+b0)���ڶ����������ʵ����(a1*b1+a0*b0)
���Ա������ﲻ�ÿ������յõ����Ϊ��������������ڼ����йش�����������˵��������ͨ������;���ж�
*/
string stringSubtractstring(string str1, string str2)
{
	//�Դ������������������޼������ǰ�漸λ��0����ȥ��������ͳһ����
	while ('0' == str1[0] && str1.size()>1)
	{
		str1 = str1.substr(1, str1.size() - 1);
	}
	while ('0' == str2[0] && str2.size()>1)
	{
		str2 = str2.substr(1, str2.size() - 1);
	}
	//ʹ�����ַ����������
	if (str1.size() > str2.size())
	{
		str2 = stringBeforeZero(str2, str1.size() - str2.size());
	}
	string result;
	for (int i = str1.size() - 1;i >= 0;i--)
	{
		int c = (str1[i] - '0') - (str2[i] - '0');//����ASCII����и�λ��������
		if (c < 0) //��������ʱ��ǰһλ��λ��ǰһλҲ����λʱ����ǰһλ��λ����������
		{
			c += 10;
			int prePos = i - 1;
			char preChar = str1[prePos];
			while ('0' == preChar)
			{
				str1[prePos] = '9';
				prePos -= 1;
				preChar = str1[prePos];
			}
			str1[prePos] -= 1;
		}
		result.insert(0, num_to_string(c));//��result�ַ�����ǰ�˲��������ɵĵ����ַ�
	}
	return result;
}
//���ַ���str�����s����
string stringFollowZero(string str, int s)
{
	for (int i = 0;i<s;i++)
	{
		str.insert(str.size(), "0");
	}
	return str;
}

string IntSub(string x, string y){
	int is_below = 0;
	int change = 0;
	if (x[0] == '-' && y[0] == '-'){
		x = x.substr(1, x.size() - 1);
		y = y.substr(1, y.size() - 1);
		change = 1;
	}else if (x[0] == '-'){
		x = x.substr(1, x.size() - 1);
		string r = IntAdd(x, y);
		r.insert(0, string("-"));
		return r;
	}else if (y[0] == '-'){
		y = y.substr(1, y.size() - 1);
		string r = IntAdd(x, y);
		r.insert(0, string("-"));
		return r;
	}
	//�Դ������ĵ�һ���������޼������ǰ�漸λ��0����ȥ��������ͳһ����
	while ('0' == x[0] && x.size()>1)
	{
		x = x.substr(1, x.size() - 1);
	}
	//�Դ������ĵڶ����������޼������ǰ�漸λ��0����ȥ��������ͳһ����
	while ('0' == y[0] && y.size()>1)
	{
		y = y.substr(1, y.size() - 1);
	}
	int i = x.size() - 1, j = y.size() - 1;
	int cn = 0;
	if (j > i){
		x = stringBeforeZero(x, j - i);
		is_below = 1;
	}else if (j < i){
		y = stringBeforeZero(y, i - j);
	}else{
		int cnt = 0;
		while(cnt < x.size()){
			if (x[cnt] > y[cnt])
				break;
			else if (x[cnt] < y[cnt]){
				is_below = 1;
				break;
			}else
				cnt++;
		}
		if(cnt == x.size()){
			return string("0");
		}
	}
	if (is_below){
		string r = x;
		x = y;
		y = r;
	}
	i = x.size();
	while(i >= 0){
		if (cn == 1){
			x[i] -= 1;
			cn = 0;
		}
		x[i] -= y[i] - '0';
		if (x[i] < '0'){
			x[i] += 10;
			cn = 1;
		}
		i--;
	}
	if ((is_below && !change) || (!is_below && change))
		x.insert(0, "-");
	return x;
}

string IntAdd(string x, string y){
	int is_below = 0;
	if (x[0] == '-' && y[0] == '-'){
		x = x.substr(1, x.size() - 1);
		y = y.substr(1, y.size() - 1);
		is_below = 1;
	}else if (x[0] == '-'){
		x = x.substr(1, x.size() - 1);
		return IntSub(y, x);
	}else if (y[0] == '-'){
		y = y.substr(1, x.size() - 1);
		return IntSub(x, y);
	}
	//�Դ������ĵ�һ���������޼������ǰ�漸λ��0����ȥ��������ͳһ����
	while ('0' == x[0] && x.size()>1)
	{
		x = x.substr(1, x.size() - 1);
	}
	//�Դ������ĵڶ����������޼������ǰ�漸λ��0����ȥ��������ͳһ����
	while ('0' == y[0] && y.size()>1)
	{
		y = y.substr(1, y.size() - 1);
	}
	int i = x.size() - 1, j = y.size() - 1;
	int cn = 0;
	while(i >= 0 && j >= 0){
		if (cn == 1){
			x[i] += 1;
		}
		x[i] += y[j] - '0';
		if (x[i] > '9'){
			x[i] -= 10;
			cn = 1;
		}
		y[j] = x[i];
		i--;
		j--;
	}
	if (i < 0){
		while(cn == 1){
			if (j < 0){
				y.insert(0, string("1"));
				cn = 0;
			}else{
				y[j] = y[j] + 1;
				if (y[j] > '9'){
					y[j] -= 10;
					cn = 1;
				}
				j--;
			}
		}
		return y;
	}else{
		while(cn == 1){
			if (i < 0){
				x.insert(0, string("1"));
				cn = 0;
			}else{
				x[i] = x[i] + 1;
				if (x[i] > '9'){
					x[i] -= 10;
					cn = 1;
				}
				i--;
			}
		}
		return x;
	}
}

//���η��������˷�ʵ�ֺ���
string IntMult(string x, string y)//�ݹ麯��
{
	//�Դ������ĵ�һ���������޼������ǰ�漸λ��0����ȥ��������ͳһ����
	while ('0' == x[0] && x.size()>1)
	{
		x = x.substr(1, x.size() - 1);
	}
	//�Դ������ĵڶ����������޼������ǰ�漸λ��0����ȥ��������ͳһ����
	while ('0' == y[0] && y.size()>1)
	{
		y = y.substr(1, y.size() - 1);
	}
	/*�����f�������������������ַ������Ȳ���Ȼ��߲���2��ָ����������£���Ҫͳһ�ĳ��ȣ���������Ϊ�������ݳ���Ϊ2��n�η�
	������±������÷��η�����
	*/
	int f = 4;
	/*�����ַ�����������һ���ַ������ȴ���2ʱ��Ҫͨ�������涨���fֵ���бȽϣ�ʹ��ﵽ���ݳ���Ϊ2��n�η���ʵ�ַ�ʽ����ǰ��
	��0���������Ա�֤����ֵ��С����
	*/
	if (x.size()>2 || y.size()>2)
	{
		if (x.size() >= y.size()) //��һ�������ȴ��ڵ��ڵڶ��������ȵ����
		{
			while (x.size()>f) //�ж�fֵ
			{
				f *= 2;
			}
			if (x.size() != f)
			{
				x = stringBeforeZero(x, f - x.size());
				y = stringBeforeZero(y, f - y.size());
			}
		}
		else//�ڶ��������ȴ��ڵ�һ�������ȵ����
		{
			while (y.size()>f) //�ж�fֵ
			{
				f *= 2;
			}
			if (y.size() != f)
			{
				x = stringBeforeZero(x, f - x.size());
				y = stringBeforeZero(y, f - y.size());
			}
		}
	}
	if (1 == x.size()) //���ݳ���Ϊ1ʱ,��ǰ�油һ��0(����֮���Ի���ֳ���Ϊ1����������Ϊǰ��������޼���)
	{
		x = stringBeforeZero(x, 1);
	}
	if (1 == y.size()) //���ݳ���Ϊ1ʱ,��ǰ�油һ��0(����֮���Ի���ֳ���Ϊ1����������Ϊǰ��������޼���)
	{
		y = stringBeforeZero(y, 1);
	}
	if (x.size() > y.size()) //���һ�ζ�����У����ȷ���������ݳ���ͳһ
	{
		y = stringBeforeZero(y, x.size() - y.size());
	}
	if (x.size() < y.size()) //���һ�ζ�����У����ȷ���������ݳ���ͳһ
	{
		x = stringBeforeZero(x, y.size() - x.size());
	}
	int s = x.size();
	string a1, a0, b1, b0;
	if (s > 1)
	{
		a1 = x.substr(0, s / 2);
		a0 = x.substr(s / 2, s - 1);
		b1 = y.substr(0, s / 2);
		b0 = y.substr(s / 2, s - 1);
	}
	string result;
	if (s == 2) //����Ϊ2ʱ�����ŵݹ�Ľ�������
	{
		int na = string_to_num(a1);
		int nb = string_to_num(a0);
		int nc = string_to_num(b1);
		int nd = string_to_num(b0);
		result = num_to_string((na * 10 + nb) * (nc * 10 + nd));
	}
	else
	{ //���Ȳ�Ϊ2ʱ���÷��η����еݹ�����
	  /***************************************************
	  С��ʾ:
	  c = a*b = c2*(10^n) + c1*(10^(n/2)) + c0;
	  a = a1a0 = a1*(10^(n/2)) + a0;
	  b = b1b0 = b1*(10^(n/2)) + b0;
	  c2 = a1*b1;  c0 = a0*b0;
	  c1 = (a1 + a0)*(b1 + b0)-(c2 + c0);
	  ****************************************************/
		string c2 = IntMult(a1, b1);// (a1 * b1)
		string c0 = IntMult(a0, b0);// (a0 * b0)
		string c1_1 = stringAddstring(a1, a0);// (a1 + a0)
		string c1_2 = stringAddstring(b1, b0);// (b1 + b0)
		string c1_3 = IntMult(c1_1, c1_2);// (a1 + a0)*(b1 + b0)
		string c1_4 = stringAddstring(c2, c0);// (c2 + c0)
		string c1 = stringSubtractstring(c1_3, c1_4);// (a1 + a0)*(b1 + b0)-(c2 + c0)
		string s1 = stringFollowZero(c1, s / 2);// c1*(10^(n/2))
		string s2 = stringFollowZero(c2, s);// c2*(10^n)
		result = stringAddstring(stringAddstring(s2, s1), c0);// c2*(10^n) + c1*(10^(n/2)) + c0
	}
	return result;
}
int main()
{
	int f = 1;
	int n = 0;
	int op = 0;
	ifstream in("in.dat");
	if(!in.is_open())
    {
        cout<<"fail to open file : in.dat"<<endl;
		return -1;
    }
    in>>n;
	while (n--)
	{
		int flag1 = 0, flag2 = 0;//��¼���������ķ��ţ�Ϊ1��Ϊ����
		string A, B, C, D;
		string num1, num2;
		string r;
		in>>num1;
		in>>num2;
		int i = 0;
		in>>op;
		if (op == 3){
			if (num1[0] == '-')
			{
				flag1 = 1;
				num1 = num1.substr(1, r.size() - 1);
			}else
				flag1 = 0;
			if (num2[0] == '-')
			{
				flag2 = 1;
				num2 = num2.substr(1, r.size() - 1);
			}else
				flag2 = 0;
		}
		switch(op){
			case 1:
				r = IntAdd(num1, num2);
				break;
			case 2:
				r = IntSub(num1, num2);
				break;
			case 3:
				r = IntMult(num1, num2);
				break;
		}
		//����õĽ�������޼���ȥ����ǰ��ļ���0
		while ('0' == r[0] && r.size()>1)
		{
			r = r.substr(1, r.size() - 1);
		}
		if (op == 3 && flag1 != flag2)//�������ķ���λ��ͬ�����Ϊ����
		{
			r.insert(0, "-");
		}
		cout<<r<<endl;
	}
	system("pause");
}

// HammingCode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "HammingCode.h"

unsigned long HammingCode::cnm(int n, int m)
{
	unsigned long p = 1, np = 1, mp = 1, nmp = 1;
	for (int i = 1; i <= n; i++)
		np = np * i;
	for (int i = 1; i <= m; i++)
		mp = mp * i;
	for (int i = 1; i <= (n - m); i++)
		nmp = nmp * i;
	p = np / (mp * nmp);
	return p;
}
void HammingCode::backtracking(unsigned long n, unsigned long m, unsigned long stackindex, unsigned long& p)
{
	if (arr.size() == m)
	{
		// 如果数组大小等于m，表示找到了一个组合
		for (unsigned long j = 0; j < m; ++j)
		{
			if (j == m - 1) {
				// 如果是最后一个元素，换行输出
				//cout << "  " << arr[j] << endl;
				arrs[p] = arr;
				p++;
			}
			else {
				// 否则输出元素并添加空格
				//cout << "  " << arr[j];
			}
		}
		return;
	}
	// 使用回溯法生成组合
	for (unsigned long i = stackindex; i <= n; ++i)
	{
		arr.push_back(i);           // 将当前元素加入组合
		backtracking(n, m, i + 1, p);  // 递归调用，继续生成下一个元素
		arr.pop_back();             // 回溯，移除当前元素，尝试其他可能的元素
	}
}
int HammingCode::getscode()
{
	int l = 0;
	int k = 8;
	std::cout << "请选择偶校验【0】或奇校验【1】:" << std::endl;
	while (k != '\r')
	{
		k = _getch();
		if (k == '0' || k == '1')
		{
			isEVEN = (k == '0');
			_putch(k);
		}
	}
	if (isEVEN)
		std::cout << std::endl << "你选择了偶校验" << std::endl;
	else
		std::cout << std::endl << "你选择了奇校验" << std::endl;
	std::cout << "请输入原始信息【0】或【1】:" << std::endl;
	k = 8;
	while (k != '\r')
	{
		k = _getch();
		if (k == '0' || k == '1')
		{
			if ((l % 4 == 0) && (l != 0))
				std::cout << "'";
			_putch(k);
			l++;
			k = k - '0';
			Scode.push_back(k);
		}
	}
	std::cout << std::endl << "你输入的原始信息是:" << std::endl;
	for (k = 0; k < Scode.size(); k++)
	{
		std::cout << Scode[k];
		l--;
		if ((l % 4 == 0) && (l != 0))
			std::cout << "'";
	}
	std::cout << std::endl;
	return 0;
}
int HammingCode::ccodelen()
{
	int k = 1;
	int n = (int)Scode.size();
	while (pow(2, k) < n + k + 1)
		k++;
	return k;
}
int HammingCode::scodelen()
{
	int n = (int)Scode.size();
	return n;
}
int HammingCode::phcode()
{
	Hcode = Scode;
	int i = 0;
	int p = 0;
	for (i = 0; i < ccodelen(); i++)
	{
		p = (int)pow(2, i) - 1;
		Hcode.insert(Hcode.begin() + p, 0);
	}
	int l = (int)Hcode.size();
	std::cout << "预处理的编码:" << std::endl;
	for (i = 0; i < Hcode.size(); i++)
	{
		std::cout << Hcode[i];
		l--;
		if ((l % 4 == 0) && (l != 0))
			std::cout << "'";
	}
	std::cout << std::endl;
	return 0;
}
bool static cmp(int a, int b)
{
	return a < b;
}
int HammingCode::hamming()
{
	phcode();
	int k = ccodelen();
	int l = (int)Hcode.size();
	unsigned long  p = 0;
	for (int i = 1; i <= k; i++)
		p = p + cnm(k, i);
	arrs = new vector<int>[p];
	groups = new vector<int>[k];
	p = 0;
	for (int g = 1; g <= k; g++)//组合数 1组独有，2组共有，3组共有...,k组共有
	{
		arr.clear();
		backtracking(k, g, 1, p);
	}
	std::cout << "汉明码分组过程:" << std::endl;
	int  gc = 0;
	for (unsigned long g = 0; g < p; g++)
	{
		if ((int)arrs[g].size() > gc)
		{
			gc = (int)arrs[g].size();
			if (gc == 1)
				std::cout << gc << "组独有:" << std::endl;
			else
				std::cout << gc << "组共有:" << std::endl;
		}
		unsigned __int64  s = 0;
		for (int i = 0; i < arrs[g].size(); i++)
		{
			std::cout << arrs[g][i] << " ";
			s = s + (unsigned __int64)pow(2, arrs[g][i] - 1);
		}
		if (s <= l)
		{
			std::cout << ":" << s << std::endl;
			for (int i = 0; i < arrs[g].size(); i++)
			{
				Hcode[(unsigned __int64)pow(2, arrs[g][i] - 1) - 1] = Hcode[(unsigned __int64)pow(2, arrs[g][i] - 1) - 1] ^ Hcode[s - 1];
				groups[arrs[g][i] - 1].push_back((int)s);
			}
		}
		else
		{
			std::cout << ":" << "*" << s << std::endl;
		}
	}
	std::cout << "汉明码分组成员:" << std::endl;
	for (int i = 0; i < k; i++)
		std::sort(groups[i].begin(), groups[i].end(), cmp);
	for (int i = 0; i < k; i++)
	{
		std::cout << i + 1 << "组: ";
		for (int p = 0; p < groups[i].size(); p++)
			std::cout << groups[i][p] << ",";
		std::cout << std::endl;
	}
	//奇校验最后取反一次
	if (!isEVEN)
		for (int i = 1; i <= k; i++)
			Hcode[(unsigned __int64)pow(2, i - 1) - 1] = !Hcode[(unsigned __int64)pow(2, i - 1) - 1];
	delete[] groups;
	delete[] arrs;
	return 0;
}
int HammingCode::puthcode()
{
	int i;
	int l = (int)Hcode.size();
	for (i = 0; i < Hcode.size(); i++)
	{
		std::cout << Hcode[i];
		l--;
		if ((l % 4 == 0) && (l != 0))
			std::cout << "'";
	}
	return 0;
}
int main()
{
	HammingCode hc;
	std::cout << "汉明码(HammingCode)演示程序 v0.01 2024.5.1 leu9981" << std::endl;
	hc.getscode();
	int k = hc.ccodelen();
	std::cout << "原始信息长度 n=" << hc.scodelen() << " 效验位长度 k=" << k << " 汉明码总长度 l=" << k + hc.scodelen() << std::endl;
	hc.hamming();
	std::cout << "汉明码=";
	hc.puthcode();
	std::cout << std::endl << "按任意键退出" << std::endl;
	k=_getch();
	return 0;
}
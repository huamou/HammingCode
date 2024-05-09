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
void HammingCode::combine(unsigned long n, unsigned long m, unsigned long stackindex, unsigned long& p)
{
	if (arr.size() == m)
	{
		// 如果数组大小等于m，表示找到了一个组合
		arrs[p++] = arr;		
		return;
	}
	// 使用回溯法生成组合
	for (unsigned long i = stackindex; i <= n; ++i)
	{
		arr.push_back(i);           // 将当前元素加入组合
		combine(n, m, i + 1, p);  // 递归调用，继续生成下一个元素
		arr.pop_back();             // 回溯，移除当前元素，尝试其他可能的元素
	}
}
void HammingCode::setoptions()
{
	int l = 0;
	int k = 8;
	k = 8;
	std::cout << "请选择编码【0】或解码【1】: ";
	while (k != '\r')
	{
		k = _getch();
		if (k == '0' || k == '1')
		{
			isEncrypt = (k == '0');
			_putch(k);
		}
	}
	k = 8;
	std::cout << std::endl << "请选择偶校验【0】或奇校验【1】: ";
	while (k != '\r')
	{
		k = _getch();
		if (k == '0' || k == '1')
		{
			isEVEN = (k == '0');
			_putch(k);
		}
	}
	if (isEncrypt)
		std::cout << std::endl << "你选择了编码";
	else
		std::cout << std::endl << "你选择了解码";
	if (isEVEN)
		std::cout << ",偶校验" << std::endl;
	else
		std::cout << ",奇校验" << std::endl;
}
bool static isPower2(size_t N)//N为2的m次方
{
	for (int i = 0; (unsigned __int64)pow(2, i) <= N; i++)
	{
		if ((unsigned __int64)pow(2, i) == N)
			return true;
	}
	return false;
}
void HammingCode::getcode(vector<bool>& incode) const
{
	int l = 0;
	int k = 8;
	std::cout << "请输入二进制【0】或【1】:" << std::endl;
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
			incode.push_back(k);
		}
	}
	std::cout << std::endl;
	if (!isEncrypt)
	{
		if (incode.size() < 3)//解码数据必须大于等于3位 最小n=1 k=2 l=3
		{
			std::cout << "解码数据必须大于等于3位" << std::endl;
			exit(-1);
		}
		if (isPower2(incode.size()))//输入汉明码是2的n次方，最后一位数据可以去掉
		{
			std::cout << "输入解码数据为2的n次方，去掉最后一位数据" << std::endl;
			incode.pop_back();
		}
	}
	return;
}
void HammingCode::getcodelen()
{
	if (isEncrypt)
	{
		int k = 1;
		int n = (int)Scode.size();
		ScodeLen = n;
		while (pow(2, k) < n + k + 1)
			k++;
		KcodeLen = k;
		HcodeLen = k + n;
	}
	else
	{
		int k = 1;
		HcodeLen = (int)Hcode.size();
		int n = HcodeLen - k;
		while (pow(2, k) < n + k + 1)
		{
			k++;
			n = HcodeLen - k;
		}
		KcodeLen = k;
		ScodeLen = HcodeLen - k;
	}
}
void HammingCode::phcode()
{
	if (isEncrypt)
		Hcode = Scode;
	int i = 0;
	int p = 0;
	if (isEncrypt)
		for (i = 0; i < KcodeLen; i++)
		{
			p = (int)pow(2, i) - 1;
			Hcode.insert(Hcode.begin() + p, 0);
		}
	int l = HcodeLen;
	std::cout << "预处理的编码:" << std::endl;
	for (i = 0; i < Hcode.size(); i++)
	{
		std::cout << Hcode[i];
		l--;
		if ((l % 4 == 0) && (l != 0))
			std::cout << "'";
	}
	std::cout << std::endl;
	return;
}
bool static cmp(int a, int b)
{
	return a < b;
}
void HammingCode::hamming()
{
	phcode();
	int k = KcodeLen;
	int l = HcodeLen;
	unsigned long  p = 0;
	for (int i = 1; i <= k; i++)
		p = p + cnm(k, i);
	arrs = new vector<int>[p];
	groups = new vector<int>[k];
	p = 0;
	for (int g = 1; g <= k; g++)//组合数 1组独有，2组共有，3组共有...,k组共有
	{
		arr.clear();
		combine(k, g, 1, p);
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
				if (gc > 1)
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
	return;
}
void HammingCode::correctcode()
{
	std::cout << "检测位:" << std::endl;
	int ecc = 0;
	int ebit = 0;//出错检测位位数
	vector<int> pecc;
	for (int i = 0; i < KcodeLen; i++)
	{
		std::cout << "P" << pow(2, i) << "=" << Hcode[(unsigned __int64)pow(2, i) - 1] << std::endl;
		if (Hcode[(unsigned __int64)pow(2, i) - 1] != 0)
		{
			ecc += (int)pow(2, i);
			pecc.push_back((int)pow(2, i));
			ebit++;
		}
	}
	switch (ebit)
	{
	case 0://没有错误
		break;
	case 1://1位检测位出错，修改校验位
		std::cout << pecc[0] << "校验位出错" << std::endl;
		iHcode[(unsigned __int64)ecc - 1] = !iHcode[(unsigned __int64)ecc - 1];
		break;
	default://多位检测位出错，几组共有源信息位出错
		if (ecc <= HcodeLen)//共有位出错，修改数据位
		{
			std::cout << "第" << ecc << "位数据位出错,成功纠错" << std::endl;
			iHcode[(unsigned __int64)ecc - 1] = !iHcode[(unsigned __int64)ecc - 1];
		}
		else
		{
			std::cout << "多位校验位出错,但无法纠错" << std::endl;
		}
		break;
	}
	Hcode = iHcode;
	return;
}
void HammingCode::putcode()
{
	int i;
	int l = (int)Hcode.size();
	std::cout << "汉明码= ";
	for (i = 0; i < Hcode.size(); i++)
	{
		std::cout << Hcode[i];
		l--;
		if ((l % 4 == 0) && (l != 0))
			std::cout << "'";
	}
	std::cout << "  源信息= ";
	if (isEncrypt)
	{
		for (i = 0; i < Scode.size(); i++)
		{
			std::cout << Scode[i];
			l--;
			if ((l % 4 == 0) && (l != 0))
				std::cout << "'";
		}
	}
	else
	{
		for (i = KcodeLen; i > 0; i--)
		{
			Hcode.erase(Hcode.begin() + (unsigned __int64)pow(2, i - 1) - 1);
		}
		l = (int)Hcode.size();
		for (i = 0; i < Hcode.size(); i++)
		{
			std::cout << Hcode[i];
			l--;
			if ((l % 4 == 0) && (l != 0))
				std::cout << "'";
		}
	}
	return;
}
int main()
{
	HammingCode hc;
	std::cout << "汉明码(HammingCode)演示程序 v0.02 2024.5.1 leu9981" << std::endl;
	hc.setoptions();
	if (hc.isEncrypt)
		hc.getcode(hc.Scode);
	else
	{
		hc.getcode(hc.iHcode);
		hc.Hcode = hc.iHcode;
	}
	hc.getcodelen();
	std::cout << "源信息长度 n=" << hc.ScodeLen << " 校验位长度 k=" << hc.KcodeLen << " 汉明码总长度 l=" << hc.HcodeLen << std::endl;
	hc.hamming();
	if (!hc.isEncrypt)
		hc.correctcode();
	hc.putcode();
	std::cout << std::endl << "按任意键退出" << std::endl;
	int k = _getch();
	return 0;
}
#pragma once
#include <vector>
#include <conio.h>
#include <algorithm>
using namespace std;
class HammingCode
{
private:
	vector<bool> Scode;				    //源信息
	vector<bool> Hcode;					//汉明码=校验码+源信息		
	vector<bool> iHcode;   			    //待验证的汉明码=校验码+源信息	
	vector<int>* groups = nullptr;      //汉明码分组情况
	vector<int>  arr;					//存储一个组合的动态数组
	vector<int>* arrs = nullptr;        //存储所有组合的动态数组	
	bool isEVEN = true;		            //是否偶效验 true 为偶效验，flase为奇校验
	bool isEncrypt = true;              //编码:输入源信息生成汉明码 
	bool isCombine = true;              //组合法分组为true 
	int  ScodeLen = 0;                  //源信息长度 n 
	int  KcodeLen = 0;                  //效验码位数 k	pow(2, k) >= n + k + 1
	int  HcodeLen = 0;	                //汉明码长度 n+k
public:
	unsigned long cnm(int n, int m);    //计算n取m组合数
	void combine(unsigned long  n, unsigned long  m, unsigned  long stackindex, unsigned long& p); //n取m组合
	void getcode();//输入信息:可以是源信息，也可以是编码后的汉明码
	void setoptions();//设置奇/偶效验，编码/解码 分组方法
	void getcodelen();//求 n k n+k  ScodeLen KcodeLen HcodeLen
	void phcode();//生产未效验的汉明码 校验位初设为0	
	void hamming();//求解汉明码 校验位求解
	void qhamming();//求解汉明码 校验位求解 
	void correctcode();//汉明码检错
	void putcode();//输出正确的源信息和汉明码
	//以下为属性输入/输出函数
	bool getEVEN() const;    //获取奇/偶校验
	bool getEncrypt() const; //获取编码/解码
	bool getCombine() const; //获取分组方式
	int  getScodeLen() const;//获取源信息长度
	int  getKcodeLen() const;//获取效验码长度
	int  getHcodeLen() const;//获取汉明码长度
};
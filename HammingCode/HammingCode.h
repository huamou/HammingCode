#pragma once
#include <vector>
#include <conio.h>
#include <algorithm>
using namespace std;
class HammingCode
{
private:
public:
	vector<bool> Scode;				    //源信息
	vector<bool> Hcode;					//汉明码=校验码+源信息		
	vector<bool> iHcode;				//待验证的汉明码=校验码+源信息	
	vector<int>* groups = nullptr;      //汉明码分组情况
	vector<int>  arr;					//存储一个组合的动态数组
	vector<int>* arrs = nullptr;        //存储所有组合的动态数组	
	bool isEVEN = true;		            //是否偶效验 true 为偶效验，flase为奇校验
	bool isEncrypt = true;              //输入源信息生成汉明码
	int  ScodeLen = 0;                  //源信息长度 n 
	int  KcodeLen = 0;                  //效验码位数 k	pow(2, k) >= n + k + 1
	int  HcodeLen = 0;	                //汉明码长度 l=n+k
public:
	unsigned long cnm(int n, int m);     //计算n取m组合数
	void backtracking(unsigned long  n, unsigned long  m, unsigned  long stackindex, unsigned long& p); //回溯法生成从 1 到 n 的数字中长度为 m 的所有组合
	void getcode(vector<bool> &incode);//输入信息:可能是源信息，也可能是编码后的汉明码
	void setoptions();//设置奇/偶效验，编码/解码
	void getcodelen();//求 n k l	  ScodeLen KcodeLen HcodeLen
	void phcode();//生产未效验的汉明码 校验位初设为0	
	void hamming();//求解汉明码 校验位求解	
	void putcode();//输出汉明码和源信息
	void correctcode();//汉明码检错
};
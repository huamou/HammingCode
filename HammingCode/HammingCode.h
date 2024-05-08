#pragma once
#include <vector>
#include <conio.h>
#include <algorithm>
using namespace std;
class HammingCode
{
private:
	vector<bool> Scode;				    //原始信息
	vector<bool> Hcode;					//编码后的信息  校验码+原始信息		
	vector<int>  *groups = nullptr;     //汉明码分组情况
	vector<int>  arr;					//存储一个组合的动态数组
	vector<int>  *arrs=nullptr;         //存储所有组合的动态数组	
	bool isEVEN=true;		            //是否偶效验 true 为偶效验，flase为奇校验
public:
	unsigned long cnm(int n,int m);     //计算n取m组合数
	void backtracking(unsigned long  n, unsigned long  m, unsigned  long stackindex,unsigned long &p); //回溯法生成从 1 到 n 的数字中长度为 m 的所有组合
	int getscode();//输入原始信息
	int scodelen();//原始信息长度 n
	int ccodelen();//插入效验码位数 k	pow(2,k)>=n+k+1
	int phcode();//生产未效验的汉明码 校验位初设为0	
	int hamming();//求解汉明码 校验位求解	
	int puthcode();//输出汉明码
};
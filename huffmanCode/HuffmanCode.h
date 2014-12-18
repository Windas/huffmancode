#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stdio.h>

//#include <algorithm>
//#include <function>
using namespace std;
extern int bytearr[256];
extern int length;
extern int painum;

/*--------------------------------
        父节点
-------------------------------*/
class HuffNode
{
		 
		
	public:
		char element;//要编码的字符
		 int weight;//权重
		 string code;//编码
		 HuffNode *left;
		 HuffNode *right;
		HuffNode()
		{
			this->left = this->right = NULL;
		}
		HuffNode(int ele,HuffNode *l = NULL,HuffNode* r = NULL)
		{
			this->element = ele;
			this->left = l;
			this->right = r;
		}

		HuffNode * getLeft()
		{
			return left;
		}
		void setLeft(HuffNode * tn)
		{
			left = tn;
		}
		HuffNode * getRight()
		{
			return right;
		}
		void setRight(HuffNode * tn)
		{
			right = tn;
		}
		virtual bool isLeaf()
		{
			return false;
		}

		
		
};
/*--------------------------------
        叶节点
-------------------------------*/
class LeafNode:public HuffNode
{
public:
	//int weight;
	bool isLeaf()
	{
		return true;
	}
	LeafNode(int wei,int ele)
	{
		this->weight = wei;
		this->element = ele;
	}
	

};
/*--------------------------------
        内部节点
-------------------------------*/

class IntlNode:public HuffNode
{
public:
	//int weight;
	//HuffNode *left;
	//HuffNode *right;
	IntlNode(HuffNode *le,HuffNode *ri)
	{
		this->left = le;
		this->right = ri;
		this->weight = le->weight + ri->weight;
	}
	bool isLeaf()
	{
		return false;
	}

	
	
};
/*--------------------------------
        哈夫曼树
-------------------------------*/
class HuffTree
{
	
public:
	HuffNode *root;
	HuffTree(HuffNode *left,HuffNode *right)
	{
		this->root =  new IntlNode(left,right);
	}
};

HuffNode* buildHuff();
void encode(HuffNode* root,string zocode);//从根节点开始递归，左为0，右为1
void buildHeap(HuffNode* arr[] );//传入要建堆的数组
HuffNode * removetop(HuffNode *arr[]);//传入建好堆的数组
void add(HuffNode *arr[],HuffNode * val);//传入建好堆的数组,要添加的元素
void findCode(char ch,HuffNode *root);//char表示要查找的字符，code表示编码
void findBytecode(HuffNode *root,char** ch,int* countnum,FILE *fp);//遍历树找到与之对应的字符,传入的参数为每次递归的根节点，解析的01字符，作为01字符长度的计数器，防止越界
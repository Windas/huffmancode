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
        ���ڵ�
-------------------------------*/
class HuffNode
{
		 
		
	public:
		char element;//Ҫ������ַ�
		 int weight;//Ȩ��
		 string code;//����
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
        Ҷ�ڵ�
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
        �ڲ��ڵ�
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
        ��������
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
void encode(HuffNode* root,string zocode);//�Ӹ��ڵ㿪ʼ�ݹ飬��Ϊ0����Ϊ1
void buildHeap(HuffNode* arr[] );//����Ҫ���ѵ�����
HuffNode * removetop(HuffNode *arr[]);//���뽨�öѵ�����
void add(HuffNode *arr[],HuffNode * val);//���뽨�öѵ�����,Ҫ��ӵ�Ԫ��
void findCode(char ch,HuffNode *root);//char��ʾҪ���ҵ��ַ���code��ʾ����
void findBytecode(HuffNode *root,char** ch,int* countnum,FILE *fp);//�������ҵ���֮��Ӧ���ַ�,����Ĳ���Ϊÿ�εݹ�ĸ��ڵ㣬������01�ַ�����Ϊ01�ַ����ȵļ���������ֹԽ��
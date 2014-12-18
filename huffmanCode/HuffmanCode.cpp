#include "HuffmanCode.h"
HuffNode * rootNode;//�����γɵ����ĸ��ڵ�
extern string code;//�����ļ��������ַ���
extern string byteCode;//����01�ַ���ת�����ֽ��ַ���
extern int pagesizecount;//��Ϊ�ı����ȼ������������ȡ���ı�
extern HuffNode ** leafNodeSet;//��Ϊ�洢Ҷ�ڵ�ļ���
int nodecount = 0;//��ΪҶ�ڵ㼯�ϱ����ļ�����
/*--------------------------------
        ������������
-------------------------------*/
HuffNode* buildHuff()
{
	HuffNode* arr[256];
	int i,j;//i��Ϊbytearr�ļ�������j��Ϊarr�ļ�����
	for(i = 0,j = 0;i < 256;++i)//Ϊ�ı��г��ֵ��ַ�����Ҷ�ڵ㣬���ŵ�����arr��
	{
		if(bytearr[i] != 0)
		{
			arr[j] = new LeafNode(bytearr[i],(char)i);
			++j;
		}
		else
		{
			continue;
		}
		
	}
	length = j;
	painum = length - 1;
	buildHeap(arr);//������С��,ÿ��ȥ����С��������
	HuffNode *root = arr[0];//���ڴ洢���ڵ�
	while(painum != 0)
	{
		HuffNode *fir = removetop(arr);
		HuffNode *sec = removetop(arr);
		root = (new HuffTree(fir,sec))->root;//������С�Ľڵ�ϳ�һ����������ͷ���������
		add(arr,root);
	}
	rootNode = root;
	return root;
}
//bool operator>(HuffNode a,HuffNode b)
//{
//	return a.weight > b.weight;
//}

/*--------------------------------
        С����
-------------------------------*/

void buildHeap(HuffNode* arr[] )//����Ҫ���ѵ�����
{
	for(int i = painum;i > 0;i-=2)
	{
		int root = (i-1)/2;
		int smallest = root;
		if(arr[smallest]->weight > arr[2*root+1]->weight)//���ڵ�����ӽڵ��
		{
			smallest = 2*root+1;
		}
		if((2*root+2) <= painum)
		{
			if(arr[smallest]->weight > arr[2*root+2]->weight)
			{
				smallest = 2*root+2;
			}
		}
		if(root != smallest)//���ڵ㲻����С�ģ�����
		{
			HuffNode * val = arr[root];
			arr[root] = arr[smallest];
			arr[smallest] = val;
		}
		
		
		
	}
	
}
	/*--------------------------------
			ȡ������Ԫ��
	-------------------------------*/
HuffNode * removetop(HuffNode *arr[])//���뽨�öѵ�����
{
	HuffNode * val = arr[0];//��topԪ�غ����һ��Ԫ�ؽ���
	arr[0] =arr[painum];
	arr[painum] = val;
	--painum;
	buildHeap(arr);
	return arr[painum+1];
	
}
	/*--------------------------------
			���Ԫ��
	-------------------------------*/
void add(HuffNode *arr[],HuffNode * val)//���뽨�öѵ�����,Ҫ��ӵ�Ԫ��
{

	++painum;
	arr[painum] = val;
	buildHeap(arr);
}

/*--------------------------------
        �Թ����������б���
-------------------------------*/
void encode(HuffNode* root,string zocode)//�Ӹ��ڵ㿪ʼ�ݹ飬��Ϊ0����Ϊ1
{
	if(root->isLeaf())
	{
		root->code = zocode;
		leafNodeSet[nodecount] = root;
		++nodecount;
		return;
	}
	else
	{
		encode(root->left,zocode+"0");
		encode(root->right,zocode+"1");
		return;
	}
}
/*--------------------------------
       ���ұ���
-------------------------------*/
void findCode(char ch,HuffNode *root)//char��ʾҪ���ҵ��ַ���code��ʾ����
{
	for(nodecount = 0;nodecount < length;++nodecount)
	{
		if(leafNodeSet[nodecount]->element == ch)
		{
			code+=leafNodeSet[nodecount]->code;
			//StringToCode();
			++pagesizecount;
			return;
		}
	}
	
}
